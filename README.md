Data Structures and Algorithms
===============================

Copyright 2013 Thomas Trapp, http://www.thomastrapp.com

datas-and-algos is free Software under the terms of the GNU General Public License
Version 2. See COPYING for full license text.

A (still) small repository of algorithms I have written for fun, including unit tests.

Algorithms:
------------
- mergesort.h
  Typical Mergesort implementation using C++.
- sort-and-count-inversions.h
  Inplace sort. Returns the count of inversions.
- strassen-matrix-multiply.h
  Matrix multiplication as invented by Strassen ([Wikipedia: Strassen algorithm](http://en.wikipedia.org/wiki/Strassen_algorithm "Wikipedia: Strassen algorithm"))

Data structures:
-----------------
- square-matrix.h
  A square matrix to be used with strassen-matrix-multiply.h
- stack.h
  A typical stack (worse than std::stack)

Build unit tests:
------------------
- Either use the convenience script in `scripts/build-and-run-tests.sh` or
- Use cmake directly:
    cd test/build
    cmake ..
    make
    ./data-structures-test
- The unit test framework (google-test) will automatically be downloaded and built. 

Dependencies:
--------------
  cmake >= 2.8.7

