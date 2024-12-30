#ifndef CPP_RESULT
#define CPP_RESULT

#include <source_location>
#include <sstream>
#include <string>
#include <variant>

namespace cpp
{
namespace result
{
class error
{
public:
    error(const char* err) : m_msg(err) {}
    error(const std::string& err) : m_msg(err) {}

    const std::string& msg() const
    {
        return m_msg;
    }

private:
    const std::string m_msg;
};

static const std::string msg_invalid_call{"Invalid call of err_msg()."};

template <typename T> class result
{
public:
    static_assert(!std::is_same<T, cpp::result::error>::value,
                  "T cannot be of type cpp::result::error");

    result(const T& data) : m_value(data) {}

    result(const error& err) : m_value(err) {}

    bool error() const noexcept
    {
        return std::holds_alternative<cpp::result::error>(m_value);
    }

    bool valid() const noexcept
    {
        return !error();
    }

    const T& value() const
    {
        static_assert(!std::is_same<T, std::monostate>::value,
                      "value() cannot be called on result_void");

        return std::get<T>(m_value);
    }

    const std::string& err_msg() const
    {
        if (!error())
            return msg_invalid_call;

        return std::get<cpp::result::error>(m_value).msg();
    }

private:
    const std::variant<T, cpp::result::error> m_value;
};

using result_void = result<std::monostate>;

static const result_void SUCCESS{std::monostate{}};

cpp::result::error report_error(
    const char*                 msg,
    const std::source_location& location = std::source_location::current())
{
    std::ostringstream error_msg;
    error_msg << msg << " [file: " << location.file_name()
              << ", function: " << location.function_name()
              << ", line: " << location.line() << "]";

    return error_msg.str();
}

} // namespace result
} // namespace cpp

#endif