
#include <cstdlib>

#include "transcompiler.h"
#include "data.h"
#include <iostream>

int main(int argc, char* argv[])
{
    data data;

    transcompiler(data, argc, argv);

    for (const auto& i : data.i)
    {
        if (i.p == issue::phase::PARSING)
            std::cout << "Parsing ";
        else if (i.p == issue::phase::OPTIMIZAZION)
            std::cout << "Optimization ";
        else if (i.p == issue::phase::CODE_GENERATION)
            std::cout << "Code Generation ";
        else
            std::cout << "Storing Result ";

        if (i.t == issue::type::WARNING)
            std::cout << "Warning: ";
        else if (i.t == issue::type::INFO)
            std::cout << "Info: ";
        else
            std::cout << "Error: ";

        std::cout << i.msg << std::endl;

        //if (i.number > 0)
        std::cout << "Line " << i.number << ": " << i.line << std::endl;
    }

    if (!data.success)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
