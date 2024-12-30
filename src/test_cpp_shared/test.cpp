
#include "app.hpp"
#include "result.hpp"
#include "testing.hpp"

bool test_result()
{
    {
        // test error
        const std::string err_msg("error message");

        const cpp::result::error err(err_msg);

        if (err.msg() != err_msg)
            return false;
    }

    {
        // test error
        const std::string err_msg("error message");

        const cpp::result::error err("error message");

        if (err.msg() != err_msg)
            return false;
    }

    {
        const auto                     ref = 123;
        const cpp::result::result<int> res{ref};

        if (!res.valid())
            return false;

        if (res.error())
            return false;

        const auto value = res.value();
        if (value != ref)
            return false;

        const auto err_msg = res.err_msg();
        if (err_msg != cpp::result::msg_invalid_call)
            return false;
    }

    {
        const std::string ref{"error message"};

        const cpp::result::error       err{ref};
        const cpp::result::result<int> res{err};

        if (res.valid())
            return false;

        if (!res.error())
            return false;

        const auto err_msg = res.err_msg();
        if (err_msg == cpp::result::msg_invalid_call)
            return false;

        if (err_msg != ref)
            return false;
    }

    {
        if (!cpp::result::SUCCESS.valid())
            return false;

        if (cpp::result::SUCCESS.error())
            return false;

        const auto err_msg = cpp::result::SUCCESS.err_msg();
        if (err_msg != cpp::result::msg_invalid_call)
            return false;
    }

    {
        const std::string ref{"error message"};

        const cpp::result::error err{ref};
        cpp::result::result_void res_err{err};

        if (res_err.valid())
            return false;

        if (!res_err.error())
            return false;

        const auto err_msg = res_err.err_msg();
        if (err_msg != ref)
            return false;
    }

    return true;
}

cpp::result::result_void test_case(bool success)
{
    if (success)
        return cpp::result::SUCCESS;

    return cpp::result::report_error("Expected Failure");
}

cpp::result::result_void test_case_check(bool success)
{
    return cpp::testing::check("Test Case Check", success == true);
}

cpp::result::result_void test_case_check_macro(bool success)
{
    CHECK_("Test Case Macro", success == true);

    return cpp::result::SUCCESS;
}

bool test_testing()
{
    {
        auto alias = std::bind(test_case, true);

        const auto res = cpp::testing::run_test("test_case() success", alias);

        if (!res)
            return false;
    }

    {
        auto alias = std::bind(test_case, false);

        const auto res = cpp::testing::run_test("test_case() failure", alias);

        if (res)
            return false;
    }

    {
        const auto res = cpp::testing::check("Base Check", true);
        if (res.error())
            return false;

        if (!res.valid())
            return true;
    }

    {
        const auto res = cpp::testing::check("Base Check", false);
        if (!res.error())
            return false;

        if (res.valid())
            return true;
    }

    {
        auto alias = std::bind(test_case_check, true);

        const auto res =
            cpp::testing::run_test("test_case_check() success", alias);

        if (!res)
            return false;
    }

    {
        auto alias = std::bind(test_case_check, false);

        const auto res =
            cpp::testing::run_test("test_case_check() failure", alias);

        if (res)
            return false;
    }

    {
        const auto res = test_case_check_macro(true);
        if (res.error())
            return false;

        if (!res.valid())
            return true;
    }

    {
        const auto res = test_case_check_macro(false);
        if (!res.error())
            return false;

        if (res.valid())
            return true;
    }

    return true;
}

int main()
{
    {
        const auto res = test_result();
        if (!res)
            return cpp::app::FAILURE;
    }

    {
        const auto res = test_testing();
        if (!res)
            return cpp::app::FAILURE;
    }

    return cpp::app::SUCCESS;
}
