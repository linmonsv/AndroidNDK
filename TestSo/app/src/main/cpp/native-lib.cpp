#include <jni.h>
#include <string>
#include <iostream>
#include <android/log.h>
#define  LOGI(...) __android_log_print(ANDROID_LOG_INFO, "========= Info =========   ", __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "========= Error =========   ", __VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_INFO, "========= Debug =========   ", __VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, "========= Warn =========   ", __VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_testso_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


extern "C" JNIEXPORT void JNICALL
Java_com_example_testso_MainActivity_nativeDownload(
        JNIEnv* env,
        jobject thiz) {
    std::string hello = "Hello from C++";

    LOGD("DEBUG");
    LOGE("ERROR");
    LOGI("INFO");
    LOGW("WARN");

    jcalss jSdkClass = *env->FindClass(env, "com/example/testso/MainActivity");
    if (jSdkClass == 0) {
        LOGE("Unable to find class");
        return;
    }
    jmethodID javaCallback = *env->GetMethodID(env, jSdkClass, "onProgressCallBack", "(JJ)I");
    jint ret = *env->CallIntMethod(env, thiz, javaCallback,1,1);

    return ;
}
