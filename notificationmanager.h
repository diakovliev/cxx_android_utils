#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "androidcontext.h"

class NotificationManager
{
public:
    NotificationManager();
    virtual ~NotificationManager();

    void notify(int id, const char *title, const char *text);
    void notify(const char *tag, int id, const char *title, const char *text);
    void cancel(int id);
    void cancel(const char *tag, int id);
    void cancelAll();

    static void freeJavaResources(std::weak_ptr<AttachedJENV> jvm_weak);

private:
    static bool getJavaNotificationManager(std::weak_ptr<AttachedJENV> jvm_weak);
    static bool createJavaNotificationBuilder(std::weak_ptr<AttachedJENV> jvm_weak);
    static bool initializeStatics(std::weak_ptr<AttachedJENV> jvm_weak);

private:
    static JavaGlobalRef<jobject> *notificationManager_;
    static JavaGlobalRef<jobject> *notificationBuilder_;

};

#endif // NOTIFICATIONMANAGER_H
