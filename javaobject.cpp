#include <android/log.h>

#include "javaobject.h"

#define LOG(L,F, ...) __android_log_print(L, "JavaObject", F, ## __VA_ARGS__ )

/************************ jobject *********************************/
template<>
JavaMemberId JavaObject_common<jobject>::getMemberId(JavaMember *member)
{
    JavaMemberId result;
    result.functionid = 0;
    if (member)
    {
        members_ids_map_type::iterator iter = members_ids_.find(member->uniq_name);
        if ( iter == members_ids_.end() )
        {
            jclass clazz = env_->GetObjectClass(obj_);
            while (clazz)
            {
                if (member->flags & Function)
                {
                    result.functionid = env_->GetMethodID(clazz, member->name, member->sig);
                }
                else if (member->flags & Field)
                {
                    result.fieldid = env_->GetFieldID(clazz, member->name, member->sig);
                }
                if (!result.functionid)
                {
                    LOG(ANDROID_LOG_WARN, "No member with name: %s trying superclass", member->name);
                    env_->ExceptionClear();
                    /* try to find in superclass */
                    clazz = env_->GetSuperclass(clazz);
                }
                else
                {
                    LOG(ANDROID_LOG_INFO, "JavaMember: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
                        result.functionid, member->type, member->flags, member->uniq_name, member->name, member->sig);
                    break;
                }
            }
            members_ids_[member->uniq_name] = result;
        }
        else
        {
            result = iter->second;
            LOG(ANDROID_LOG_INFO, "JavaMember: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found in cache",
                result.functionid, member->type, member->flags, member->uniq_name, member->name, member->sig);
        }
    }
    return result;
}

template<>
JavaMember *JavaObject_common<jobject>::findMember(const char *method_name)
{
    JavaMember *member = 0;
    for (size_t i = 0; i < members_size_; ++i)
    {
        if (!strcmp(members_[i].uniq_name, method_name))
        {
            member = &members_[i];
            LOG(ANDROID_LOG_INFO, "JavaMember: { t: %d, f: %d, u: %s, n: %s, s: %s } found",
                member->type, member->flags, member->uniq_name, member->name, member->sig);

            break;
        }
    }

    if (!member)
    {
        LOG(ANDROID_LOG_ERROR, "No method with name: %s", method_name);
    }
    return member;
}

template<>
jvalue JavaObject_common<jobject>::call(const char *method_name, ...)
{
    va_list ap;
    va_start(ap,method_name);

    jvalue result;
    memset(&result, 0, sizeof(result));

    JavaMember *method = JavaObject_common<jobject>::findMember(method_name);
    JavaMemberId id = getMemberId(method);
    if (method && id.functionid)
    {
        if (!(method->flags & Function))
        {
            LOG(ANDROID_LOG_ERROR, "Attempt to use non function member as function (%s)", method_name);
            return result;
        }
        if (method->flags & (Private|Protected))
        {
            LOG(ANDROID_LOG_INFO, "Attempt to call private or protected method (%s)", method_name);
#ifdef __STRICT_ACCESS_CHECKING__
            LOG(ANDROID_LOG_ERROR, "Strict access checking enabled, return null value", method_name);
            return result;
#endif
        }
        switch(method->type)
        {
        case Unknown:
            LOG(ANDROID_LOG_ERROR, "Unsupported method type (%s)", method_name);
        break;
        case Void:
            env_->CallVoidMethodV(obj_, id.functionid, ap);
        break;
        case Object:
            result.l = env_->CallObjectMethodV(obj_, id.functionid, ap);
        break;
		case Boolean:
            result.z = env_->CallBooleanMethodV(obj_, id.functionid, ap);
		break;
        case Byte:
            result.b = env_->CallByteMethodV(obj_, id.functionid, ap);
        break;
        case Char:
            result.c = env_->CallCharMethodV(obj_, id.functionid, ap);
        break;
        case Short:
            result.s = env_->CallShortMethodV(obj_, id.functionid, ap);
        break;
        case Int:
            result.i = env_->CallIntMethodV(obj_, id.functionid, ap);
        break;
        case Long:
            result.j = env_->CallLongMethodV(obj_, id.functionid, ap);
        break;
        case Float:
            result.f = env_->CallFloatMethodV(obj_, id.functionid, ap);
        break;
        case Double:
            result.d = env_->CallDoubleMethodV(obj_, id.functionid, ap);
        break;
        default:;
        }
    }

    va_end(ap);

    return result;
}

