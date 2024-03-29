#include "data.h"

inline void add_cmd(data& data, const std::string& cmd)
{
    data.result.push_back("    " + cmd);
}

inline bool generate_code(data& data, const intermediate& i)
{
    add_cmd(data, "# " + i.line);

    switch (i.command)
    {
    case (intermediate::cmd::comment):
        add_cmd(data, "#" + i.operand);
        break;

    case (intermediate::cmd::load_init_memory):
        [[fallthrough]];
    case (intermediate::cmd::load_memory):
        add_cmd(data, "with open(\"" + i.operand + "\", \"r\") as file:");
        add_cmd(data, "    text = file.read()");
        break;

    case (intermediate::cmd::print_memory):

        add_cmd(data, "print(text)");

        break;

    case (intermediate::cmd::process_memory):

        add_cmd(data, "text = text_conversion.title_case(text)");

        break;

    case (intermediate::cmd::save_memory):

        add_cmd(data, "with open(\"" + i.operand + "\", \"w\") as file:");
        add_cmd(data, "    file.write(text)");

        break;

    case (intermediate::cmd::create_file):

        add_cmd(data, "open('" + i.operand + "', 'a')");

        break;

    case (intermediate::cmd::text_init_memory):
        [[fallthrough]];
    case (intermediate::cmd::text_memory):
        add_cmd(data, "text = \"" + i.operand + "\"");

        break;

    case (intermediate::cmd::print_text):
        add_cmd(data, "print(\"" + i.operand + "\")");
        break;

    case (intermediate::cmd::save_text):
        add_cmd(data, "with open(\"" + i.operandB + "\", \"w\") as file:");
        add_cmd(data, "    file.write(\"" + i.operand + "\")");
        break;
    }

    return true;
}

void generate_py(data& data)
{
    data.result.push_back("import text_conversion");
    data.result.push_back("if __name__ == '__main__':");

    for (const auto& ic : data.c)
    {
        if (!generate_code(data, ic))
            return;
    }
}
