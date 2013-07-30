#include <android/log.h>

#include "notificationmanager.h"

#define NOTIFICATION_SERVICE_NAME "notification"
#define NOTIFICATION_MANAGER_TAG "NotificationManager"

#define LOG(L,F, ...) __android_log_print(L, NOTIFICATION_MANAGER_TAG, F, ## __VA_ARGS__ )

JavaGlobalRef<jobject> *NotificationManager::notificationManager_ = 0;
JavaGlobalRef<jobject> *NotificationManager::notificationBuilder_ = 0;

namespace JavaObjects {

#include "jobjects/contextwrapper.h"
#include "jobjects/notificationbuilder.h"
#include "jobjects/notificationmanager.h"

}

/**************************************************************************/
NotificationManager::NotificationManager()
{
}

NotificationManager::~NotificationManager()
{
}

void NotificationManager::freeJavaResources(std::weak_ptr<AttachedJENV> jvm_weak)
{
    if (!notificationManager_ && notificationBuilder_)
    {
        LOG(ANDROID_LOG_INFO, ">>> Nothing to free");
        return;
    }

    std::shared_ptr<AttachedJENV> jvm_ptr = jvm_weak.lock();

    if (notificationManager_)
    {
        notificationManager_->deleteRef(jvm_ptr->env());
        delete notificationManager_;
        notificationManager_ = 0;
    }

    if (notificationBuilder_)
    {
        notificationBuilder_->deleteRef(jvm_ptr->env());
        delete notificationBuilder_;
        notificationBuilder_ = 0;
    }
}

bool NotificationManager::createJavaNotificationBuilder(std::weak_ptr<AttachedJENV> jvm_weak)
{
    std::shared_ptr<AttachedJENV> jvm_ptr = jvm_weak.lock();

    bool ret = false;
    jvalue notificationBuilder;
    jclass notificationBuilderClass =
            jvm_ptr->classLoader()->loadClass("android.app.Notification$Builder");

    /* As class loaded by me create local reference to avoid surprises from java GC */
    std::shared_ptr<JavaLocalRef<jclass> > notifBuilderClassRef(jvm_ptr->createRef(notificationBuilderClass));

    jvm_ptr->exceptionsHandler(__FILE__, __LINE__);

    if (!notificationBuilderClass)
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to get Notification.Builder class");
        return ret;
    }

    std::shared_ptr<JavaClass> jc(jvm_ptr->createJO(notifBuilderClassRef->get(), &JavaObjects::NotificationBuilder_Desc));

    notificationBuilder = jc->call("<init>", AndroidContext::instance()->activity());
    if (!notificationBuilder.l)
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable create Notification.Builder instance");
    }
    else
    {
        notificationBuilder_ = jvm_ptr->createGlobalRef(notificationBuilder.l);
    }

    LOG(ANDROID_LOG_INFO, ">>> Notification.Builder instance created");

    if (notificationBuilder_) ret = true;

    return ret;
}

bool NotificationManager::getJavaNotificationManager(std::weak_ptr<AttachedJENV> jvm_weak)
{
    bool ret = false;

    std::shared_ptr<AttachedJENV> jvm_ptr = jvm_weak.lock();

    std::shared_ptr<JavaObject> jactivity(
                    jvm_ptr->createJO(AndroidContext::instance()->activity(),&JavaObjects::ContextWrapper_Desc));

    jvalue notificationManager = jactivity->call("getSystemService",
                                          jvm_ptr->env()->NewStringUTF(NOTIFICATION_SERVICE_NAME));
    notificationManager_ = jvm_ptr->createGlobalRef(notificationManager.l);


    LOG(ANDROID_LOG_INFO, ">>> Notification service retrieved");

    if (notificationManager_) ret = true;
    return ret;
}

bool NotificationManager::initializeStatics(std::weak_ptr<AttachedJENV> jvm_weak)
{
    std::shared_ptr<AttachedJENV> jvm_ptr = jvm_weak.lock();

    bool init = true;
    if (!notificationManager_ || !notificationBuilder_)
    {
        /* Initialize java objects */
        if (!notificationManager_ && init)
        {
            init = init && getJavaNotificationManager(jvm_ptr);
        }
        if (!notificationBuilder_ && init)
        {
            init = init && createJavaNotificationBuilder(jvm_ptr);
        }
        if (!init)
        {
            LOG(ANDROID_LOG_ERROR, ">>> Unable to init java objects");
        }
    }
    return init;
}

