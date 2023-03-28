#include "text_conversion.h"
#include "text_conversion_constexpr.h"

namespace text_conversion
{

const char* version()
{
    return text_conversion_constexpr::version;
}

const char* date()
{
    return __DATE__;
}

} // namespace text_conversion
