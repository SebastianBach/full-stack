#pragma once
#include "script.h"
#include <map>

namespace script
{
struct token
{
    command cmd;
    bool    has_operand;
};

static const std::map<std::string, token> tokens = {
    {"text", {command::TEXT, true}},
    {"load", {command::LOAD, true}},
    {"save", {command::SAVE, true}},
    {"process", {command::PROCESS, false}},
    {"print", {command::PRINT, false}}};

struct code
{
    char code_value;
    bool has_operand;
};

static const std::map<command, code> codes = {{command::TEXT, {0, true}},
                                              {command::PROCESS, {1, false}},
                                              {command::PRINT, {2, false}},
                                              {command::LOAD, {3, true}},
                                              {command::SAVE, {4, true}}};

} // namespace script
