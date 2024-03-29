
#include <cstdlib>
#include <iostream>
#include <script.h>
#include <source_location>

inline void print_error(const char* msg, const std::source_location& location)
{
    std::cout << "\033[31m";
    std::cout << "Error: " << msg << std::endl;
    std::cout << location.file_name() << " " << location.function_name() << " "
              << location.line() << std::endl;
    std::cout << "\033[0m";
}

static int s_returnValue = EXIT_SUCCESS;

#define CHECK(ARG)                                                             \
    if (!(ARG))                                                                \
    {                                                                          \
        print_error(#ARG, std::source_location::current());                    \
        s_returnValue = EXIT_FAILURE;                                          \
    }

void print(const char* msg)
{
    std::cout << msg << std::endl;
}

int main()
{

    {
        script::command cmd;
        std::string     operand;

        script::parse("# this is some comment", cmd, operand);
        CHECK(cmd == script::command::COMMENT);

        script::parse("text this is some test text", cmd, operand);
        CHECK(cmd == script::command::TEXT);

        script::parse("process", cmd, operand);
        CHECK(cmd == script::command::PROCESS);

        script::parse("print", cmd, operand);
        CHECK(cmd == script::command::PRINT);

        script::parse("load file", cmd, operand);
        CHECK(cmd == script::command::LOAD);

        script::parse("save file", cmd, operand);
        CHECK(cmd == script::command::SAVE);
    }

    {
        script::engine eng{print};

        eng.run(script::command::TEXT, "test text");

        CHECK(eng.get_memory() == "test text");

        eng.run(script::command::PROCESS, "");

        CHECK(eng.get_memory() == "Test Text");

        eng.run(script::command::SAVE, "_current_content.txt");

        eng.run(script::command::TEXT, "nothing");

        CHECK(eng.get_memory() == "nothing");

        eng.run(script::command::LOAD, "_current_content.txt");

        CHECK(eng.get_memory() == "Test Text");

        const auto res = eng.run(script::command::LOAD, "_invalid_file.txt");

        CHECK(!res.empty());
    }

    {
        std::vector<char> data;

        {
            std::vector<std::string> lines;
            lines.push_back("text this is a test headline");
            lines.push_back("process");
            lines.push_back("print");

            const auto res = script::compile(lines, data);

            CHECK(res.empty());

            CHECK(!data.empty());

            CHECK(data.size() == 43);
        }
        {
            const auto res_runtime = script::runtime(data, print);

            CHECK(res_runtime.empty());
        }
    }

    return s_returnValue;
}
