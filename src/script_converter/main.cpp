#include "converter.h"
#include <cstdlib>

int main(int argc, char* argv[])
{
    if (!converter(argc, argv))
    {
        print_error("failure.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
