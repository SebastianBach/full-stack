#ifndef CPP_TESTING
#define CPP_TESTING

#include "result.hpp"
#include <functional>
#include <iostream>

namespace cpp
{
namespace testing
{
bool run_test(const char*                                      test,
              const std::function<cpp::result::result_void()>& func)
{
    const auto res = func();

    if (res.valid())
    {
        std::cout << "Test Case: \"" << test << "\" run successfully.\n";
    }
    else
    {
        std::cout << "Test Case: \"" << test << "\" found an error: ";
        std::cout << res.err_msg() << "\n";
        return false;
    }

    return true;
}

inline cpp::result::result_void
check(const char* check, bool ok,
      const std::source_location& location = std::source_location::current())
{
    if (ok)
        return cpp::result::SUCCESS;

    return cpp::result::report_error(check, location);
}

#define CHECK_(MSG, ARG) if (!(ARG)) return cpp::result::report_error(MSG);

} // namespace testing
} // namespace cpp

#endif
