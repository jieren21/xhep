#pragma once

#include <Python.h>

class Vec4
{
  protected:
    double val[4]; // [x, y, z, t]

  public:
    Vec4() { val[0] = val[1] = val[2] = val[3] = 0; }

    Vec4(double x, double y, double z, double t)
    {
        val[0] = x;
        val[1] = y;
        val[2] = z;
        val[3] = t;
    }

    Vec4(double *x)
    {
        val[0] = x[0];
        val[1] = x[1];
        val[2] = x[2];
        val[3] = x[3];
    }

  public:
    double x() const { return val[0]; }
    double y() const { return val[1]; }
    double z() const { return val[2]; }
    double t() const { return val[3]; }

    double px() const { return val[0]; }
    double py() const { return val[1]; }
    double pz() const { return val[2]; }
    double E() const { return val[3]; }

    double m() const;
    double mt() const;

    double p() const;
    double pt() const;
    double Et() const;

    double cos_theta() const;
    double theta() const;
    double eta() const;
    double phi() const;
    double rapidity() const;

  public:
    static Vec4 px_py_pz_m(double px, double py, double pz, double m);
    static Vec4 pt_eta_phi_m(double pt, double eta, double phi, double m);
    static Vec4 pt_eta_phi_E(double pt, double eta, double phi, double E);

  public:
    static double delta_eta(Vec4 &a, Vec4 &b);
    static double delta_phi(Vec4 &a, Vec4 &b);
    static double delta_R(Vec4 &a, Vec4 &b);
    static double delta_rapidity(Vec4 &a, Vec4 &b);
    static double delta_R_rapidity(Vec4 &a, Vec4 &b);
};

inline Vec4 operator+(const Vec4 &a) { return a; }
inline Vec4 operator-(const Vec4 &a) { return Vec4(-a.x(), -a.y(), -a.z(), -a.t()); }

inline Vec4 operator+(const Vec4 &a, const Vec4 &b) { return Vec4(a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.t() + b.t()); }
inline Vec4 operator-(const Vec4 &a, const Vec4 &b) { return Vec4(a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.t() - b.t()); }
inline Vec4 operator*(const Vec4 &a, const double b) { return Vec4(a.x() * b, a.y() * b, a.z() * b, a.t() * b); }
inline Vec4 operator*(const double a, const Vec4 &b) { return Vec4(a * b.x(), a * b.y(), a * b.z(), a * b.t()); }
inline Vec4 operator/(const Vec4 &a, const double b) { return Vec4(a.x() / b, a.y() / b, a.z() / b, a.t() / b); }

inline Vec4 operator+=(Vec4 &a, const Vec4 &b) { return a = a + b; }
inline Vec4 operator-=(Vec4 &a, const Vec4 &b) { return a = a - b; }
inline Vec4 operator*=(Vec4 &a, const double b) { return a = a * b; }
inline Vec4 operator/=(Vec4 &a, const double b) { return a = a / b; }

struct PyVec4
{
    PyObject_HEAD;
    Vec4 v;
};

extern PyTypeObject PyVec4_Type;

#define PyVec4_Check(op) (PyObject_TypeCheck((PyObject *)(op), &PyVec4_Type))

PyObject *PyVec4_New(const Vec4 &v);

