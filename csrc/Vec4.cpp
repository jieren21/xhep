#include "Vec4.h"
#include "utils.h"

// ==================================================
// Vec4
// ==================================================

double Vec4::p() const
{
    return sqrt(px() * px() + py() * py() + pz() * pz());
}

double Vec4::pt() const
{
    return sqrt(px() * px() + py() * py());
}

double Vec4::Et() const
{
    double pt = this->pt();
    return pt == 0 ? 0 : E() * pt / p();
}

double Vec4::m() const
{
    double t = E() * E() - px() * px() - py() * py() - pz() * pz();
    return t >= 0 ? sqrt(t) : -sqrt(-t);
}

double Vec4::mt() const
{
    double t = E() * E() - pz() * pz();
    return t >= 0 ? sqrt(t) : -sqrt(-t);
}

double Vec4::cos_theta() const
{
    double p = this->p();
    return p == 0 ? 1 : pz() / p;
}

double Vec4::theta() const
{
    return atan2(pt(), pz());
}

double Vec4::eta() const
{
    return log((p() + pz()) / (p() - pz())) / 2;
}

// Returns the azimuth angle [-pi, pi].
double Vec4::phi() const
{
    return atan2(py(), px());
}

double Vec4::rapidity() const
{
    return log((E() + pz()) / (E() - pz())) / 2;
}

Vec4 Vec4::px_py_pz_m(double px, double py, double pz, double m)
{
    return m >= 0 ? Vec4(px, py, pz, sqrt(px * px + py * py + pz * pz + m * m))
                  : Vec4(px, py, pz, sqrt(MAX(px * px + py * py + pz * pz - m * m, 0)));
}

Vec4 Vec4::pt_eta_phi_m(double pt, double eta, double phi, double m)
{
    pt = fabs(pt);
    return Vec4::px_py_pz_m(pt * cos(phi), pt * sin(phi), pt * sinh(eta), m);
}

Vec4 Vec4::pt_eta_phi_E(double pt, double eta, double phi, double E)
{
    pt = fabs(pt);
    return Vec4(pt * cos(phi), pt * sin(phi), pt * sinh(eta), E);
}

double Vec4::delta_eta(Vec4 &a, Vec4 &b)
{
    return b.eta() - a.eta();
}

double Vec4::delta_phi(Vec4 &a, Vec4 &b)
{
    double t = b.phi() - a.phi();
    while (t >= M_PI)
        t -= 2 * M_PI;
    while (t < -M_PI)
        t += 2 * M_PI;
    return t;
}

double Vec4::delta_R(Vec4 &a, Vec4 &b)
{
    double d_eta = delta_eta(a, b);
    double d_phi = delta_phi(a, b);
    return sqrt(d_eta * d_eta + d_phi * d_phi);
}

double Vec4::delta_rapidity(Vec4 &a, Vec4 &b)
{
    return b.rapidity() - a.rapidity();
}

double Vec4::delta_R_rapidity(Vec4 &a, Vec4 &b)
{
    double d_y = delta_rapidity(a, b);
    double d_phi = delta_phi(a, b);
    return sqrt(d_y * d_y + d_phi * d_phi);
}

// ==================================================
// PyVec4
// ==================================================

PyObject *PyVec4_New(const Vec4 &v)
{
    auto op = PyObject_New(PyVec4, &PyVec4_Type);
    op->v = v;
    return (PyObject *)op;
}

static int PyVec4_init(PyVec4 *self, PyObject *args, PyObject *kwds)
{
    double x = 0, y = 0, z = 0, t = 0;
    if (!PyArg_ParseTuple(args, "|dddd", &x, &y, &z, &t))
        return -1;
    self->v = Vec4(x, y, z, t);
    return 0;
}

static PyObject *PyVec4_x(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.x()); }
static PyObject *PyVec4_y(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.y()); }
static PyObject *PyVec4_z(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.z()); }
static PyObject *PyVec4_t(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.t()); }
static PyObject *PyVec4_p(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.p()); }
static PyObject *PyVec4_pt(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.pt()); }
static PyObject *PyVec4_et(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.Et()); }
static PyObject *PyVec4_m(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.m()); }
static PyObject *PyVec4_mt(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.mt()); }
static PyObject *PyVec4_cos_theta(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.cos_theta()); }
static PyObject *PyVec4_theta(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.theta()); }
static PyObject *PyVec4_eta(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.eta()); }
static PyObject *PyVec4_phi(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.phi()); }
static PyObject *PyVec4_rapidity(PyVec4 *self, void *) { return PyFloat_FromDouble(self->v.rapidity()); }

