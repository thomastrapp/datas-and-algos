Data Structures and Algorithms
===============================

Copyright 2013 Thomas Trapp, http://www.thomastrapp.com

datas-and-algos is free Software under the terms of the GNU General Public License
Version 2. See COPYING for full license text.

A (still) small repository of algorithms I have written for fun, including unit tests.

Algorithms:
------------
- **al/mergesort.h**  
  Typical Mergesort
- **al/sort-and-count-inversions.h**  
  Inplace sort. Returns the count of inversions.
- **al/strassen-matrix-multiply.h**  
  Matrix multiplication as invented by Strassen ([Wikipedia: Strassen algorithm](http://en.wikipedia.org/wiki/Strassen_algorithm "Wikipedia: Strassen algorithm"))
- **al/radixsort.h**  
  Radixsort ([Wikipedia: Radixsort](http://en.wikipedia.org/wiki/Radixsort "Wikipedia: Radixsort"))

Data structures:
-----------------
- **ds/square-matrix.h**  
  A square matrix to be used with strassen-matrix-multiply.h
- **ds/stack.h**  
  A typical stack

Build unit tests:
------------------
Either use the convenience script in `scripts/build-and-run-tests.sh` or use cmake directly:
        
        cd test/build
        cmake ..
        make
        ./data-structures-test
        
The unit test framework (google-test) will automatically be downloaded and built.

Dependencies:
--------------
cmake >= 2.8.7

