#include "utils.h"

PyObject *Ref(PyObject *x)
{
    Py_XINCREF(x);
    return x;
}

void SetRef(PyObject *&x, PyObject *y)
{
    PyObject *tmp = x;
    x = y;
    Py_XINCREF(y);
    Py_XDECREF(tmp);
}

