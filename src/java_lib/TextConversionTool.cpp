#include "TextConversionTool.h"
#include "text_conversion_constexpr.h"
#include <jni.h>
#include <span>

JNIEXPORT void JNICALL Java_TextConversionTool_textConversionC(JNIEnv* env,
                                                               jobject,
                                                               jbyteArray buf,
                                                               jint       size)
{
    jboolean isCopy;
    char*    nativeBuf =
        reinterpret_cast<char*>(env->GetByteArrayElements(buf, &isCopy));

    std::span<char> temp(nativeBuf, static_cast<size_t>(size));
    text_conversion_constexpr::convert_to_title_case(temp);

    env->ReleaseByteArrayElements(buf, reinterpret_cast<jbyte*>(nativeBuf), 0);
}
