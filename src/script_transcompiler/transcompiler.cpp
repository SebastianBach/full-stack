#include "transcompiler.h"
#include "backend.h"
#include "frontend.h"
#include "optimization.h"
#include <cstring>
#include <fstream>

TARGET get_target(char* arg)
{
    if (std::strcmp(arg, "py") == 0)
        return TARGET::PY;
    if (std::strcmp(arg, "cpp") == 0)
        return TARGET::CPP;
    if (std::strcmp(arg, "linux_x86_64") == 0)
        return TARGET::LINUX_X86_64;
    if (std::strcmp(arg, "i") == 0)
        return TARGET::INTERMEDIATE;

    return TARGET::INVALID;
}

void write_to_file(data& data, const std::string& dst)
{
    if (data.c.empty())
    {
        data.add_issue(issue::type::ERROR, issue::phase::STORE,
                       "Generated code is empty.", "", 0);
        return;
    }

    std::ofstream file_stream(dst);

    if (!file_stream.is_open())
    {
        data.add_issue(issue::type::ERROR, issue::phase::STORE,
                       "Could not write to output file.", "", 0);
        return;
    }

    for (const auto& r : data.result)
    {
        file_stream << r << "\n";
    }

    file_stream.close();
}

void transcompiler(data& data, int argc, char* argv[])
{
    if (argc != 4)
    {
        data.add_issue(issue::type::ERROR, issue::phase::PARSING,
                       "Invalid command line arguments.", "", 0);
        return;
    }

    const auto target = get_target(argv[3]);
    if (target == TARGET::INVALID)
    {
        data.add_issue(issue::type::ERROR, issue::phase::PARSING,
                       "Invalid 'target' argument.", "", 0);
        return;
    }

    parse_source(argv[1], data);

    if (!data.success)
        return;

    optimizationA(data);

    optimizationB(data);

    memory_init(data);

    generate_code(data, target);

    if (!data.success)
        return;

    write_to_file(data, argv[2]);
}
