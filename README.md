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
