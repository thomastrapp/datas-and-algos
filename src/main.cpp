#include <cstdlib>
#include <vector>
#include <iostream>

#include "al/radixsort.h"
#include "util/print.h"
#include "util/file.h"

int main(int argc, char * argv[])
{
  std::vector<unsigned int> random_numbers;
  random_numbers.reserve(1000000);

  util::push_integer_file_to_container("data/integers.txt", random_numbers);

  al::radixsort(random_numbers);

  util::print_container(random_numbers);

  return EXIT_SUCCESS;
}

