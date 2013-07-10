#include <sstream>
#include <limits>
#include <stdexcept>

#include "gtest/gtest.h"
#include "ds/square-matrix.h"

namespace {

TEST(DsSquareMatrixTest, GetSetThrowsOutOfRange)
{
  ds::square_matrix<int> m(10);

  EXPECT_THROW(m.get(9, 10), std::out_of_range);
  EXPECT_THROW(m.get(10, 9), std::out_of_range);
  EXPECT_THROW(m.get(-1, 0), std::out_of_range);
  EXPECT_THROW(m.get(0, -1), std::out_of_range);
  EXPECT_THROW(m.get(-1, -1), std::out_of_range);

  EXPECT_THROW(m.set(9, 10, 1), std::out_of_range);
  EXPECT_THROW(m.set(10, 9, 1), std::out_of_range);
  EXPECT_THROW(m.set(-1, 0, 1), std::out_of_range);
  EXPECT_THROW(m.set(0, -1, 1), std::out_of_range);
  EXPECT_THROW(m.set(-1, -1, 1), std::out_of_range);
}

TEST(DsSquareMatrixTest, CombineThrowsOutOfRange)
{
  std::array<ds::square_matrix<int>, 4> ms {{
    ds::square_matrix<int>(4),
    ds::square_matrix<int>(5),
    ds::square_matrix<int>(4),
    ds::square_matrix<int>(4)
  }};

  EXPECT_THROW({
    ds::square_matrix<int> m(ms[0], ms[1], ms[2], ms[3]);
  }, std::out_of_range);
}

TEST(DsSquareMatrixTest, SplitThrowsOutOfRange)
{
  std::array<ds::square_matrix<int>, 3> ms {{
    ds::square_matrix<int>(1),
    ds::square_matrix<int>(3),
    ds::square_matrix<int>(10)
  }};

  for(auto i : ms)
  {
    EXPECT_THROW(i.square_split(), std::out_of_range);
  }
}

TEST(DsSquareMatrixTest, InvalidWidthConstructThrows)
{
  EXPECT_THROW(ds::square_matrix<int> m(0), std::out_of_range);
}

TEST(DsSquareMatrixTest, CombineSplitMatrices)
{
  std::array<std::array<int, 4>, 4> mv {{
    { 1,2,5,6 },
    { 3,4,7,8 },
    { 9,10,13,14 },
    { 11,12,15,16 }
  }};

  std::array<ds::square_matrix<int>, 4> ms {{
    ds::square_matrix<int>(2),
    ds::square_matrix<int>(2),
    ds::square_matrix<int>(2),
    ds::square_matrix<int>(2)
  }};

  for(size_t i = 0; i < mv.size(); ++i)
  {
    for(size_t j = 0; j < mv[i].size(); ++j)
    {
      ms[i].set(j / 2, j % 2, mv[i][j]);
    }
  }

  const std::string expected_output(
    "\n1\t2\t3\t4\t\n"
    "5\t6\t7\t8\t\n"
    "9\t10\t11\t12\t\n"
    "13\t14\t15\t16\t\n"
  );

  ds::square_matrix<int> m(ms[0], ms[1], ms[2], ms[3]);

  std::stringstream ss;
  m.print(ss);

  EXPECT_EQ(expected_output, ss.str());

  typename ds::square_matrix<int>::split_result split = m.square_split();

  for(size_t i = 0; i < mv.size(); ++i)
  {
    for(size_t j = 0; j < mv[i].size(); ++j)
    {
      EXPECT_EQ(mv[i][j], split[i].get(j / 2, j % 2));
    }
  }
}

TEST(DsSquareMatrixTest, MatrixAddition)
{
  ds::square_matrix<int> m1(2);
  m1.set(0, 0, 1);
  m1.set(0, 1, 23);
  m1.set(1, 0, -11);
  m1.set(1, 1, 0);

  ds::square_matrix<int> m2(2);
  m2.set(0, 0, 2);
  m2.set(0, 1, 46);
  m2.set(1, 0, -22);
  m2.set(1, 1, 0);

  EXPECT_TRUE(m2 == (m1 + m1));
  EXPECT_FALSE(m2 != (m1 + m1));
}

TEST(DsSquareMatrixTest, MatrixSubtraction)
{
  ds::square_matrix<int> m1(2);
  m1.set(0, 0, 1);
  m1.set(0, 1, 23);
  m1.set(1, 0, -11);
  m1.set(1, 1, 0);

  ds::square_matrix<int> m2(2);
  m2.set(0, 0, 2);
  m2.set(0, 1, 46);
  m2.set(1, 0, -22);
  m2.set(1, 1, 0);

  ds::square_matrix<int> m3(2);
  m3.set(0, 0, -1);
  m3.set(0, 1, -23);
  m3.set(1, 0, 11);
  m3.set(1, 1, 0);

  EXPECT_TRUE(m3 == (m1 - m2));
  EXPECT_FALSE(m3 != (m1 - m2));
  EXPECT_EQ(2, m3.get_width());
}

TEST(DsSquareMatrixTest, Copy)
{
  ds::square_matrix<int> m(2);
  m.set(0, 0, -1);
  m.set(0, 1, -23);
  m.set(1, 0, 11);
  m.set(1, 1, 0);

  ds::square_matrix<int> m_copy(m);

  EXPECT_EQ(m, m_copy);
  EXPECT_EQ(m.get_width(), m_copy.get_width());
  EXPECT_EQ(2, m_copy.get_width());
  EXPECT_EQ(-1, m_copy.get(0, 0));
  EXPECT_EQ(-23, m_copy.get(0, 1));
  EXPECT_EQ(11, m_copy.get(1, 0));
  EXPECT_EQ(0, m_copy.get(1, 1));
}

TEST(DsSquareMatrixTest, Assignment)
{
  ds::square_matrix<int> m(2);
  m.set(0, 0, -1);
  m.set(0, 1, -23);
  m.set(1, 0, 11);
  m.set(1, 1, 0);

  ds::square_matrix<int> m_copy(2);
  m_copy = m;

  EXPECT_EQ(m, m_copy);
  EXPECT_EQ(m.get_width(), m_copy.get_width());
  EXPECT_EQ(2, m_copy.get_width());
  EXPECT_EQ(-1, m_copy.get(0, 0));
  EXPECT_EQ(-23, m_copy.get(0, 1));
  EXPECT_EQ(11, m_copy.get(1, 0));
  EXPECT_EQ(0, m_copy.get(1, 1));
}

TEST(DsSquareMatrixTest, Comparison)
{
  ds::square_matrix<int> m(2);
  m.set(0, 0, -1);
  m.set(0, 1, -23);
  m.set(1, 0, 11);
  m.set(1, 1, 0);

  ds::square_matrix<int> m_copy(2);
  m_copy = m;

  EXPECT_TRUE(m_copy == m);
  EXPECT_FALSE(m_copy != m);

  m.set(1, 1, 23);

  EXPECT_FALSE(m_copy == m);
  EXPECT_TRUE(m_copy != m);

  ds::square_matrix<int> m1(1);
  m1.set(0, 0, -1);

  EXPECT_FALSE(m_copy == m1);
  EXPECT_TRUE(m_copy != m1);
}


}

