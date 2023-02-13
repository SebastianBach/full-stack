#ifndef LIB_H__
#define LIB_H__

#include <array>
#include <string>
#include <array>

namespace func_lib
{
void convert_data(char* data, size_t cnt);

void convert_string(std::string& data);

template <typename T, auto N> void convert_array(std::array<T, N>& data)
{
    convert_data(data.data(), data.size());
}


const char* version();
const char* date();

} // namespace func_lib

#endif
