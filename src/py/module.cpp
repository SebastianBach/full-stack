#include "functions.h"
#include <Python.h>

/*
- https://docs.python.org/3/extending/extending.html
*/

const char* title_case_doc =
    "Converts the given string formatted as a headline.\n"
    "\n"
    "Args:\n"
    "    input_string (str): The string to be converted.\n"
    "\n"
    "Returns:\n"
    "    str: The converted string.\n"
    "\n"
    "This function takes a single string argument and returns a new string "
    "that has been\n"
    "formatted as APA style headline.\n"
    "\n"
    "Example:\n"
    "    >>> import text_conversion\n"
    "    >>> result = text_conversion.title_case('this is a headline')\n"
    "    >>> print(result)\n"
    "    'This Is a Headline'\n";

const char* get_library_build_date_doc =
    "Returns the build date of the module as a string.\n"
    "\n"
    "This function does not take any arguments and returns a string\n"
    "representing the date on which the module was built. This can be useful "
    "for\n"
    "version checks or logging when using the module.\n"
    "\n"
    "Returns:\n"
    "    str: The build date of the module, typically in 'YYYY-MM-DD' format.\n"
    "\n"
    "Example:\n"
    "    >>> import text_conversion\n"
    "    >>> build_date = text_conversion.get_library_build_date()\n"
    "    >>> print(build_date)\n"
    "    '2024-01-01'\n";

static PyMethodDef module_methods[] = {
    {"title_case", py_convert, METH_VARARGS, title_case_doc},
    {"get_library_build_date", py_date, METH_NOARGS,
     get_library_build_date_doc},
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