static PyObject *PyVec4_px_py_pz_m(void *self, PyObject *args)
{
    double px, py, pz, m;
    if (!PyArg_ParseTuple(args, "dddd", &px, &py, &pz, &m))
        return NULL;
    return PyVec4_New(Vec4::px_py_pz_m(px, py, pz, m));
}

static PyObject *PyVec4_pt_eta_phi_m(void *self, PyObject *args)
{
    double pt, eta, phi, m;
    if (!PyArg_ParseTuple(args, "dddd", &pt, &eta, &phi, &m))
        return NULL;
    return PyVec4_New(Vec4::pt_eta_phi_m(pt, eta, phi, m));
}

static PyObject *PyVec4_pt_eta_phi_E(void *self, PyObject *args)
{
    double pt, eta, phi, E;
    if (!PyArg_ParseTuple(args, "dddd", &pt, &eta, &phi, &E))
        return NULL;
    return PyVec4_New(Vec4::pt_eta_phi_E(pt, eta, phi, E));
}

static PyObject *PyVec4_delta_eta(void *self, PyObject *args)
{
    PyVec4 *x, *y;
    if (!PyArg_ParseTuple(args, "OO", &x, &y))
        return NULL;
    if (!PyVec4_Check(x) || !PyVec4_Check(y))
        return NULL;
    return PyFloat_FromDouble(Vec4::delta_eta(x->v, y->v));
}

static PyObject *PyVec4_delta_phi(void *self, PyObject *args)
{
    PyVec4 *x, *y;
    if (!PyArg_ParseTuple(args, "OO", &x, &y))
        return NULL;
    if (!PyVec4_Check(x) || !PyVec4_Check(y))
        return NULL;
    return PyFloat_FromDouble(Vec4::delta_phi(x->v, y->v));
}

static PyObject *PyVec4_delta_R(void *self, PyObject *args)
{
    PyVec4 *x, *y;
    if (!PyArg_ParseTuple(args, "OO", &x, &y))
        return NULL;
    if (!PyVec4_Check(x) || !PyVec4_Check(y))
        return NULL;
    return PyFloat_FromDouble(Vec4::delta_R(x->v, y->v));
}

static PyObject *PyVec4_delta_rapidity(void *self, PyObject *args)
{
    PyVec4 *x, *y;
    if (!PyArg_ParseTuple(args, "OO", &x, &y))
        return NULL;
    if (!PyVec4_Check(x) || !PyVec4_Check(y))
        return NULL;
    return PyFloat_FromDouble(Vec4::delta_rapidity(x->v, y->v));
}

static PyObject *PyVec4_delta_R_rapidity(void *self, PyObject *args)
{
    PyVec4 *x, *y;
    if (!PyArg_ParseTuple(args, "OO", &x, &y))
        return NULL;
    if (!PyVec4_Check(x) || !PyVec4_Check(y))
        return NULL;
    return PyFloat_FromDouble(Vec4::delta_R_rapidity(x->v, y->v));
}

static PyObject *PyVec4_add(PyObject *v, PyObject *w)
{
    if (PyVec4_Check(v) && PyVec4_Check(w))
    {
        Vec4 &a = ((PyVec4 *)v)->v;
        Vec4 &b = ((PyVec4 *)w)->v;
        return PyVec4_New(a + b);
    }
    Py_RETURN_NOTIMPLEMENTED;
}

static PyObject *PyVec4_sub(PyObject *v, PyObject *w)
{
    if (PyVec4_Check(v) && PyVec4_Check(w))
    {
        Vec4 &a = ((PyVec4 *)v)->v;
        Vec4 &b = ((PyVec4 *)w)->v;
        return PyVec4_New(a - b);
    }
    Py_RETURN_NOTIMPLEMENTED;
}

