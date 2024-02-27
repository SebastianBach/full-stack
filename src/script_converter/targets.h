#ifndef TARGETS_H__
#define TARGETS_H__

#include <string>
#include <vector>

struct issue
{
    enum class TYPE
    {
        INFO,
        WARNING,
        ERROR
    };

    TYPE        type;
    std::string msg;
    std::string line;
    unsigned int lineNumber;
};

bool make_cpp(std::vector<std::string>& lines, const char* dst);
bool make_py(std::vector<std::string>& lines, const char* dst);
bool make_linux_x86_64(std::vector<std::string>& lines, std::vector<issue>& issues, const char* dst);

#endif
