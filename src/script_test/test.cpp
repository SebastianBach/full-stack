
#include <script.h>

#define ASSERT(ARG)                                                            \
    if (!ARG)                                                                  \
        return -1;

int main()
{

    script::command cmd;
    std::string     operand;

    script::engine eng;

    script::parse("# this is some comment", cmd, operand);

    script::parse("text this is some test text", cmd, operand);

    eng.run(cmd, operand);

    script::parse("load some/path", cmd, operand);

    script::parse("process", cmd, operand);

    eng.run(cmd, operand);

    script::parse("print", cmd, operand);

    eng.run(cmd, "");

    return 0;
}
