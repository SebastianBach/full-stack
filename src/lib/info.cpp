#include "text_conversion.h"

namespace text_conversion
{

const char* version()
{
    return "0.1.1";
}

const char* date()
{
    return __DATE__;
}

} // namespace text_conversion
