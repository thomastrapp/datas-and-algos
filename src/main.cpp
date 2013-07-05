#include <cstdlib>
#include <iostream>

#include "../test/src/al/mergesort/random-number-array.h"

#include "al/mergesort.h"
#include "al/sort-and-count-inversions.h"

//extern std::vector<int> random_numbers;

template<typename Container>
void print_container(Container& c)
{
  typename Container::const_iterator i = c.begin();
  int j = 1;
  for(; i != c.end(); ++i, ++j)
  {
    std::cout << *i << ",";

  //  if( j % 10 == 0 )
  //    std::cout << "\n";
  }

  std::cout << std::endl;
}

int main()
{
//  std::vector<int> v {12,1,15,4,15,61,2,3,4,2,1,1};
  std::vector<int> v {6, 9, 1, 14, 8, 12, 3, 2};
//  std::vector<int> v {1,3,5,2,4,6};

  print_container(v);
  unsigned long inversions = 0;
  
  inversions = al::sort_and_count_inversions(v.begin(), v.end());

  print_container(v);

  std::cout << "Inversions: " << inversions << std::endl;

  return EXIT_SUCCESS;
}

