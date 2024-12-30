#include <script.h>

#include <app.hpp>
#include <testing.hpp>

void print(const char* msg)
{
    std::cout << msg << std::endl;
}

cpp::result::result_void test_parser()
{
    script::command cmd;
    std::string     operand;

    script::parse("# this is some comment", cmd, operand);
    CHECK_("Check Commment", cmd == script::command::COMMENT);

    script::parse("text this is some test text", cmd, operand);
    CHECK_("Check Text", cmd == script::command::TEXT);

    script::parse("process", cmd, operand);
    CHECK_("Check Process", cmd == script::command::PROCESS);

    script::parse("print", cmd, operand);
    CHECK_("Check Print", cmd == script::command::PRINT);

    script::parse("load file", cmd, operand);
    CHECK_("Check Load", cmd == script::command::LOAD);

    script::parse("save file", cmd, operand);
    CHECK_("Check Save", cmd == script::command::SAVE);

    return cpp::result::SUCCESS;
}

cpp::result::result_void test_engine()
{
    script::engine eng{print};

    eng.run(script::command::TEXT, "test text");

    CHECK_("Check Test", eng.get_memory() == "test text");

    eng.run(script::command::PROCESS, "");

    CHECK_("Check Process", eng.get_memory() == "Test Text");

    eng.run(script::command::SAVE, "_current_content.txt");

    eng.run(script::command::TEXT, "nothing");

    CHECK_("Check Save", eng.get_memory() == "nothing");

    eng.run(script::command::LOAD, "_current_content.txt");

    CHECK_("Check Load", eng.get_memory() == "Test Text");

    const auto res = eng.run(script::command::LOAD, "_invalid_file.txt");

    CHECK_("Check Load invalid file", !res.empty());

    return cpp::result::SUCCESS;
}

cpp::result::result_void test_compiler_runtime()
{
    std::vector<char> data;

    {
        std::vector<std::string> lines;
        lines.push_back("text this is a test headline");
        lines.push_back("process");
        lines.push_back("print");

        const auto res = script::compile(lines, data);

        CHECK_("Check compile succes", res.empty());

        CHECK_("Check compile result", !data.empty());

        CHECK_("Check compile result size", data.size() == 43);
    }
    {
        const auto res_runtime = script::runtime(data, print);

        CHECK_("Check runtime succes", res_runtime.empty());
    }

    return cpp::result::SUCCESS;
}

int main()
{
    if (!cpp::testing::run_test("Test Parser", test_parser))
        return cpp::app::FAILURE;

    if (!cpp::testing::run_test("Test Engine", test_engine))
        return cpp::app::FAILURE;

    if (!cpp::testing::run_test("Test Comiler and Runtime",
                                test_compiler_runtime))
        return cpp::app::FAILURE;

    return cpp::app::SUCCESS;
}
