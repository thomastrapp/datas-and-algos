#include <cstdlib>
#include <iostream>

#include "../test/src/al/mergesort/random-number-array.h"

#include "al/mergesort.h"

//extern std::vector<int> random_numbers;

template<typename Container>
void print_container(Container& c)
{
  typename Container::const_iterator i = c.begin();
  int j = 1;
  for(; i != c.end(); ++i, ++j)
  {
    std::cout << *i << ",";

    if( j % 10 == 0 )
      std::cout << "\n";
  }

  std::cout << std::endl;
}

int main()
{
  std::vector<int> values {12,1,15,4,15,61,2,3,4,2,1,1};

  al::mergesort(random_numbers.begin(), random_numbers.end());
//  std::sort(random_numbers.begin(), random_numbers.end());

  print_container(random_numbers);

  return EXIT_SUCCESS;
}

