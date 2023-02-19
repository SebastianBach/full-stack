#include "functions.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <text_conversion_constexpr.h>

PyObject* py_convert(PyObject*, PyObject* args)
{
    const char* input_string;

    if (!PyArg_ParseTuple(args, "s", &input_string))
    {
        return NULL;
    }

    std::string data{input_string};

    text_conversion_constexpr::convert_to_title_case(data);

    return PyUnicode_FromString(data.c_str());
}

PyObject* py_date(PyObject*, PyObject*)
{
    return PyUnicode_FromString(__DATE__);
}
