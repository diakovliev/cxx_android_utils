#ifndef ANDROIDCONTEXT_H
#define ANDROIDCONTEXT_H

#include "javaobject.h"

/****************************************************/
class ClassLoader
{
public:
    ClassLoader(jobject classLoader, jmethodID methodID);

    jclass loadClass(const char *name);

    ClassLoader *clone(JNIEnv *env);

private:
    jobject classLoader_;
    jmethodID methodID_;
    JNIEnv *env_;

};

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

    template<typename T>
    JavaObject_common<T> *createJO(const T &obj, JavaMethod *methods, size_t methods_size)
    {
        if (attached())
        {
            JavaObject_common<T> *res = new JavaObject_common<T>(env_, obj, methods, methods_size);
            return res;
        }
        else
        {
            return 0;
        }
    }

    template<typename T>
    JavaObject_common<T> *createJO(const T &obj, JavaObjectDesc *desc)
    {
        if (attached())
        {
            JavaObject_common<T> *res = new JavaObject_common<T>(env_, obj, desc);
            return res;
        }
        else
        {
            return 0;
        }
    }

    ClassLoader *classLoader();

    void exceptionsHandler(const char *file, int line);

    template<typename T>
    JavaLocalRef<T> *createRef(const T &obj)
    {
        JavaLocalRef<T> *res = new JavaLocalRef<T>(env_, obj);
        return res;
    }

    template<typename T>
    JavaGlobalRef<T> *createGlobalRef(const T &obj)
    {
        JavaGlobalRef<T> *res = new JavaGlobalRef<T>(env_, obj);
        return res;
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
