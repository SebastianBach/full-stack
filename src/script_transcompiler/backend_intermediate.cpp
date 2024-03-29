#include "backend.h"

namespace
{
bool generate_intermediate(const intermediate& i, data& data)
{
    data.result.push_back("from: " + i.line);

    switch (i.command)
    {
    case (intermediate::cmd::comment):
        data.result.push_back("COMMENT: " + i.operand);
        break;
    case (intermediate::cmd::create_file):
        data.result.push_back("CREATE FILE: " + i.operand);
        break;
    case (intermediate::cmd::load_init_memory):
        data.result.push_back("LOAD INIT MEMORY: " + i.operand);
        break;
    case (intermediate::cmd::load_memory):
        data.result.push_back("LOAD INTO MEMORY: " + i.operand);
        break;
    case (intermediate::cmd::print_memory):
        data.result.push_back("PRINT MEMORY");
        break;
    case (intermediate::cmd::process_memory):
        data.result.push_back("PROCESS MEMORY");
        break;
    case (intermediate::cmd::save_memory):
        data.result.push_back("SAVE MEMORY: " + i.operand);
        break;
    case (intermediate::cmd::text_init_memory):
        data.result.push_back("TEXT INIT MEMORY: " + i.operand);
        break;
    case (intermediate::cmd::text_memory):
        data.result.push_back("TEXT TO MEMORY: " + i.operand);
        break;
    case (intermediate::cmd::print_text):
        data.result.push_back("PRINT TEXT: " + i.operand);
        break;
    case (intermediate::cmd::save_text):
        data.result.push_back("SAVE TEXT: '" + i.operand + "' to " + i.operandB);
        break;
    }

    return true;
}
} // namespace

void generate_intermediate(data& data)
{
    for (const auto& ic : data.c)
    {
        if (!generate_intermediate(ic, data))
            return;
    }
}