/* get field */
template<>
jvalue JavaObject_common<jobject>::get(const char *field_name)
{
    jvalue result;
    memset(&result, 0, sizeof(result));

    JavaMember *field = JavaObject_common<jobject>::findMember(field_name);
    JavaMemberId id = getMemberId(field);
    if (field && id.fieldid)
    {
        if (!(field->flags & Field))
        {
            LOG(ANDROID_LOG_ERROR, "Attempt to use non field member as field (%s)", field_name);
            return result;
        }
        if (field->flags & (Private|Protected))
        {
            LOG(ANDROID_LOG_INFO, "Attempt to access to private or protected field (%s)", field_name);
#ifdef __STRICT_ACCESS_CHECKING__
            LOG(ANDROID_LOG_ERROR, "Strict access checking enabled, return null value", field_name);
            return result;
#endif
        }
        switch(field->type)
        {
        case Unknown:
            LOG(ANDROID_LOG_ERROR, "Unsupported field type (%s)", field_name);
        break;
        case Object:
            result.l = env_->GetObjectField(obj_, id.fieldid);
        break;
        case Boolean:
            result.z = env_->GetBooleanField(obj_, id.fieldid);
        break;
        case Byte:
            result.b = env_->GetByteField(obj_, id.fieldid);
        break;
        case Char:
            result.c = env_->GetCharField(obj_, id.fieldid);
        break;
        case Short:
            result.s = env_->GetShortField(obj_, id.fieldid);
        break;
        case Int:
            result.i = env_->GetIntField(obj_, id.fieldid);
        break;
        case Long:
            result.j = env_->GetLongField(obj_, id.fieldid);
        break;
        case Float:
            result.f = env_->GetFloatField(obj_, id.fieldid);
        break;
        case Double:
            result.d = env_->GetDoubleField(obj_, id.fieldid);
        break;
        default:;
        }
    }

    return result;
}

/* set field */
template<>
void JavaObject_common<jobject>::set(const char *field_name, jvalue value)
{
    JavaMember *field = JavaObject_common<jobject>::findMember(field_name);
    JavaMemberId id = getMemberId(field);
    if (field && id.fieldid)
    {
        if (!(field->flags & Field))
        {
            LOG(ANDROID_LOG_ERROR, "Attempt to use non field member as field (%s)", field_name);
            return;
        }
        if (field->flags & (Private|Protected))
        {
            LOG(ANDROID_LOG_INFO, "Attempt to access to private or protected field (%s)", field_name);
#ifdef __STRICT_ACCESS_CHECKING__
            LOG(ANDROID_LOG_ERROR, "Strict access checking enabled, return null value", field_name);
            return;
#endif
        }
        switch(field->type)
        {
        case Unknown:
            LOG(ANDROID_LOG_ERROR, "Unsupported field type (%s)", field_name);
        break;
        case Object:
            env_->SetObjectField(obj_, id.fieldid, value.l);
        break;
        case Boolean:
            env_->SetBooleanField(obj_, id.fieldid, value.z);
        break;
        case Byte:
            env_->SetByteField(obj_, id.fieldid, value.b);
        break;
        case Char:
            env_->SetCharField(obj_, id.fieldid, value.c);
        break;
        case Short:
            env_->SetShortField(obj_, id.fieldid, value.s);
        break;
        case Int:
            env_->SetIntField(obj_, id.fieldid, value.i);
        break;
        case Long:
            env_->SetLongField(obj_, id.fieldid, value.j);
        break;
        case Float:
            env_->SetFloatField(obj_, id.fieldid, value.f);
        break;
        case Double:
            env_->SetDoubleField(obj_, id.fieldid, value.d);
        break;
        default:;
        }
    }
}

