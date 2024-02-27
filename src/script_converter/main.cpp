#include "converter.h"
#include <cstdlib>
#include "targets.h"

int main(int argc, char* argv[])
{

    std::vector<issue> issues;

    if (!converter(argc, argv, issues))
    {
        print_error("failure.");
        return EXIT_FAILURE;
    }

    for (const auto& issue: issues){

        if (issue.type == issue::TYPE::ERROR)
            std::cout << "Error: " << issue.msg;
        else
            std::cout << "Warning: " << issue.msg;

        std::cout << "\n"  << issue.lineNumber << ": " << issue.line << "\n";
    } 

    return EXIT_SUCCESS;
}
