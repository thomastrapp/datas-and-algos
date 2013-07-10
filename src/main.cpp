#include <cstdlib>
#include <array>

#include "ds/square-matrix.h"

int main(int argc, char * argv[])
{
  const size_t matrix_size = 2;
  std::array<ds::square_matrix<long>, 4> matrices {{
    ds::square_matrix<long>(matrix_size),
    ds::square_matrix<long>(matrix_size),
    ds::square_matrix<long>(matrix_size),
    ds::square_matrix<long>(matrix_size)
  }};
  
  int h = 1;
  for(auto& m : matrices)
  {
    for(size_t i = 0; i < matrix_size; ++i)
      for(size_t j = 0; j < matrix_size; ++j)
      {
        m.set(i, j, h++);
      }
  }
  
  ds::square_matrix<long> m_multiplied(matrices[0] * matrices[1]);
  m_multiplied.print();
  
  return EXIT_SUCCESS;
}

