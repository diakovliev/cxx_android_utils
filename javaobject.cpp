#include <android/log.h>

#include "javaobject.h"

#define LOG(L,F, ...) __android_log_print(L, "JavaObject", F, ## __VA_ARGS__ )

/************************ jobject *********************************/
template<>
JavaMethod *JavaObject_common<jobject>::findMethod(const char *method_name)
{
    JavaMethod *method = 0;
    for (size_t i = 0; i < methods_size_; ++i)
    {
        if (!strcmp(methods_[i].uniq_name, method_name))
        {
            method = &methods_[i];
            LOG(ANDROID_LOG_INFO, ">> JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } found",
                method->id, method->type, method->flags, method->uniq_name, method->name, method->sig);
            break;
        }
    }
    if (method && !method->id)
    {
        jclass clazz = env_->GetObjectClass(obj_);
        while (clazz && !method->id)
        {
            method->id = env_->GetMethodID(clazz, method->name, method->sig);
            if (!method->id)
            {
                LOG(ANDROID_LOG_WARN, ">> No method with name: %s trying superclass", method_name);
                env_->ExceptionClear();
                /* try to find in superclass */
                clazz = env_->GetSuperclass(clazz);
            }
            else
            {
                LOG(ANDROID_LOG_INFO, ">> JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
                    method->id, method->type, method->flags, method->uniq_name, method->name, method->sig);
            }
        }
    }
    if (method && !method->id)
    {
        method = 0;
    }
    if (!method)
    {
        LOG(ANDROID_LOG_ERROR, ">> No method with name: %s", method_name);
    }
    return method;
}

template<>
jobject JavaObject_common<jobject>::call(const char *method_name, ...)
{
    va_list ap;
    va_start(ap,method_name);

    jobject result = 0;

    JavaMethod *method = JavaObject_common<jobject>::findMethod(method_name);
    if (method)
    {
        switch(method->type)
        {
        case Void:
            env_->CallVoidMethodV(obj_, method->id, ap);
        break;
        case Object:
            result = env_->CallObjectMethodV(obj_, method->id, ap);
        break;
        default:;
        }
    }

    va_end(ap);

    return result;
}

/************************ jclass *********************************/
template<>
JavaMethod *JavaObject_common<jclass>::findMethod(const char *method_name)
{
    JavaMethod *method = 0;
    for (size_t i = 0; i < methods_size_; ++i)
    {
        if (!strcmp(methods_[i].uniq_name, method_name))
        {
            method = &methods_[i];
            LOG(ANDROID_LOG_INFO, ">> JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } found",
                method->id, method->type, method->flags, method->uniq_name, method->name, method->sig);
            break;
        }
    }
    if (method && !method->id)
    {
        if (!(method->flags & Constructor))
        {
            method->id = env_->GetStaticMethodID(obj_, method->name, method->sig);
            LOG(ANDROID_LOG_INFO, ">> JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
                method->id, method->type, method->flags, method->uniq_name, method->name, method->sig);
        }
        else
        {
            method->id = env_->GetMethodID(obj_, method->name, method->sig);
            LOG(ANDROID_LOG_INFO, ">> JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
                method->id, method->type, method->flags, method->uniq_name, method->name, method->sig);
        }
    }
    if (method && !method->id)
    {
        method = 0;
    }
    if (!method)
    {
        LOG(ANDROID_LOG_ERROR, ">> No method with name: %s", method_name);
    }
    return method;
}

template<>
jobject JavaObject_common<jclass>::call(const char *method_name, ...)
{
    va_list ap;
    va_start(ap,method_name);

    jobject result = 0;

    JavaMethod *method = JavaObject_common<jclass>::findMethod(method_name);
    if (method)
    {
        if (!(method->flags & Constructor))
        {
            switch(method->type)
            {
            case Void:
                env_->CallStaticVoidMethodV(obj_, method->id, ap);
            break;
            case Object:
                result = env_->CallStaticObjectMethodV(obj_, method->id, ap);
            break;
            default:;
            }
        }
        else
        {
            result = env_->NewObjectV(obj_, method->id, ap);
        }
    }

    va_end(ap);

    return result;
}
