#ifndef TARGETS_H__
#define TARGETS_H__


#include <vector>
#include <string>

bool make_cpp(std::vector<std::string>& lines, const char* dst);
bool make_py(std::vector<std::string>& lines, const char* dst);
bool make_linux_x86_64(std::vector<std::string>& lines, const char* dst);

#endif
