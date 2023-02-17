#ifndef LIB_H__
#define LIB_H__

#include <array>
#include <string>

namespace func_lib
{
void convert_data(char* data, size_t cnt);

void convert_string(std::string& data);


#if __cplusplus >= 201703L
template <typename T, auto N> void convert_array(std::array<T, N>& data)
{
    convert_data(data.data(), data.size());
}
#else
template <typename T, int N> void convert_array(std::array<T, N>& data)
{
    convert_data(data.data(), data.size());
}
#endif


const char* version();
const char* date();

} // namespace func_lib

#endif