void NotificationManager::notify(jint id, const char *title, const char *text)
{
    std::shared_ptr<AttachedJENV> jvm_ptr(new AttachedJENV());
    if (!jvm_ptr->attached())
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to get VM");
        return;
    }

    if (!initializeStatics(jvm_ptr))
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nb(jvm_ptr->createJO(notificationBuilder_->get(),
                                                     &JavaObjects::NotificationBuilder_Desc));
    nb->call("setAutoCancel", (jboolean)JNI_TRUE);
    nb->call("setContentTitle", jvm_ptr->env()->NewStringUTF(title));
    nb->call("setContentText", jvm_ptr->env()->NewStringUTF(text));
    nb->call("setSmallIcon", /*android.R.drawable.sym_action_email*/0x0108008f);
    jvalue notification = nb->call("getNotification");
    if (notification.l)
    {
        std::shared_ptr<JavaLocalRef<jobject> > notif(jvm_ptr->createRef(notification.l));
        std::shared_ptr<JavaObject> nm(jvm_ptr->createJO(notificationManager_->get(),
                                                         &JavaObjects::NotificationManager_Desc));
        nm->call("notify", id, notif->get());

        LOG(ANDROID_LOG_INFO, ">>> Notification created succesfully");
    }
    else
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to create Notification object");
    }
}

void NotificationManager::notify(const char *tag, int id, const char *title, const char *text)
{
    std::shared_ptr<AttachedJENV> jvm_ptr(new AttachedJENV());
    if (!jvm_ptr->attached())
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to get VM");
        return;
    }

    if (!initializeStatics(jvm_ptr))
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nb(jvm_ptr->createJO(notificationBuilder_->get(),
                                                     &JavaObjects::NotificationBuilder_Desc));
    nb->call("setAutoCancel", (jboolean)JNI_TRUE);
    nb->call("setContentTitle", jvm_ptr->env()->NewStringUTF(title));
    nb->call("setContentText", jvm_ptr->env()->NewStringUTF(text));
    nb->call("setSmallIcon", /*android.R.drawable.sym_action_email*/0x0108008f);
    jvalue notification = nb->call("getNotification");
    if (notification.l)
    {
        std::shared_ptr<JavaLocalRef<jobject> > notif(jvm_ptr->createRef(notification.l));
        std::shared_ptr<JavaObject> nm(jvm_ptr->createJO(notificationManager_->get(),
                                                         &JavaObjects::NotificationManager_Desc));
        nm->call("notify_0", jvm_ptr->env()->NewStringUTF(tag), id, notif->get());

        LOG(ANDROID_LOG_INFO, ">>> Notification created succesfully");
    }
    else
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to create Notification object");
    }
}

void NotificationManager::cancel(int id)
{
    std::shared_ptr<AttachedJENV> jvm_ptr(new AttachedJENV());
    if (!jvm_ptr->attached())
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to get VM");
        return;
    }

    if (!initializeStatics(jvm_ptr))
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nm(jvm_ptr->createJO(notificationManager_->get(),
                                                     &JavaObjects::NotificationManager_Desc));
    nm->call("cancel", id);

    LOG(ANDROID_LOG_INFO, ">>> Notification id:%d canceled succesfully", id);
}

void NotificationManager::cancel(const char *tag, int id)
{
    std::shared_ptr<AttachedJENV> jvm_ptr(new AttachedJENV());
    if (!jvm_ptr->attached())
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to get VM");
        return;
    }

    if (!initializeStatics(jvm_ptr))
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nm(jvm_ptr->createJO(notificationManager_->get(),
                                                     &JavaObjects::NotificationManager_Desc));
    nm->call("cancel_1", jvm_ptr->env()->NewStringUTF(tag), id);

    LOG(ANDROID_LOG_INFO, ">>> Notification tag:'%s' id:%d canceled succesfully", tag, id);
}

void NotificationManager::cancelAll()
{
    std::shared_ptr<AttachedJENV> jvm_ptr(new AttachedJENV());
    if (!jvm_ptr->attached())
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to get VM");
        return;
    }

    if (!initializeStatics(jvm_ptr))
    {
        LOG(ANDROID_LOG_ERROR, ">>> Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nm(jvm_ptr->createJO(notificationManager_->get(),
                                                     &JavaObjects::NotificationManager_Desc));
    nm->call("cancelAll");

    LOG(ANDROID_LOG_INFO, ">>> All notification canceled succesfully");
}
