#pragma once

#include <string>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif



#ifdef __cplusplus
extern "C"
{
#endif

    EXPORT void title_case(char* text);

    EXPORT const char* version();

#ifdef __cplusplus
}
#endif
