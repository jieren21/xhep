#include <Python.h>

#include "Vec4.h"

#include "utils.h"

static PyMethodDef _C_methods[] = {
    {NULL} /* Sentinel */
};

static PyModuleDef _CModule = {
    PyModuleDef_HEAD_INIT,
    "_C",
    "Example module that creates an extension type.",
    -1,
    _C_methods};

PyMODINIT_FUNC PyInit__C(void)
{
    if (PyType_Ready(&PyVec4_Type) < 0)
        return NULL;

    PyObject *m = PyModule_Create(&_CModule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyVec4_Type);

    PyModule_AddObject(m, "Vec4", (PyObject *)&PyVec4_Type);

    return m;
}

