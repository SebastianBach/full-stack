#include "functions.h"
#include <Python.h>

/*
- https://docs.python.org/3/extending/extending.html
*/

static PyMethodDef module_methods[] = {
    {"title_case", py_convert, METH_VARARGS,
     "Converts the given string formatted as a headline"},
    {"get_library_build_date", py_date, METH_NOARGS,
     "Returns the build date of the module as a string."},
    {NULL, NULL, 0, NULL}};

// defines MODULE name
static struct PyModuleDef func_module = {
    PyModuleDef_HEAD_INIT,
    "text_conversion",
    "A module providing conversion functionality.",
    -1,
    module_methods,
    NULL,
    NULL,
    NULL,
    NULL};

// has to be named PyInit_MODULE
PyMODINIT_FUNC PyInit_text_conversion(void)
{
    return PyModule_Create(&func_module);
}
