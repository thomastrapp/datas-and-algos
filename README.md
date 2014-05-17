Data Structures and Algorithms
===============================

Copyright 2013 Thomas Trapp, http://www.thomastrapp.com

datas-and-algos is free Software under the terms of the GNU General Public License
Version 2. See COPYING for full license text.

A (still) small repository of algorithms I have written for fun, including unit tests.

Algorithms:
------------
- **al/mergesort.h**  
  [Mergesort](http://en.wikipedia.org/wiki/Mergesort "Wikipedia: Mergesort")
- **al/sort-and-count-inversions.h**  
  Inplace sort, returns the count of inversions
- **al/strassen-matrix-multiply.h**  
  Matrix multiplication as invented by [Strassen](http://en.wikipedia.org/wiki/Strassen_algorithm "Wikipedia: Strassen algorithm")
- **al/radixsort.h**  
  [LSD Radixsort](http://en.wikipedia.org/wiki/Radix_sort#Least_significant_digit_radix_sorts "Wikipedia: Radixsort")
- **al/murmur.h**   
  [MurmurHash](http://en.wikipedia.org/wiki/MurmurHash#Algorithm "Wikipedia: MurmurHash") as invented by Austin Appleby
- **al/counting-sort.h**   
  [Counting Sort](http://en.wikipedia.org/wiki/Counting_sort "Wikipedia: Counting sort")
- **al/boyer-moore-substring.h**   
  [Boyer-Moore String Search](http://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm "Wikipedia: Boyer-Moore string search algorithm")

Data structures:
-----------------
- **ds/square-matrix.h**  
  A square matrix utilising `strassen-matrix-multiply.h`
- **ds/stack.h**  
  A stack
- **ds/binary-search-tree.h**  
  A binary search tree
- **ds/fixed-hashtable.h**   
  A hashtable with fixed size. `al::murmur` is used as a hash function.
- **ds/priority-queue.h**   
  A priority queue based on `std::make_heap`, `std::push_heap` and `std::pop_heap`

Project structure:
-------------------
- **src/al/**    
  Algorithms
- **src/ds/**    
  Data structures
- **test/src/al/**    
  Unit tests for algorithms
- **test/src/ds/**    
  Unit tests for data structures
- **test/src/generic/**    
  Generic unit tests (`rule-of-five.h`, useful for default constructible objects that implement the rule of five)
- **test/smhasher/**    
  [SMHasher](http://code.google.com/p/smhasher/ "Google Code: SMHasher") build to verify my MurmurHash implementation. Will automatically download SMHasher from Google Code.
- **scripts/**    
  Helper scripts (`build.sh`, `build-and-run-tests.sh`, ...)
- **scripts/static-analysis/**    
  Convenience wrappers for cppcheck and cpplint (`run_cppcheck.sh`, `run_cpplint.sh`)

Build unit tests:
------------------
Either use the convenience script in `scripts/build-and-run-tests.sh` or use cmake directly:
        
        cd test/build
        cmake ..
        make
        ./datas-and-algos-test
        
The unit testing framework ([googletest](http://code.google.com/p/googletest/ "Google Code: googletest")) will automatically be downloaded and built by cmake.

Dependencies:
--------------
cmake >= 2.8.7, boost (`boost::optional` for `ds::fixed_hashtable`)

