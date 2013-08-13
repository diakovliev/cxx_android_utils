#ifndef JAVAOBJECT_H
#define JAVAOBJECT_H

#include <jni.h>
#include <cstddef>
#include <memory>
#include <cassert>
#include <map>
#include <string>

/****************************************************/
#if 0
typedef union jvalue {
    jboolean    z;
    jbyte       b;
    jchar       c;
    jshort      s;
    jint        i;
    jlong       j;
    jfloat      f;
    jdouble     d;
    jobject     l;
} jvalue;
#endif

enum JavaMethodType {
    Unknown,
    Void,
    Boolean,
    Byte,
    Char,
    Short,
    Int,
    Long,
    Float,
    Double,
    Object
};

enum JavaMethodFlags {
    Constructor = 0x0001,
    Private 	= 0x0002,
    Protected 	= 0x0004,
    Public 		= 0x0008,
    Static 		= 0x0010,
    Final 		= 0x0020,
    Native 		= 0x0040,
    Abstract	= 0x0080,
    /*-----------------*/
    Function	= 0x4000,
    Field		= 0x8000
};

union JavaMemberId {
    jmethodID functionid;
    jfieldID fieldid;
};

struct JavaMember {
    JavaMethodType type;
    unsigned flags;
    const char *uniq_name;
    const char *name;
    const char *sig;
};

struct JavaObjectDesc {
    JavaMember *methods;
    size_t msize;
};

template<class T>
class JavaObject_common {
public:

    /* regular constructor */
    JavaObject_common(JNIEnv *env, const T &obj, JavaMember *methods, size_t methods_size)
        : obj_(obj)
        , members_(methods)
        , members_size_(methods_size)
        , env_(env)
        , members_ids_()
    {
    }

    JavaObject_common(JNIEnv *env, const T &obj, JavaObjectDesc *desc)
        : obj_(obj)
        , members_(desc->methods)
        , members_size_(desc->msize)
        , env_(env)
        , members_ids_()
    {
    }

    virtual ~JavaObject_common()
    {
    }

    /* method_name is uniq_name in methods table */
    jvalue call(const char *method_name, ...);

    /* get field */
    jvalue get(const char *field_name);

    /* set field */
    void set(const char *field_name, jvalue value);

protected:
    JavaMember *findMember(const char *member_name);
    JavaMemberId getMemberId(JavaMember *member);

private:
    T obj_;
    JavaMember *members_;
    size_t members_size_;
    JNIEnv *env_;

    typedef std::map<std::string, JavaMemberId> members_ids_map_type;
    members_ids_map_type members_ids_;
};

/************************ jobject *********************************/
template<>
JavaMemberId JavaObject_common<jobject>::getMemberId(JavaMember *member);
template<>
jvalue JavaObject_common<jobject>::call(const char *method_name, ...);
/* get field */
template<>
jvalue JavaObject_common<jobject>::get(const char *field_name);
/* set field */
template<>
void JavaObject_common<jobject>::set(const char *field_name, jvalue value);

/************************ jclass *********************************/
template<>
JavaMemberId JavaObject_common<jclass>::getMemberId(JavaMember *member);
template<>
jvalue JavaObject_common<jclass>::call(const char *method_name, ...);
/* get field */
template<>
jvalue JavaObject_common<jclass>::get(const char *field_name);
/* set field */
template<>
void JavaObject_common<jclass>::set(const char *field_name, jvalue value);

/********************************************************/
typedef JavaObject_common<jobject> JavaObject;
typedef JavaObject_common<jclass> JavaClass;

/********************************************************/

template<class T>
class JavaLocalRef
{
    JNIEnv *env_;
    T ref_;
protected:
    JavaLocalRef(const JavaLocalRef& src) {}

public:
    JavaLocalRef(JNIEnv *env, const T &obj)
        : env_(env)
        , ref_(0)
    {
        ref_ = (T)env_->NewLocalRef((jobject)obj);
    }

    ~JavaLocalRef()
    {
        env_->DeleteLocalRef((jobject)ref_);
    }

    T& get()
    {
        return ref_;
    }
};

/********************************************************/
template<class T>
class JavaGlobalRef
{
    T ref_;
protected:
    JavaGlobalRef(const JavaGlobalRef& src) {}

public:
    JavaGlobalRef(JNIEnv *env, const T &obj)
        : ref_(0)
    {
        ref_ = (T)env->NewGlobalRef((jobject)obj);
    }

    void deleteRef(JNIEnv *env)
    {
        env->DeleteGlobalRef((jobject)ref_);
        ref_ = 0;

    }

    ~JavaGlobalRef()
    {
        /* reference should be deleted before destroy object */
        assert(ref_ == 0);
    }

    T& get()
    {
        return ref_;
    }
};


#endif // JAVAOBJECT_H
