#include "lib.h"
#include "my_func.h"
#include <span>

namespace func_lib
{
void convert_string(std::string& data)
{
    func::convert2(data);
}

void convert_data(char* data, size_t cnt) {
    std::span<char> temp(data, cnt);
    func::convert2(temp);
}

} // namespace func_lib
