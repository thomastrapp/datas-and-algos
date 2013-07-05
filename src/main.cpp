#include <cstdlib>
#include <iostream>
#include <fstream>

#include "al/mergesort.h"
#include "al/sort-and-count-inversions.h"

int main()
{
  std::vector<int> v;
  v.reserve(100000);

  {
    std::ifstream f("data/integers.txt");

    if( !f.is_open() )
    {
      std::cout << "cannot open file for reading" << std::endl;
      return EXIT_FAILURE;
    }

    int num = 0;
    while( f.good() )
    {
      if( f >> num )
        v.push_back(num);
    }

    f.close();
  }

  std::cout << "Read file, " 
            << v.size() 
            << " integers loaded" 
            << std::endl;

  size_t inversions = 0;
  inversions = 
    al::sort_and_count_inversions<
      typename std::vector<int>::iterator, 
      size_t
    >
  (v.begin(), v.end());

  std::cout << "Inversions: " << inversions << std::endl;

  return EXIT_SUCCESS;
}

