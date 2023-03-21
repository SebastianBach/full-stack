
#include <script.h>

int main()
{

    script::command cmd;
    std::string     operand;

    script::engine eng;

    script::parse("# this is some comment", cmd, operand);

    script::parse("TEXT this is some test text", cmd, operand);


    eng.run(cmd, operand);

    script::parse("LOAD some/path", cmd, operand);

    script::parse("PROCESS", cmd, operand);

    eng.run(cmd, operand);

    script::parse("PRINT", cmd, operand);

    eng.run(cmd, "");



    return 0;
}
