#ifndef JAVAOBJECT_H
#define JAVAOBJECT_H

#include <jni.h>
#include <cstddef>
#include <memory>
#include <cassert>

/****************************************************/
enum JavaMethodType {
    Void,
    Object
};

enum JavaMethodFlags {
    Static = 0x01,
    Nonvirtual = 0x02,
    Constructor = 0x04
};

struct JavaMethod {
    jmethodID id;
    JavaMethodType type;
    unsigned flags;
    const char *uniq_name;
    const char *name;
    const char *sig;
};

struct JavaObjectDesc {
    JavaMethod *methods;
    size_t msize;
};

template<typename T>
class JavaObject_common {
public:

    /* regular constructor */
    JavaObject_common(JNIEnv *env, const T &obj, JavaMethod *methods, size_t methods_size)
        : obj_(obj)
        , methods_(methods)
        , methods_size_(methods_size)
        , env_(env)
    {
    }

    JavaObject_common(JNIEnv *env, const T &obj, JavaObjectDesc *desc)
        : obj_(obj)
        , methods_(desc->methods)
        , methods_size_(desc->msize)
        , env_(env)
    {
    }

    virtual ~JavaObject_common()
    {
    }

    /* method_name is uniq_name in methods table */
    jobject call(const char *method_name, ...);

protected:
    JavaMethod *findMethod(const char *method_name);

private:
    T obj_;
    JavaMethod *methods_;
    size_t methods_size_;
    JNIEnv *env_;
};

/************************ jobject *********************************/
template<>
JavaMethod *JavaObject_common<jobject>::findMethod(const char *method_name);
template<>
jobject JavaObject_common<jobject>::call(const char *method_name, ...);

/************************ jclass *********************************/
template<>
JavaMethod *JavaObject_common<jclass>::findMethod(const char *method_name);
template<>
jobject JavaObject_common<jclass>::call(const char *method_name, ...);

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
