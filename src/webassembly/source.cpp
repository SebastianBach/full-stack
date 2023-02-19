#include <iostream>
#include <stdio.h>
#include <emscripten/emscripten.h>
#include "text_conversion_constexpr.h"


// https://developer.mozilla.org/en-US/docs/WebAssembly/C_to_wasm

int main()
{
  std::cout << "init module" << std::endl;
  return 0;
}

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN EMSCRIPTEN_KEEPALIVE void title_case(long int *data, long int length)
{
  std::span<long int> temp(data, length);
  text_conversion_constexpr::convert_to_title_case(temp);
}
