#ifndef DATA_H__
#define DATA_H__

#include "script.h"
#include <string>
#include <vector>

enum class TARGET
{
    INTERMEDIATE,
    CPP,
    PY,
    LINUX_X86_64,
    INVALID
};

struct issue
{
    enum class type
    {
        INFO,
        WARNING,
        ERROR
    };

    enum class phase
    {
        PARSING,
        OPTIMIZAZION,
        CODE_GENERATION,
        STORE
    };

    type         t;
    phase        p;
    std::string  msg;
    std::string  line;
    unsigned int number;
};

using issues = std::vector<issue>;

struct intermediate
{
    enum class cmd
    {
        comment,
        text_init_memory,
        text_memory,
        load_init_memory,
        load_memory,
        process_memory,
        print_memory,
        save_memory,
        create_file,

        // code blocks

        print_text, // directly print text
        save_text   // directy save text to file

        // optimizations for separate sub-programs
        // block must include also output, otherwise block does nothing
        // block wiht only text or load does nothing

        // - print_text
        // - copy_file
        // - text_to_file
        // block_start, block-end
    };

    cmd          command;
    std::string  operand;
    std::string  line;
    unsigned int number;
    std::string  operandB;
};

using code = std::vector<intermediate>;

using generated = std::vector<std::string>;

struct data
{
    issues    i;
    code      c;
    generated result;
    bool      success = true;

    void add_issue(issue::type type, issue::phase phase, const std::string& msg,
                   const std::string& line, unsigned int number)
    {
        i.push_back(issue{type, phase, msg, line, number});
        if (type == issue::type::ERROR)
            success = false;
    }

    void add_cmd(intermediate::cmd cmd, const std::string& operand,
                 const std::string& line, unsigned int number)
    {
        c.push_back(intermediate{cmd, operand, line, number, ""});
    }

    void add_cmd(intermediate::cmd cmd, const std::string& operand,
                 const std::string& line, unsigned int number,
                 const std::string& operandB)
    {
        c.push_back(intermediate{cmd, operand, line, number, operandB});
    }
};

#endif
