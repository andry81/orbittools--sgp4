* README_EN.txt
* 2018.09.21
* sgp4

1. DESCRIPTION
2. LICENSE
3. REPOSITORIES
4. INSTALLATION
5. AUTHOR EMAIL

-------------------------------------------------------------------------------
1. DESCRIPTION
-------------------------------------------------------------------------------
SGP4 patched sources fork from:
https://www.danrw.com/sgp4/
https://github.com/dnwrnr/sgp4

Partially refactored to use C++ std types and std functions.

C++ SGP4 Satellite Library

The original library patched to fix these issue:

1. All double's replaced by dd_real from QD library to decrease precision
   fluctuation to the minimum in certain cases.

2. uint64_t in DateTime and all time related classes replaced by floating point
   value to avoid truncation of the ticks fraction part.

3. Fix trigonometric range before call and after call to triginometric
   functions because of sloppy QD arithmetic outside and inside a function
   call.

All patches improved precision from ~1 meter per 100km altitude along
velocity vector in certain routines up to 10^-7 meters per 100km altitude along
velocity vector.

Cmake scripts uses the cmake modules from the tacklelib library:

https://svn.code.sf.net/p/tacklelib/cmake/trunk

Third-party QD library hosts here:

https://svn.code.sf.net/p/orbittools/qd_/trunk

-------------------------------------------------------------------------------
2. LICENSE
-------------------------------------------------------------------------------
The MIT license (see included text file "license.txt" or
https://en.wikipedia.org/wiki/MIT_License)

-------------------------------------------------------------------------------
3. REPOSITORIES
-------------------------------------------------------------------------------
Primary:
  * https://svn.code.sf.net/p/orbittools/sgp4/trunk
First mirror:
  * https://github.com/andry81/orbittools--sgp4.git
Second mirror:
  * https://bitbucket.org/andry81/orbittools-sgp4.git

-------------------------------------------------------------------------------
4. INSTALLATION
-------------------------------------------------------------------------------
N/A

-------------------------------------------------------------------------------
5. AUTHOR EMAIL
-------------------------------------------------------------------------------
Andrey Dibrov (andry at inbox dot ru)
