#include <android/log.h>

#include "androidcontext.h"

#define ANDROID_CONTEXT_TAG "AndroidContext"
#define QT_APPLICATION_CLASS_NAME "org/qtproject/qt5/android/QtNative"
#define QT_APPLICATION_GET_ACTIVITY_METHOD "activity"
#define QT_APPLICATION_GET_ACTIVITY_METHOD_SIG "()Landroid/app/Activity;"
#define QT_APPLICATION_GET_CLASS_LOADER_METHOD "classLoader"
#define QT_APPLICATION_GET_CLASS_LOADER_METHOD_SIG "()Ljava/lang/ClassLoader;"
#define CLASS_LOADER_LOAD_CLASS_METHOD "loadClass"
#define CLASS_LOADER_LOAD_CLASS_METHOD_SIG "(Ljava/lang/String;)Ljava/lang/Class;"

#define LOG(L,F, ...) __android_log_print(L, ANDROID_CONTEXT_TAG, F, ## __VA_ARGS__ )

/***************************************************************************/
AttachedJENV::AttachedJENV()
    : env_(0)
    , attached_(false)
    , classLoader_(0)
{
    JavaVM *jvm_ = AndroidContext::instance()->jvm();

    if (jvm_ && jvm_->GetEnv(reinterpret_cast<void**>(&env_), JNI_VERSION_1_6) < 0)
    {
        if (jvm_->AttachCurrentThread(&env_, NULL) < 0)
        {
            LOG(ANDROID_LOG_ERROR, "AttachCurrentThread failed");
            env_ = NULL;
        }
        attached_ = true;
    }
    else
    {
        LOG(ANDROID_LOG_ERROR, "GetEnv failed");
    }
}

AttachedJENV::~AttachedJENV()
{
    JavaVM *jvm_ = AndroidContext::instance()->jvm();

    if (jvm_ && attached_) {
        jvm_->DetachCurrentThread();
        env_ = 0;
    }
}

JNIEnv *AttachedJENV::env()
{
    return env_;
}

void AttachedJENV::exceptionsHandler(const char *file, int line)
{
    if (env_->ExceptionOccurred())
    {
        LOG(ANDROID_LOG_ERROR, "Java exception occured at %s:%d", file, line);
        env_->ExceptionDescribe();
        env_->ExceptionClear();
    }
}

bool AttachedJENV::attached()
{
    return attached_;
}

std::shared_ptr<ClassLoader> AttachedJENV::classLoader()
{
    if (!classLoader_.get())
    {
        // Create classLoader instance associated with current thread
        classLoader_.reset(AndroidContext::instance()->classLoader()->clone(env_));
    }
    return classLoader_;
}

/***************************************************************************/
ClassLoader::ClassLoader(jobject classLoader, jmethodID methodID)
    : classLoader_(classLoader)
    , methodID_(methodID)
    , env_(0)
{
}

ClassLoader *ClassLoader::clone(JNIEnv *env)
{
    ClassLoader *cloned = new ClassLoader(classLoader_, methodID_);
    cloned->env_ = env;
    return cloned;
}

jclass ClassLoader::loadClass(const char *name)
{
    jclass result = 0;

    if (env_)
    {
        result = static_cast<jclass>(
                    env_->CallObjectMethod(classLoader_, methodID_,
                                           env_->NewStringUTF(name)));
    }

    return result;
}

/***************************************************************************/
AndroidContext::AndroidContext()
    : jvm_(0)
    , qtNativeClass_(0)
    , qtActivity_(0)
    , classLoader_(0)
{
}

AndroidContext *AndroidContext::instance()
{
    static AndroidContext *result = 0;
    if (!result) {
        result = new AndroidContext();
    }
    return result;
}

ClassLoader *AndroidContext::classLoader()
{
    return classLoader_;
}

bool AndroidContext::initialize(JavaVM *jvm/*, JNIEnv* env*/)
{
    bool res = false;

    jvm_ = jvm;

    JNIEnv* env;
    if (jvm_->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        LOG(ANDROID_LOG_FATAL, "GetEnv failed");
        return -JNI_FALSE;
    }

    if (env)
    {
        LOG(ANDROID_LOG_INFO, "Loading class '%s'", QT_APPLICATION_CLASS_NAME);

        qtNativeClass_ = env->FindClass(QT_APPLICATION_CLASS_NAME);

        if (!qtNativeClass_)
        {
            LOG(ANDROID_LOG_ERROR, "Class not found '%s'", QT_APPLICATION_CLASS_NAME);
        }
        else
        {
            qtNativeClass_ = static_cast<jclass>(env->NewGlobalRef(qtNativeClass_));

            /* ClassLoader */
            jmethodID methodID = env->GetStaticMethodID(qtNativeClass_,
                                                        QT_APPLICATION_GET_CLASS_LOADER_METHOD,
                                                        QT_APPLICATION_GET_CLASS_LOADER_METHOD_SIG);

            jobject classLoader = env->NewGlobalRef(env->CallStaticObjectMethod(qtNativeClass_, 
																				methodID));
            if (!classLoader)
            {
                LOG(ANDROID_LOG_ERROR, "Unable to get class loader");
            }

            jclass classLoaderClass = env->GetObjectClass(classLoader);

            methodID = env->GetMethodID(classLoaderClass, 
										CLASS_LOADER_LOAD_CLASS_METHOD, 
										CLASS_LOADER_LOAD_CLASS_METHOD_SIG);

            classLoader_ = new ClassLoader(classLoader, methodID);

            methodID = env->GetStaticMethodID(qtNativeClass_,
                                              QT_APPLICATION_GET_ACTIVITY_METHOD,
                                              QT_APPLICATION_GET_ACTIVITY_METHOD_SIG);

            LOG(ANDROID_LOG_INFO, "Get activity");

            if (!methodID)
            {
                LOG(ANDROID_LOG_ERROR, "Can't find method '%s(%s)'",
                                    QT_APPLICATION_GET_ACTIVITY_METHOD, 
									QT_APPLICATION_GET_ACTIVITY_METHOD_SIG);
            }
            else
            {
                qtActivity_ = env->CallStaticObjectMethod(qtNativeClass_, methodID);
                if (qtActivity_)
                {
                    qtActivity_ = env->NewGlobalRef(qtActivity_);
                    res = true;
                }
                else
                {
                    LOG(ANDROID_LOG_ERROR, "Get activity failed");
                }
            }
        }
    }
    return res;
}

JavaVM *AndroidContext::jvm()
{
    return jvm_;
}

jobject AndroidContext::activity()
{
    return qtActivity_;
}

/***************************************************************************/
extern "C" {

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    reserved = reserved;

    LOG(ANDROID_LOG_INFO, "Android context initialization...");

    AndroidContext *context = AndroidContext::instance();
    if (!context->initialize(vm))
    {
        LOG(ANDROID_LOG_FATAL, "Android context initialization failed");
        return -1;
    }

    LOG(ANDROID_LOG_INFO, "Android context initialization done");

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved)
{
    vm = vm;
    reserved = reserved;
}

}
