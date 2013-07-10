#include <stdexcept>

#include "gtest/gtest.h"
#include "ds/square-matrix.h"
#include "al/strassen-matrix-multiply.h"

namespace {

TEST(AlStrassenTest, Multiplies)
{
  ds::square_matrix<int> m1(2);
  m1.set(0, 0, 1);
  m1.set(0, 1, 2);
  m1.set(1, 0, 3);
  m1.set(1, 1, 4);

  ds::square_matrix<int> result(
    al::strassen_matrix_multiply(m1, m1)
  );

  ds::square_matrix<int> m2(2);
  m2.set(0, 0, 7);
  m2.set(0, 1, 10);
  m2.set(1, 0, 15);
  m2.set(1, 1, 22);

  EXPECT_TRUE(result == m2);
}

TEST(AlStrassenTest, ThrowsOnSizeDiff)
{
  ds::square_matrix<int> m1(2);
  m1.set(0, 0, 1);
  m1.set(0, 1, 2);
  m1.set(1, 0, 3);
  m1.set(1, 1, 4);

  ds::square_matrix<int> m2(1);
  m1.set(0, 0, 1);

  EXPECT_THROW(al::strassen_matrix_multiply(m1, m2), std::out_of_range);
}

TEST(AlStrassenTest, ThrowsOnNotPowerOfTwo)
{
  ds::square_matrix<int> m1(5);
  EXPECT_THROW(al::strassen_matrix_multiply(m1, m1), std::out_of_range);
}


}

