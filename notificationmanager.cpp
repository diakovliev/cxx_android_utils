#include <android/log.h>

#include "notificationmanager.h"

#define NOTIFICATION_MANAGER_TAG "NotificationManager"

#define LOG(L,F, ...) __android_log_print(L, NOTIFICATION_MANAGER_TAG, F, ## __VA_ARGS__ )

std::shared_ptr<JavaGlobalRef<jobject> > NotificationManager::notificationManager_;
std::shared_ptr<JavaGlobalRef<jobject> > NotificationManager::notificationBuilder_;

namespace JavaObjects {

#include "jobjects/context.h"
#include "jobjects/contextwrapper.h"
#include "jobjects/notificationbuilder.h"
#include "jobjects/notificationmanager.h"
#if 0
#include "jobjects/drawable.h"
#endif

}

/**************************************************************************/
NotificationManager::NotificationManager()
{
}

NotificationManager::~NotificationManager()
{
}

void NotificationManager::freeJavaResources(std::weak_ptr<AttachedJENV> jenv_weak)
{
    if (notificationManager_ && notificationBuilder_)
    {
        LOG(ANDROID_LOG_INFO, "Nothing to free");
        return;
    }

    std::shared_ptr<AttachedJENV> jenv = jenv_weak.lock();

    if (notificationManager_)
    {
        notificationManager_->deleteRef(jenv->env());
        notificationManager_.reset();
    }

    if (notificationBuilder_)
    {
        notificationBuilder_->deleteRef(jenv->env());
        notificationBuilder_.reset();
    }
}

bool NotificationManager::createJavaNotificationBuilder(std::weak_ptr<AttachedJENV> jenv_weak)
{
    std::shared_ptr<AttachedJENV> jenv = jenv_weak.lock();

    bool ret = false;
    jvalue notificationBuilder;
    jclass notificationBuilderClass =
            jenv->classLoader()->loadClass("android.app.Notification$Builder");

    /* As class loaded by me create local reference to avoid surprises from java GC */
    std::shared_ptr<JavaLocalRef<jclass> > notifBuilderClassRef(jenv->createRef(notificationBuilderClass));

    jenv->exceptionsHandler(__FILE__, __LINE__);

    if (!notificationBuilderClass)
    {
        LOG(ANDROID_LOG_ERROR, "Unable to get Notification.Builder class");
        return ret;
    }

    std::shared_ptr<JavaClass> jc = jenv->createJO(notifBuilderClassRef->get(), &JavaObjects::NotificationBuilder_Desc);

    notificationBuilder = jc->call("<init>", AndroidContext::instance()->activity());
    if (!notificationBuilder.l)
    {
        LOG(ANDROID_LOG_ERROR, "Unable create Notification.Builder instance");
    }
    else
    {
        notificationBuilder_ = jenv->createGlobalRef(notificationBuilder.l);
    }

    LOG(ANDROID_LOG_INFO, "Notification.Builder instance created");

    if (notificationBuilder_) ret = true;

    return ret;
}

bool NotificationManager::getJavaNotificationManager(std::weak_ptr<AttachedJENV> jenv_weak)
{
    bool ret = false;

    std::shared_ptr<AttachedJENV> jenv = jenv_weak.lock();

    std::shared_ptr<JavaObject> jactivity = jenv->createJO(AndroidContext::instance()->activity(),&JavaObjects::ContextWrapper_Desc);

    std::shared_ptr<JavaLocalRef<jclass> > contextClassRef =
            jenv->createRef(jenv->classLoader()->loadClass("android.content.Context"));

    std::shared_ptr<JavaClass> context = jenv->createJO(contextClassRef->get(), &JavaObjects::Context_Desc);

    jvalue notificationManager = jactivity->call("getSystemService",
                                                 context->get("NOTIFICATION_SERVICE").l);

    notificationManager_ = jenv->createGlobalRef(notificationManager.l);

    LOG(ANDROID_LOG_INFO, "Notification service retrieved");

    if (notificationManager_) ret = true;
    return ret;
}

bool NotificationManager::initializeStatics(std::weak_ptr<AttachedJENV> jenv_weak)
{
    std::shared_ptr<AttachedJENV> jenv = jenv_weak.lock();

    bool init = true;
    if (!notificationManager_ || !notificationBuilder_)
    {
        /* Initialize java objects */
        if (!notificationManager_ && init)
        {
            init = init && getJavaNotificationManager(jenv);
        }
        if (!notificationBuilder_ && init)
        {
            init = init && createJavaNotificationBuilder(jenv);
        }
        if (!init)
        {
            LOG(ANDROID_LOG_ERROR, "Unable to init java objects");
        }
    }
    return init;
}

jint NotificationManager::getIconIndex(std::weak_ptr<AttachedJENV> jenv_weak)
{
    std::shared_ptr<AttachedJENV> jenv = jenv_weak.lock();
#if 0
    jclass drawable_class =
            jenv->classLoader()->loadClass("android.R.drawable");

    int sym_action_email = 0;
    if (drawable_class)
    {
        std::shared_ptr<JavaLocalRef<jclass> > ref = jenv->createRef(drawable_class);
        std::shared_ptr<JavaClass> drawable = jenv->createJO(ref->get(), &JavaObjects::drawable_Desc);
        sym_action_email = drawable->get("sym_action_email").i;
    }

    return sym_action_email;
#endif
    return 0x0108008f;
}