/************************ jclass *********************************/
template<>
JavaMemberId JavaObject_common<jclass>::getMemberId(JavaMember *member)
{
    JavaMemberId result;
    result.functionid = 0;
    if (member)
    {
        members_ids_map_type::iterator iter = members_ids_.find(member->uniq_name);
        if ( iter == members_ids_.end() )
        {
            if (!(member->flags & Constructor))
            {
                if (member->flags & Function)
                {
                    result.functionid = env_->GetStaticMethodID(obj_, member->name, member->sig);
                    LOG(ANDROID_LOG_INFO, "JavaMember: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
                        result.functionid, member->type, member->flags, member->uniq_name, member->name, member->sig);
                }
                if (member->flags & Field)
                {
                    result.fieldid = env_->GetStaticFieldID(obj_, member->name, member->sig);
                    LOG(ANDROID_LOG_INFO, "JavaMember: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
                        result.fieldid, member->type, member->flags, member->uniq_name, member->name, member->sig);
                }
            }
            else
            {
                result.functionid = env_->GetMethodID(obj_, member->name, member->sig);
                LOG(ANDROID_LOG_INFO, "JavaMember: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found",
                    result.functionid, member->type, member->flags, member->uniq_name, member->name, member->sig);
            }
            members_ids_[member->uniq_name] = result;
        }
        else
        {
            result = iter->second;
            LOG(ANDROID_LOG_INFO, "JavaMember: { id: %p, t: %d, f: %d, u: %s, n: %s, s: %s } id found in cache",
                result.functionid, member->type, member->flags, member->uniq_name, member->name, member->sig);
        }
    }
    return result;
}

template<>
JavaMember *JavaObject_common<jclass>::findMember(const char *member_name)
{
    JavaMember *member = 0;
    for (size_t i = 0; i < members_size_; ++i)
    {
        if (!strcmp(members_[i].uniq_name, member_name))
        {
            member = &members_[i];
            LOG(ANDROID_LOG_INFO, "JavaMember: { t: %d, f: %d, u: %s, n: %s, s: %s } found",
                member->type, member->flags, member->uniq_name, member->name, member->sig);
            break;
        }
    }
    if (!member)
    {
        LOG(ANDROID_LOG_ERROR, "No member with name: %s", member_name);
    }
    return member;
}

template<>
jvalue JavaObject_common<jclass>::call(const char *method_name, ...)
{
    va_list ap;
    va_start(ap,method_name);

    jvalue result;
    memset(&result, 0, sizeof(result));

    JavaMember *method = JavaObject_common<jclass>::findMember(method_name);
    JavaMemberId id = getMemberId(method);
    if (method && id.functionid)
    {
        if (!(method->flags & Constructor))
        {
            if (!(method->flags & Function))
            {
                LOG(ANDROID_LOG_ERROR, "Attempt to use non function member as function (%s)", method_name);
                return result;
            }
            if (method->flags & (Private|Protected))
            {
                LOG(ANDROID_LOG_INFO, "Attempt to call private or protected method (%s)", method_name);
#ifdef __STRICT_ACCESS_CHECKING__
                LOG(ANDROID_LOG_ERROR, "Strict access checking enabled, return null value", method_name);
                return result;
#endif
            }
            switch(method->type)
            {
            case Unknown:
                LOG(ANDROID_LOG_ERROR, "Unsupported method type (%s)", method_name);
            break;
            case Void:
                env_->CallStaticVoidMethodV(obj_, id.functionid, ap);
            break;
            case Object:
                result.l = env_->CallStaticObjectMethodV(obj_, id.functionid, ap);
            break;
            case Boolean:
                result.z = env_->CallStaticBooleanMethodV(obj_, id.functionid, ap);
            break;
            case Byte:
                result.b = env_->CallStaticByteMethodV(obj_, id.functionid, ap);
            break;
            case Char:
                result.c = env_->CallStaticCharMethodV(obj_, id.functionid, ap);
            break;
            case Short:
                result.s = env_->CallStaticShortMethodV(obj_, id.functionid, ap);
            break;
            case Int:
                result.i = env_->CallStaticIntMethodV(obj_, id.functionid, ap);
            break;
            case Long:
                result.j = env_->CallStaticLongMethodV(obj_, id.functionid, ap);
            break;
            case Float:
                result.f = env_->CallStaticFloatMethodV(obj_, id.functionid, ap);
            break;
            case Double:
                result.d = env_->CallStaticDoubleMethodV(obj_, id.functionid, ap);
            break;
            default:;
            }
        }
        else
        {
            if (method->flags & (Private|Protected))
            {
                if (!(method->flags & Function))
                {
                    LOG(ANDROID_LOG_ERROR, "Attempt to use non function member as function (%s)", method_name);
                    return result;
                }
                LOG(ANDROID_LOG_INFO, "Attempt to call private or protected constructor (%s)", method_name);
#ifdef __STRICT_ACCESS_CHECKING__
                LOG(ANDROID_LOG_ERROR, "Strict access checking enabled, return null value", method_name);
                return result;
#endif
            }
            result.l = env_->NewObjectV(obj_, id.functionid, ap);
        }
    }

    va_end(ap);

    return result;
}

