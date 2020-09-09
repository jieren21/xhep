#pragma once

#include <Python.h>

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

// ==================
// Refcount utilities
// ==================

// Reference a Python object `x` by increasing the refcount of the newly referenced object
PyObject *Ref(PyObject *x);
#define REF(x) Ref((PyObject *)x)

// Set `x` reference to a new Python object `y`,
// by increasing the refcount of the newly referenced object
// and decreasing the refcount of the previously referenced object
void SetRef(PyObject *&x, PyObject *y);
#define SET_REF(x, y) SetRef((PyObject *&)(x), (PyObject *)(y))

