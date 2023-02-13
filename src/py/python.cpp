#include <Python.h>
#include <cstdlib>
#include <iostream>
#include <my_func.h>
#include <string>

/*
- https://docs.python.org/3/extending/extending.html
*/

static PyObject* py_convert(PyObject* self, PyObject* args)
{
    const char* input_string;

    if (!PyArg_ParseTuple(args, "s", &input_string))
    {
        return NULL;
    }

    std::string data{input_string};

    func::convert2(data);

    return PyUnicode_FromString(data.c_str());
}

static PyMethodDef module_methods[] = {
    {"convert", py_convert, METH_VARARGS, "Converts Data."},
    {NULL, NULL, 0, NULL}};

// defines MODULE name
static struct PyModuleDef func_module = {
    PyModuleDef_HEAD_INIT, "func",
    "A module providing conversion functionality.", -1, module_methods};

// has to be named PyInit_MODULE
PyMODINIT_FUNC PyInit_func(void)
{
    return PyModule_Create(&func_module);
}
