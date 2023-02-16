#include "functions.h"
#include <Python.h>

/*
- https://docs.python.org/3/extending/extending.html
*/

static PyMethodDef module_methods[] = {
    {"convert", py_convert, METH_VARARGS, "Converts Data."},
    {"get_library_build_date", py_date, METH_NOARGS,
     "Returns the creation date of the module."},
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
