#include "data.h"

namespace
{

struct cpp_file
{
    bool use_iostream        = false;
    bool use_string          = false;
    bool use_text_conversion = false;
    bool use_fstream         = false;

    std::vector<std::string> lines;
};

inline bool generate_cpp_code(const intermediate& i, cpp_file& file, data&)
{
    file.lines.push_back("// " + i.line);

    switch (i.command)
    {
    case (intermediate::cmd::comment):
    {
        file.lines.push_back("//" + i.operand);
        break;
    }
    case (intermediate::cmd::text_init_memory):
    {
        file.lines.push_back("std::string text = \"" + i.operand + "\";");
        file.use_string = true;
        break;
    }
    case (intermediate::cmd::text_memory):
    {
        file.lines.push_back("text = \"" + i.operand + "\";");
        break;
    }
    case (intermediate::cmd::print_memory):
    {
        file.lines.push_back("std::cout << text << std::endl;");
        file.use_iostream = true;
        break;
    }
    case (intermediate::cmd::load_init_memory):
    {
        file.lines.push_back("std::string text;");
    }
        [[fallthrough]];
    case (intermediate::cmd::load_memory):
    {
        file.lines.push_back("{");
        file.lines.push_back("    std::ifstream file{\"" + i.operand + "\"};");
        file.lines.push_back("    if (!file.is_open())");
        file.lines.push_back("        return EXIT_FAILURE;");
        file.lines.push_back("    std::stringstream buffer;");
        file.lines.push_back("    buffer << file.rdbuf();");
        file.lines.push_back("    text = buffer.str();");
        file.lines.push_back("    file.close();");
        file.lines.push_back("}");

        file.use_fstream = true;
        break;
    }
    case (intermediate::cmd::create_file):
    {
        file.lines.push_back("{");
        file.lines.push_back("    std::ofstream file{\"" + i.operand + "\"};");
        file.lines.push_back("    file.close();");
        file.lines.push_back("}");

        file.use_fstream = true;
        break;
    }
    case (intermediate::cmd::save_memory):
    {
        file.lines.push_back("{");
        file.lines.push_back("    std::ofstream output_file{\"" + i.operand +
                             "\"};");
        file.lines.push_back("    if (!output_file.is_open())");
        file.lines.push_back("        return EXIT_FAILURE;");
        file.lines.push_back("    output_file << text << std::endl;");
        file.lines.push_back("    output_file.close();");
        file.lines.push_back("}");
        file.use_fstream = true;
        break;
    }
    case (intermediate::cmd::process_memory):
    {
        file.lines.push_back("text_conversion::convert_to_title_case(text);");
        file.use_text_conversion = true;
        break;
    }
    case (intermediate::cmd::print_text):
    {
        file.lines.push_back("std::cout << \"" + i.operand +
                             "\" << std::endl;");
        file.use_iostream = true;
        break;
    }
    case (intermediate::cmd::save_text):
    {
        file.lines.push_back("{");
        file.lines.push_back("    std::ofstream output_file{\"" + i.operandB +
                             "\"};");
        file.lines.push_back("    if (!output_file.is_open())");
        file.lines.push_back("        return EXIT_FAILURE;");
        file.lines.push_back("    output_file << \"" + i.operand +
                             "\" << std::endl;");
        file.lines.push_back("    output_file.close();");
        file.lines.push_back("}");
        file.use_fstream = true;
        break;
        break;
    }
    }

    return true;
}
} // namespace

void generate_cpp(data& data)
{
    cpp_file file;

    for (const auto& ic : data.c)
    {
        if (!generate_cpp_code(ic, file, data))
            return;
    }

    if (file.use_text_conversion)
        data.result.push_back("#include \"text_conversion.h\"");

    data.result.push_back("#include <cstdlib>");
    if (file.use_iostream)
        data.result.push_back("#include <iostream>");
    if (file.use_string)
        data.result.push_back("#include <string>");
    if (file.use_fstream)
    {
        data.result.push_back("#include <fstream>");
        data.result.push_back("#include <sstream>");
    }

    data.result.push_back("\nint main() {");

    for (const auto& line : file.lines)
        data.result.push_back("    " + line);

    data.result.push_back("    return EXIT_SUCCESS;");
    data.result.push_back("}\n");
}
