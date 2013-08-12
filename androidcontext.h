#ifndef ANDROIDCONTEXT_H
#define ANDROIDCONTEXT_H

#include "javaobject.h"

#ifdef __EXCEPTIONS_SUPPORT__
#include <stdexcept>
#endif

/****************************************************/
class ClassLoader
{
public:
    ClassLoader(jobject classLoader, jmethodID methodID);

    jclass loadClass(const char *name);

protected:
    friend class AttachedJENV;
    ClassLoader *clone(JNIEnv *env);

private:
    jobject classLoader_;
    jmethodID methodID_;
    JNIEnv *env_;

};

#ifdef __EXCEPTIONS_SUPPORT__

/****************************************************/
class NotAttachedJENV: public std::runtime_error
{
public:
    NotAttachedJENV()
        : std::runtime_error("Attempt to use not attached JNIEnv")
    {
    }
};

#endif

/****************************************************/
class AttachedJENV
{
private:
    JNIEnv *env_;
    bool attached_;
    std::shared_ptr<ClassLoader> classLoader_;

public:    
    AttachedJENV();
    ~AttachedJENV();

    JNIEnv *env();
    bool attached();
    std::shared_ptr<ClassLoader> classLoader();
    void exceptionsHandler(const char *file, int line);

    template<typename T>
    std::shared_ptr<JavaObject_common<T> > createJO(const T &obj, JavaMember *methods, size_t methods_size)
    {
        JavaObject_common<T> *res = 0;
        if (attached())
        {
            res = new JavaObject_common<T>(env_, obj, methods, methods_size);
        }
#ifdef __EXCEPTIONS_SUPPORT__
        else
        {
            throw NotAttachedJENV();
        }
#endif
        return std::shared_ptr<JavaObject_common<T> >(res);
    }

    template<typename T>
    std::shared_ptr<JavaObject_common<T> > createJO(const T &obj, JavaObjectDesc *desc)
    {
        JavaObject_common<T> *res = 0;
        if (attached())
        {
            res = new JavaObject_common<T>(env_, obj, desc);
        }
#ifdef __EXCEPTIONS_SUPPORT__
        else
        {
            throw NotAttachedJENV();
        }
#endif
        return std::shared_ptr<JavaObject_common<T> >(res);
    }

    template<typename T>
    std::shared_ptr<JavaLocalRef<T> > createRef(const T &obj)
    {
        JavaLocalRef<T> *res = 0;
        if (attached())
        {
            res = new JavaLocalRef<T>(env_, obj);
        }
#ifdef __EXCEPTIONS_SUPPORT__
        else
        {
            throw NotAttachedJENV();
        }
#endif
        return std::shared_ptr<JavaLocalRef<T> >(res);
    }

    template<typename T>
    std::shared_ptr<JavaGlobalRef<T> > createGlobalRef(const T &obj)
    {
        JavaGlobalRef<T> *res = 0;
        if (attached())
        {
            res = new JavaGlobalRef<T>(env_, obj);
        }
#ifdef __EXCEPTIONS_SUPPORT__
        else
        {
            throw NotAttachedJENV();
        }
#endif
        return std::shared_ptr<JavaGlobalRef<T> >(res);
    }

};

/****************************************************/
class AndroidContext
{
protected:
    AndroidContext();

public:
    static AndroidContext *instance();

    jobject activity();
    bool initialize(JavaVM *jvm);

    ClassLoader *classLoader();

protected:
    friend class AttachedJENV;
    JavaVM *jvm();

private:
    JavaVM *jvm_;
    jclass qtNativeClass_;
    jobject qtActivity_;
    ClassLoader *classLoader_;

};

#endif // ANDROIDCONTEXT_H
