#include "backend.h"

void generate_py(data& data);
void generate_cpp(data& data);
void generate_intermediate(data& data);
void generate_linux_x86_64(data& data);

void generate_code(data& data, TARGET target)
{
    if (target == TARGET::PY)
        return generate_py(data);

    if (target == TARGET::CPP)
        return generate_cpp(data);

    if (target == TARGET::INTERMEDIATE)
        return generate_intermediate(data);

    if(target == TARGET::LINUX_X86_64)
        return generate_linux_x86_64(data);
}
