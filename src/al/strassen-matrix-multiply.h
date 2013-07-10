#ifndef AL_STRASSEN_MATRIX_MULTIPLY_H
#define AL_STRASSEN_MATRIX_MULTIPLY_H

#include <iterator>
#include <stdexcept>

// forward declaration since ds/square-matrix.h references this file (avoid
// chicken-egg problem)
namespace ds {
  template<typename value_type>
  class square_matrix;
}

namespace al {

template<typename square_matrix>
square_matrix strassen_matrix_multiply(
  const square_matrix& left, 
  const square_matrix& right
)
{
  if( left.get_width() != right.get_width() )
  {
    throw std::out_of_range("matrix width differs, "
      "strassen matrix multiply impossible");
  }
  
  if( left.get_width() < 2 )
  {
    square_matrix matrix(1);
    matrix.set(0, 0, left.get(0, 0) * right.get(0, 0));
    return matrix;
  }
  
  // implement zero padding for matrices whose width is not a power of two

  // split each matrix into 4 squares
  typename square_matrix::split_result 
    left_split(left.square_split());
  typename square_matrix::split_result 
    right_split(right.square_split());

  const square_matrix& A(left_split[0]);
  const square_matrix& B(left_split[1]);
  const square_matrix& C(left_split[2]);
  const square_matrix& D(left_split[3]);

  const square_matrix& E(right_split[0]);
  const square_matrix& F(right_split[1]);
  const square_matrix& G(right_split[2]);
  const square_matrix& H(right_split[3]);

  // strassen magic
  const square_matrix M1((A + D) * (E + H));
  const square_matrix M2((C + D) * E);
  const square_matrix M3(A * (F - H));
  const square_matrix M4(D * (G - E));
  const square_matrix M5((A + B) * H);
  const square_matrix M6((C - A) * (E + F));
  const square_matrix M7((B - D) * (G + H));

  const square_matrix result(
      M1 + M4 - M5 + M7,
      M3 + M5,
      M2 + M4,
      M1 - M2 + M3 + M6
  );

  return result;
}

}

#endif
