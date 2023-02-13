#include "lib.h"

namespace func_lib
{
const char* version()
{
    return "0.1.0";
}
const char* date()
{
    return __DATE__;
}
} // namespace func_lib
