Python3 utilities for HEP (high energy physics) calculations.

Installation
============

Build C lib
-----------

Change the current directory to csrc and build the C lib.

```bash
cd csrc
python3 setup.py build
```

The C lib (*e.g. _C.cpython-38-x86_64-linux-gnu.so* built with Python3.8 on x86_64 Linux) will be installed in the root directory of xhep.

Set PYTHONPATH
--------------

Add xhep to python library searching path. Put the actual xhep path in the following command, replacing the *path-to-xhep*. For instance, the xhep is placed in */home/rabbit/heplibs/xhep*, the *path-to-xhep* should be */home/rabbit/heplibs*.

```bash
export PYTHONPATH=$PYTHONPATH:path-to-xhep
```


Usage
=====

Import xhep in Python3 shell or scripts.

```python
import xhep
```

Or import xhep components directly.

```python
from xhep import Vec4
```


Vec4
====

Vec4 is the Lorentz four-vector.

It can be build from (*px, py, pz, m*), (*pt, eta, phi, m*), or (*pt, eta, phi, E*).

```python
v1 = Vec4.px_py_pz_m(1, 2, 3, 0)
v2 = Vec4.pt_eta_phi_m(1, 2, 3, 0)
v3 = Vec4.pt_eta_phi_E(1, 2, 3, 10)
```

A Vec4 object has the following attributes.

* *x*: Gets the x component.
* *y*: Gets the y component.
* *z*: Gets the z component.
* *t*: Gets the time component.
* *px*: Gets the px component.
* *py*: Gets the py component.
* *pz*: Gets the pz component.
* *E*: Gets the energy component.
* *p*: Gets the magnitude of momentum.
* *pt*: Gets the magnitude of transverse momentum.
* *Et*: Gets the magnitude of transverse energy.
* *m*: Gets the invariant mass.
* *mt*: Gets the transverse invariant mass.
* *cos_theta*: Gets the cos of polar angle.
* *theta*: Gets the polar angle in rads.
* *eta*: Gets the pseudo rapidity.
* *phi*: Gets the azimuth angle.
* *rapidity*: Gets the rapidity.

The distances between two Vec4 objects can be calculated by

```python
d = Vec4.delta_eta(v1, v2)
d = Vec4.delta_phi(v1, v2)
d = Vec4.delta_R(v1, v2)    # dR^2 = dη^2 + dϕ^2

d = Vec4.delta_rapidity(v1, v2)
d = Vec4.delta_R_rapidity(v1, v2)    # dR^2 = dy^2 + dϕ^2
```
