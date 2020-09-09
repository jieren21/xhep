import os
from distutils.core import setup, Extension

include_dirs = [os.path.abspath('.')]
library_dirs = []
libraries = []

## Pythia8
#include_dirs.append('/home/renjie/apps/hep/pythia8230/include')
#library_dirs.append('/home/renjie/apps/hep/pythia8230/lib')
#libraries.append('pythia8')

## HepMC
#include_dirs.append('/home/renjie/apps/hep/hepmc2.06.09/include')
#library_dirs.append('/home/renjie/apps/hep/hepmc2.06.09/lib')
#libraries.append('HepMC')

## FastJet
#include_dirs.append('/home/renjie/apps/hep/fastjet-3.3.0/build/include')
#library_dirs.append('/home/renjie/apps/hep/fastjet-3.3.0/build/lib')
#libraries.append('fastjet')


sources = []
headers = []
subdirs = ['.']
for subdir in subdirs:
    for file in os.listdir(subdir):
        if os.path.splitext(file)[1] == '.h':
            headers.append(os.path.join(subdir, file))
        elif os.path.splitext(file)[1] == '.cpp':
            sources.append(os.path.join(subdir, file))

_C_module = Extension('_C', sources=sources, depends=headers,
                      include_dirs=include_dirs, library_dirs=library_dirs, libraries=libraries,
                      extra_compile_args=['-g', '--std=c++11', '-Wno-write-strings'])

os.system('rm -r build')

setup(name='xhep',
      version='1.0',
      description='This is a demo package',
      ext_modules=[_C_module])

os.system('cp build/lib.*/*.so ..')

