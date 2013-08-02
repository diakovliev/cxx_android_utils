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
            LOG(ANDROID_LOG_INFO, "JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } found",
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
                LOG(ANDROID_LOG_WARN, "No method with name: %s trying superclass", method_name);
                env_->ExceptionClear();
                /* try to find in superclass */
                clazz = env_->GetSuperclass(clazz);
            }
            else
            {
                LOG(ANDROID_LOG_INFO, "JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
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
        LOG(ANDROID_LOG_ERROR, "No method with name: %s", method_name);
    }
    return method;
}

template<>
jvalue JavaObject_common<jobject>::call(const char *method_name, ...)
{
    va_list ap;
    va_start(ap,method_name);

    jvalue result;
    memset(&result, 0, sizeof(result));

    JavaMethod *method = JavaObject_common<jobject>::findMethod(method_name);
    if (method)
    {
        if (method->flags & (Private|Protected))
        {
            LOG(ANDROID_LOG_INFO, "Attempt to call private or protected method (%s)", method_name);
        }
        switch(method->type)
        {
        case Unknown:
            LOG(ANDROID_LOG_ERROR, "Unsupported method type (%s)", method_name);
        break;
        case Void:
            env_->CallVoidMethodV(obj_, method->id, ap);
        break;
        case Object:
            result.l = env_->CallObjectMethodV(obj_, method->id, ap);
        break;
		case Boolean:
            result.z = env_->CallBooleanMethodV(obj_, method->id, ap);
		break;
        case Byte:
            result.b = env_->CallByteMethodV(obj_, method->id, ap);
        break;
        case Char:
            result.c = env_->CallCharMethodV(obj_, method->id, ap);
        break;
        case Short:
            result.s = env_->CallShortMethodV(obj_, method->id, ap);
        break;
        case Int:
            result.i = env_->CallIntMethodV(obj_, method->id, ap);
        break;
        case Long:
            result.j = env_->CallLongMethodV(obj_, method->id, ap);
        break;
        case Float:
            result.f = env_->CallFloatMethodV(obj_, method->id, ap);
        break;
        case Double:
            result.d = env_->CallDoubleMethodV(obj_, method->id, ap);
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
            LOG(ANDROID_LOG_INFO, "JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } found",
                method->id, method->type, method->flags, method->uniq_name, method->name, method->sig);
            break;
        }
    }
    if (method && !method->id)
    {
        if (!(method->flags & Constructor))
        {
            method->id = env_->GetStaticMethodID(obj_, method->name, method->sig);
            LOG(ANDROID_LOG_INFO, "JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
                method->id, method->type, method->flags, method->uniq_name, method->name, method->sig);
        }
        else
        {
            method->id = env_->GetMethodID(obj_, method->name, method->sig);
            LOG(ANDROID_LOG_INFO, "JavaMethod: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
                method->id, method->type, method->flags, method->uniq_name, method->name, method->sig);
        }
    }
    if (method && !method->id)
    {
        method = 0;
    }
    if (!method)
    {
        LOG(ANDROID_LOG_ERROR, "No method with name: %s", method_name);
    }
    return method;
}

template<>
jvalue JavaObject_common<jclass>::call(const char *method_name, ...)
{
    va_list ap;
    va_start(ap,method_name);

    jvalue result;
    memset(&result, 0, sizeof(result));

    JavaMethod *method = JavaObject_common<jclass>::findMethod(method_name);
    if (method)
    {
        if (!(method->flags & Constructor))
        {
            if (method->flags & (Private|Protected))
            {
                LOG(ANDROID_LOG_INFO, "Attempt to call private or protected method (%s)", method_name);
            }
            switch(method->type)
            {
            case Unknown:
                LOG(ANDROID_LOG_ERROR, "Unsupported method type (%s)", method_name);
            break;
            case Void:
                env_->CallStaticVoidMethodV(obj_, method->id, ap);
            break;
            case Object:
                result.l = env_->CallStaticObjectMethodV(obj_, method->id, ap);
            break;
            case Boolean:
                result.z = env_->CallStaticBooleanMethodV(obj_, method->id, ap);
            break;
            case Byte:
                result.b = env_->CallStaticByteMethodV(obj_, method->id, ap);
            break;
            case Char:
                result.c = env_->CallStaticCharMethodV(obj_, method->id, ap);
            break;
            case Short:
                result.s = env_->CallStaticShortMethodV(obj_, method->id, ap);
            break;
            case Int:
                result.i = env_->CallStaticIntMethodV(obj_, method->id, ap);
            break;
            case Long:
                result.j = env_->CallStaticLongMethodV(obj_, method->id, ap);
            break;
            case Float:
                result.f = env_->CallStaticFloatMethodV(obj_, method->id, ap);
            break;
            case Double:
                result.d = env_->CallStaticDoubleMethodV(obj_, method->id, ap);
            break;
            default:;
            }
        }
        else
        {
            if (method->flags & (Private|Protected))
            {
                LOG(ANDROID_LOG_INFO, "Attempt to call private or protected constructor (%s)", method_name);
            }
            result.l = env_->NewObjectV(obj_, method->id, ap);
        }
    }

    va_end(ap);

    return result;
}
