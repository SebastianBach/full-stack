#include "optimization.h"
#include "script.h"
#include <optional>

namespace
{

inline auto set_memory(intermediate::cmd cmd)
{
    return cmd == intermediate::cmd::text_memory ||
           cmd == intermediate::cmd::load_memory;
}

void _remove_set_memory(data& data)
{
    code temp;
    temp.reserve(data.c.size());

    std::optional<intermediate> prev;

    for (const auto& line : data.c)
    {
        if (line.command == intermediate::cmd::comment)
        {
            temp.push_back(line);
            continue;
        }

        if (set_memory(line.command))
        {
            if (prev.has_value())
            {
                const auto& prev_line = prev.value();
                data.add_issue(issue::type::INFO, issue::phase::OPTIMIZAZION,
                               "Remove line.", prev_line.line,
                               prev_line.number);
            }

            prev = line;
        }
        else
        {
            if (prev.has_value())
            {
                temp.push_back(prev.value());
                prev = std::optional<intermediate>();
            }

            temp.push_back(line);
        }
    }

    if (prev.has_value())
        temp.push_back(prev.value());

    data.c = temp;
}

void _remove_redundant_process(data& data)
{
    code temp;
    temp.reserve(data.c.size());

    std::optional<intermediate> prev;

    for (const auto& line : data.c)
    {
        if (line.command == intermediate::cmd::comment)
        {
            temp.push_back(line);
            continue;
        }

        if (line.command == intermediate::cmd::process_memory)
        {
            if (prev.has_value())
            {
                const auto& prev_line = prev.value();
                data.add_issue(issue::type::INFO, issue::phase::OPTIMIZAZION,
                               "Remove line.", prev_line.line,
                               prev_line.number);
            }

            prev = line;
        }
        else
        {
            if (prev.has_value())
            {
                temp.push_back(prev.value());
                prev = std::optional<intermediate>();
            }

            temp.push_back(line);
        }
    }

    if (prev.has_value())
        temp.push_back(prev.value());

    data.c = temp;
}

inline auto block_start(intermediate::cmd cmd)
{
    return cmd == intermediate::cmd::load_memory ||
           cmd == intermediate::cmd::text_memory;
}

void _remove_dangling_process(code& block, data& data)
{

    if (block.size() < 2)
        return;

    const auto last_line = block.at(block.size() - 1);

    if (last_line.command == intermediate::cmd::process_memory)
    {

        data.add_issue(issue::type::INFO, issue::phase::OPTIMIZAZION,
                       "Remove 'process' without effect.", last_line.line,
                       last_line.number);

        block.pop_back();
    }
}

void _check_print_text(code& code_block)
{
    auto copy = code_block;

    if (copy.size() != 2)
        return;

    const auto& first_line  = copy.at(0);
    const auto& second_line = copy.at(1);

    if (first_line.command != intermediate::cmd::text_memory)
        return;

    if (second_line.command != intermediate::cmd::print_memory)
        return;

    code_block.clear();
    code_block.push_back(intermediate{intermediate::cmd::print_text,
                                      first_line.operand, first_line.line,
                                      first_line.number, ""});
}

void _check_save_text(code& code_block)
{
    auto copy = code_block;

    if (copy.size() != 2)
        return;

    const auto& first_line  = copy.at(0);
    const auto& second_line = copy.at(1);

    if (first_line.command != intermediate::cmd::text_memory)
        return;

    if (second_line.command != intermediate::cmd::save_memory)
        return;

    code_block.clear();
    code_block.push_back(intermediate{intermediate::cmd::save_text,
                                      first_line.operand, first_line.line,
                                      first_line.number, second_line.operand});
}

void _pre_process(code& block)
{

    auto copy = block;

    if (copy.size() < 3)
        return;

    const auto first_line  = copy.at(0);
    const auto second_line = copy.at(1);

    if (first_line.command != intermediate::cmd::text_memory)
        return;

    if (second_line.command != intermediate::cmd::process_memory)
        return;

    // preprocess

    script::engine engine(nullptr);

    engine.run(script::command::TEXT, first_line.operand);
    engine.run(script::command::PROCESS, "");

    const auto res = engine.get_memory();

    block.clear();
    block.push_back(intermediate{intermediate::cmd::text_memory, res,
                                 first_line.line, first_line.number, ""});

    for (auto i = 2u; i < copy.size(); ++i)
        block.push_back(copy.at(i));
}

void _check_no_output(code& block, data& data)
{
    if (block.size() < 2)
        return;

    auto has_output = false;

    for (const auto& line : block)
    {
        if (line.command == intermediate::cmd::print_memory ||
            line.command == intermediate::cmd::save_memory)
            return;
    }

    if (!has_output)
    {
        data.add_issue(issue::type::INFO, issue::phase::OPTIMIZAZION,
                       "Delete code block without effect.", block.at(0).line,
                       block.at(0).number);

        block.clear();
    }
}

} // namespace

// dead code removal; pre-processing
void optimizationA(data& data)
{
    // dead code removal: setting memory

    _remove_set_memory(data);
    _remove_redundant_process(data);
}

void optimizationB(data& data)
{
    std::vector<code> blocks;

    for (const auto& line : data.c)
    {
        if (line.command == intermediate::cmd::comment)
            continue;

        if (line.command == intermediate::cmd::create_file)
        {
            code block;
            block.push_back(line);
            blocks.push_back(block);
            continue;
        }

        if (block_start(line.command))
        {
            code block;
            blocks.push_back(block);
        }

        blocks[blocks.size() - 1].push_back(line);
    }

    // optimize blocks

    for (auto& block : blocks)
    {
        _check_no_output(block, data);

        if (block.empty())
            continue;

        _remove_dangling_process(block, data);
        _pre_process(block);
        _check_print_text(block);
        _check_save_text(block);
    }

    // write blocks back

    data.c.clear();

    for (const auto& block : blocks)
        for (const auto& line : block)
            data.c.push_back(line);
}

void memory_init(data& data)
{
    for (auto& line : data.c)
    {
        if (line.command == intermediate::cmd::text_memory)
        {
            line.command = intermediate::cmd::text_init_memory;
            return;
        }

        if (line.command == intermediate::cmd::load_memory)
        {
            line.command = intermediate::cmd::load_init_memory;
            return;
        }
    }
}