void NotificationManager::notify(jint id, const char *title, const char *text)
{
    std::shared_ptr<AttachedJENV> jenv(new AttachedJENV());
    if (!jenv->attached())
    {
        LOG(ANDROID_LOG_ERROR, "Unable to get VM");
        return;
    }

    if (!initializeStatics(jenv))
    {
        LOG(ANDROID_LOG_ERROR, "Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nb = jenv->createJO(notificationBuilder_->get(),
                                                     &JavaObjects::NotificationBuilder_Desc);
    nb->call("setAutoCancel", (jboolean)JNI_TRUE);
    nb->call("setContentTitle", jenv->env()->NewStringUTF(title));
    nb->call("setContentText", jenv->env()->NewStringUTF(text));
    nb->call("setSmallIcon", getIconIndex(jenv));
    jvalue notification = nb->call("getNotification");
    if (notification.l)
    {
        std::shared_ptr<JavaLocalRef<jobject> > notif(jenv->createRef(notification.l));
        std::shared_ptr<JavaObject> nm = jenv->createJO(notificationManager_->get(),
                                                         &JavaObjects::NotificationManager_Desc);
        nm->call("notify", id, notif->get());

        LOG(ANDROID_LOG_INFO, "Notification created succesfully");
    }
    else
    {
        LOG(ANDROID_LOG_ERROR, "Unable to create Notification object");
    }
}

void NotificationManager::notify(const char *tag, int id, const char *title, const char *text)
{
    std::shared_ptr<AttachedJENV> jenv(new AttachedJENV());
    if (!jenv->attached())
    {
        LOG(ANDROID_LOG_ERROR, "Unable to get VM");
        return;
    }

    if (!initializeStatics(jenv))
    {
        LOG(ANDROID_LOG_ERROR, "Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nb = jenv->createJO(notificationBuilder_->get(),
                                                     &JavaObjects::NotificationBuilder_Desc);
    nb->call("setAutoCancel", (jboolean)JNI_TRUE);
    nb->call("setContentTitle", jenv->env()->NewStringUTF(title));
    nb->call("setContentText", jenv->env()->NewStringUTF(text));
    nb->call("setSmallIcon", getIconIndex(jenv));
    jvalue notification = nb->call("getNotification");
    if (notification.l)
    {
        std::shared_ptr<JavaLocalRef<jobject> > notif(jenv->createRef(notification.l));
        std::shared_ptr<JavaObject> nm = jenv->createJO(notificationManager_->get(),
                                                         &JavaObjects::NotificationManager_Desc);
        nm->call("notify_0", jenv->env()->NewStringUTF(tag), id, notif->get());

        LOG(ANDROID_LOG_INFO, "Notification created succesfully");
    }
    else
    {
        LOG(ANDROID_LOG_ERROR, "Unable to create Notification object");
    }
}

void NotificationManager::cancel(int id)
{
    std::shared_ptr<AttachedJENV> jenv(new AttachedJENV());
    if (!jenv->attached())
    {
        LOG(ANDROID_LOG_ERROR, "Unable to get VM");
        return;
    }

    if (!initializeStatics(jenv))
    {
        LOG(ANDROID_LOG_ERROR, "Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nm = jenv->createJO(notificationManager_->get(),
                                                     &JavaObjects::NotificationManager_Desc);
    nm->call("cancel", id);

    LOG(ANDROID_LOG_INFO, "Notification id:%d canceled succesfully", id);
}

void NotificationManager::cancel(const char *tag, int id)
{
    std::shared_ptr<AttachedJENV> jenv(new AttachedJENV());
    if (!jenv->attached())
    {
        LOG(ANDROID_LOG_ERROR, "Unable to get VM");
        return;
    }

    if (!initializeStatics(jenv))
    {
        LOG(ANDROID_LOG_ERROR, "Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nm = jenv->createJO(notificationManager_->get(),
                                                     &JavaObjects::NotificationManager_Desc);
    nm->call("cancel_1", jenv->env()->NewStringUTF(tag), id);

    LOG(ANDROID_LOG_INFO, "Notification tag:'%s' id:%d canceled succesfully", tag, id);
}

void NotificationManager::cancelAll()
{
    std::shared_ptr<AttachedJENV> jenv(new AttachedJENV());
    if (!jenv->attached())
    {
        LOG(ANDROID_LOG_ERROR, "Unable to get VM");
        return;
    }

    if (!initializeStatics(jenv))
    {
        LOG(ANDROID_LOG_ERROR, "Unable to init internal objects");
        return;
    }

    std::shared_ptr<JavaObject> nm = jenv->createJO(notificationManager_->get(),
                                                     &JavaObjects::NotificationManager_Desc);
    nm->call("cancelAll");

    LOG(ANDROID_LOG_INFO, "All notification canceled succesfully");
}
