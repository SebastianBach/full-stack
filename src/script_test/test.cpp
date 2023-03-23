
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

#define ASSERT(ARG)                                                            \
    if (!(ARG))                                                                \
    {                                                                          \
        print_error(#ARG, std::source_location::current());                    \
        return -1;                                                             \
    }


void print(const char* msg)
{
    // nothing
}

int main()
{

    {
        script::command cmd;
        std::string     operand;

        script::parse("# this is some comment", cmd, operand);
        ASSERT(cmd == script::command::COMMENT);

        script::parse("text this is some test text", cmd, operand);
        ASSERT(cmd == script::command::TEXT);

        script::parse("process", cmd, operand);
        ASSERT(cmd == script::command::PROCESS);

        script::parse("print", cmd, operand);
        ASSERT(cmd == script::command::PRINT);

        script::parse("load file", cmd, operand);
        ASSERT(cmd == script::command::LOAD);

        script::parse("save file", cmd, operand);
        ASSERT(cmd == script::command::SAVE);
    }

    {
        script::engine eng{print};

        eng.run(script::command::TEXT, "test text");

        ASSERT(eng.get_memory() == "test text");

        eng.run(script::command::PROCESS, "");

        ASSERT(eng.get_memory() == "Test Text");
    }

    return 0;
}