static PyObject *PyVec4_mul(PyObject *v, PyObject *w)
{
    if (PyVec4_Check(v) && PyNumber_Check(w))
    {
        Vec4 &a = ((PyVec4 *)v)->v;
        double b = PyFloat_AS_DOUBLE(w = PyNumber_Float(w));
        Py_DECREF(w);
        return PyVec4_New(a * b);
    }
    if (PyNumber_Check(v) && PyVec4_Check(w))
    {
        double a = PyFloat_AS_DOUBLE(v = PyNumber_Float(v));
        Vec4 &b = ((PyVec4 *)w)->v;
        Py_DECREF(v);
        return PyVec4_New(a * b);
    }
    Py_RETURN_NOTIMPLEMENTED;
}

static PyObject *PyVec4_div(PyObject *v, PyObject *w)
{
    if (PyVec4_Check(v) && PyNumber_Check(w))
    {
        Vec4 &a = ((PyVec4 *)v)->v;
        double b = PyFloat_AS_DOUBLE(w = PyNumber_Float(w));
        Py_DECREF(w);
        return PyVec4_New(a / b);
    }
    Py_RETURN_NOTIMPLEMENTED;
}

static PyObject *PyVec4_pos(PyObject *v)
{
    if (PyVec4_Check(v))
        return v;
    Py_RETURN_NOTIMPLEMENTED;
}

static PyObject *PyVec4_neg(PyObject *v)
{
    if (PyVec4_Check(v))
    {
        Vec4 &a = ((PyVec4 *)v)->v;
        return PyVec4_New(-a);
    }
    Py_RETURN_NOTIMPLEMENTED;
}

static PyObject *PyVec4_repr(PyVec4 *self)
{
    char buf[128];
    PyOS_snprintf(buf, 128, "Vec4(%g, %g, %g, %g)", self->v.x(), self->v.y(), self->v.z(), self->v.t());
    return PyUnicode_FromString(buf);
}

