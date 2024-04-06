#include <jni.h>
#include <string>
#include "text_conversion_constexpr.h"


extern "C" JNIEXPORT

jstring JNICALL
Java_com_example_titlecase_MainActivity_titleCase(
        JNIEnv *env,
        jobject /* this */, jstring input) {

    const char* cStr = env->GetStringUTFChars(input, nullptr);
    std::string cppStr(cStr);
    env->ReleaseStringUTFChars(input, cStr);
    text_conversion_constexpr::convert_to_title_case(cppStr);
    return env->NewStringUTF(cppStr.c_str());
}