/* get field */
template<>
jvalue JavaObject_common<jclass>::get(const char *field_name)
{
    jvalue result;
    memset(&result, 0, sizeof(result));

    JavaMember *field = JavaObject_common<jclass>::findMember(field_name);
    JavaMemberId id = getMemberId(field);
    if (field && id.fieldid)
    {
        if (!(field->flags & Field))
        {
            LOG(ANDROID_LOG_ERROR, "Attempt to use non field member as field (%s)", field_name);
            return result;
        }
        if (field->flags & (Private|Protected))
        {
            LOG(ANDROID_LOG_INFO, "Attempt to access to private or protected field (%s)", field_name);
#ifdef __STRICT_ACCESS_CHECKING__
            LOG(ANDROID_LOG_ERROR, "Strict access checking enabled, return null value", field_name);
            return result;
#endif
        }
        switch(field->type)
        {
        case Unknown:
            LOG(ANDROID_LOG_ERROR, "Unsupported field type (%s)", field_name);
        break;
        case Object:
            result.l = env_->GetStaticObjectField(obj_, id.fieldid);
        break;
        case Boolean:
            result.z = env_->GetStaticBooleanField(obj_, id.fieldid);
        break;
        case Byte:
            result.b = env_->GetStaticByteField(obj_, id.fieldid);
        break;
        case Char:
            result.c = env_->GetStaticCharField(obj_, id.fieldid);
        break;
        case Short:
            result.s = env_->GetStaticShortField(obj_, id.fieldid);
        break;
        case Int:
            result.i = env_->GetStaticIntField(obj_, id.fieldid);
        break;
        case Long:
            result.j = env_->GetStaticLongField(obj_, id.fieldid);
        break;
        case Float:
            result.f = env_->GetStaticFloatField(obj_, id.fieldid);
        break;
        case Double:
            result.d = env_->GetStaticDoubleField(obj_, id.fieldid);
        break;
        default:;
        }
    }

    return result;
}

/* set field */
template<>
void JavaObject_common<jclass>::set(const char *field_name, jvalue value)
{
    JavaMember *field = JavaObject_common<jclass>::findMember(field_name);
    JavaMemberId id = getMemberId(field);
    if (field && id.fieldid)
    {
        if (!(field->flags & Field))
        {
            LOG(ANDROID_LOG_ERROR, "Attempt to use non field member as field (%s)", field_name);
            return;
        }
        if (field->flags & (Private|Protected))
        {
            LOG(ANDROID_LOG_INFO, "Attempt to access to private or protected field (%s)", field_name);
#ifdef __STRICT_ACCESS_CHECKING__
            LOG(ANDROID_LOG_ERROR, "Strict access checking enabled, return null value", field_name);
            return;
#endif
        }
        switch(field->type)
        {
        case Unknown:
            LOG(ANDROID_LOG_ERROR, "Unsupported field type (%s)", field_name);
        break;
        case Object:
            env_->SetStaticObjectField(obj_, id.fieldid, value.l);
        break;
        case Boolean:
            env_->SetStaticBooleanField(obj_, id.fieldid, value.z);
        break;
        case Byte:
            env_->SetStaticByteField(obj_, id.fieldid, value.b);
        break;
        case Char:
            env_->SetStaticCharField(obj_, id.fieldid, value.c);
        break;
        case Short:
            env_->SetStaticShortField(obj_, id.fieldid, value.s);
        break;
        case Int:
            env_->SetStaticIntField(obj_, id.fieldid, value.i);
        break;
        case Long:
            env_->SetStaticLongField(obj_, id.fieldid, value.j);
        break;
        case Float:
            env_->SetStaticFloatField(obj_, id.fieldid, value.f);
        break;
        case Double:
            env_->SetStaticDoubleField(obj_, id.fieldid, value.d);
        break;
        default:;
        }
    }
}