static PyGetSetDef PyVec4_getseters[] = {
    {"x", (getter)PyVec4_x, NULL, "Gets the x component.", NULL},
    {"y", (getter)PyVec4_y, NULL, "Gets the y component.", NULL},
    {"z", (getter)PyVec4_z, NULL, "Gets the z component.", NULL},
    {"t", (getter)PyVec4_t, NULL, "Gets the time component.", NULL},
    {"px", (getter)PyVec4_x, NULL, "Gets the px component.", NULL},
    {"py", (getter)PyVec4_y, NULL, "Gets the py component.", NULL},
    {"pz", (getter)PyVec4_z, NULL, "Gets the pz component.", NULL},
    {"E", (getter)PyVec4_t, NULL, "Gets the energy component.", NULL},
    {"p", (getter)PyVec4_p, NULL, "Gets the magnitude of momentum.", NULL},
    {"pt", (getter)PyVec4_pt, NULL, "Gets the magnitude of transverse momentum.", NULL},
    {"Et", (getter)PyVec4_et, NULL, "Gets the magnitude of transverse energy.", NULL},
    {"m", (getter)PyVec4_m, NULL, "Gets the invariant mass.", NULL},
    {"mt", (getter)PyVec4_mt, NULL, "Gets the transverse invariant mass.", NULL},
    {"cos_theta", (getter)PyVec4_cos_theta, NULL, "Gets the cos of polar angle.", NULL},
    {"theta", (getter)PyVec4_theta, NULL, "Gets the polar angle in rads.", NULL},
    {"eta", (getter)PyVec4_eta, NULL, "Gets the pseudo rapidity.", NULL},
    {"phi", (getter)PyVec4_phi, NULL, "Gets the azimuth angle.", NULL},
    {"rapidity", (getter)PyVec4_rapidity, NULL, "Gets the rapidity.", NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef PyVec4_methods[] = {
    {"px_py_pz_m", (PyCFunction)PyVec4_px_py_pz_m, METH_VARARGS | METH_STATIC, "Constructs a Lorentz four-vector from (px, py, pz, m)."},
    {"pt_eta_phi_m", (PyCFunction)PyVec4_pt_eta_phi_m, METH_VARARGS | METH_STATIC, "Constructs a Lorentz four-vector from (pt, eta, phi, m)."},
    {"pt_eta_phi_E", (PyCFunction)PyVec4_pt_eta_phi_E, METH_VARARGS | METH_STATIC, "Constructs a Lorentz four-vector from (pt, eta, phi, E)."},
    {"delta_eta", (PyCFunction)PyVec4_delta_eta, METH_VARARGS | METH_STATIC, ""},
    {"delta_phi", (PyCFunction)PyVec4_delta_phi, METH_VARARGS | METH_STATIC, ""},
    {"delta_R", (PyCFunction)PyVec4_delta_R, METH_VARARGS | METH_STATIC, ""},
    {"delta_rapidity", (PyCFunction)PyVec4_delta_rapidity, METH_VARARGS | METH_STATIC, ""},
    {"delta_R_rapidity", (PyCFunction)PyVec4_delta_R_rapidity, METH_VARARGS | METH_STATIC, ""},
    {NULL} /* Sentinel */
};

static PyNumberMethods PyVec4_as_number = {
    (binaryfunc)PyVec4_add, /* nb_add */
    (binaryfunc)PyVec4_sub, /* nb_subtract */
    (binaryfunc)PyVec4_mul, /* nb_multiply */
    0,                      /* nb_remainder */
    0,                      /* nb_divmod */
    0,                      /* nb_power */
    (unaryfunc)PyVec4_neg,  /* nb_negative */
    (unaryfunc)PyVec4_pos,  /* nb_positive */
    0,                      /* nb_absolute */
    0,                      /* nb_bool */
    0,                      /* nb_invert */
    0,                      /* nb_lshift */
    0,                      /* nb_rshift */
    0,                      /* nb_and */
    0,                      /* nb_xor */
    0,                      /* nb_or */
    0,                      /* nb_int */
    0,                      /* nb_reserved */
    0,                      /* nb_float */
    0,                      /* nb_inplace_add */
    0,                      /* nb_inplace_subtract */
    0,                      /* nb_inplace_multiply */
    0,                      /* nb_inplace_remainder */
    0,                      /* nb_inplace_power */
    0,                      /* nb_inplace_lshift */
    0,                      /* nb_inplace_rshift */
    0,                      /* nb_inplace_and */
    0,                      /* nb_inplace_xor */
    0,                      /* nb_inplace_or */
    0,                      /* nb_floor_divide */
    (binaryfunc)PyVec4_div, /* nb_true_divide */
    0,                      /* nb_inplace_floor_divide */
    0,                      /* nb_inplace_true_divide */
};

PyTypeObject PyVec4_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)    /* HEAD */
    "_C.Vec4",                        /* tp_name */
    sizeof(PyVec4),                   /* tp_basicsize */
    0,                                /* tp_itemsize */
    0,                                /* tp_dealloc */
    0,                                /* tp_print */
    0,                                /* tp_getattr */
    0,                                /* tp_setattr */
    0,                                /* tp_reserved */
    (reprfunc)PyVec4_repr,            /* tp_repr */
    &PyVec4_as_number,                /* tp_as_number */
    0,                                /* tp_as_sequence */
    0,                                /* tp_as_mapping */
    0,                                /* tp_hash  */
    0,                                /* tp_call */
    0,                                /* tp_str */
    0,                                /* tp_getattro */
    0,                                /* tp_setattro */
    0,                                /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,               /* tp_flags */
    "Immutable Lorentz four-vector.", /* tp_doc */
    0,                                /* tp_traverse */
    0,                                /* tp_clear */
    0,                                /* tp_richcompare */
    0,                                /* tp_weaklistoffset */
    0,                                /* tp_iter */
    0,                                /* tp_iternext */
    PyVec4_methods,                   /* tp_methods */
    0,                                /* tp_members */
    PyVec4_getseters,                 /* tp_getset */
    0,                                /* tp_base */
    0,                                /* tp_dict */
    0,                                /* tp_descr_get */
    0,                                /* tp_descr_set */
    0,                                /* tp_dictoffset */
    (initproc)PyVec4_init,            /* tp_init */
    0,                                /* tp_alloc */
    PyType_GenericNew,                /* tp_new */
};
