#include "gtest/gtest.h"
#include "ds/stack.h"

namespace {

class DsStackTest : public ::testing::Test
{
  protected:
    bool stack_values_equal(
      ds::stack<int> left, 
      ds::stack<int> right
    )
    {
      if( left.size() != right.size() )
        return false;

      while( left.size() )
      {
        if( left.top() != right.top() )
          return false;

        left.pop();
        right.pop();
      }

      return true;
    }
};

TEST_F(DsStackTest, EmptyRemoveFails)
{
  ds::stack<int> s;
  EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST_F(DsStackTest, AddRemoveToZero)
{
  ds::stack<int> s;

  s.push(0);
  s.push(1);
  s.push(2);
  s.pop();
  s.pop();
  s.pop();

  EXPECT_EQ(0, s.size());
}

TEST_F(DsStackTest, AddRemoveConsistentSize)
{
  ds::stack<int> s;
  int my_val = 0;

  const size_t num_add = 500;
  const size_t num_rem = 250;

  size_t i = 0;
  for(; i < num_add; ++i)
  {
    EXPECT_EQ(i, s.size());
    s.push(my_val);
  }

  for(; i > num_add - num_rem; --i)
  {
    EXPECT_EQ(i, s.size());
    s.pop();
  }

  for(; i < num_add + num_rem; ++i)
  {
    EXPECT_EQ(i, s.size());
    s.push(my_val);
  }

  for(; i > 0; --i)
  {
    EXPECT_EQ(i, s.size());
    s.pop();
  }

  ASSERT_EQ(0, s.size());
  ASSERT_TRUE(s.empty());
  EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST_F(DsStackTest, EmptyTopFails)
{
  ds::stack<int> s;
  EXPECT_THROW(s.top(), std::out_of_range);
}

TEST_F(DsStackTest, CopiesValues)
{
  ds::stack<int> left;
  std::vector<int> values {1,2,3,4,5};

  for(auto i : values)
  {
    left.push(i);
  }

  ds::stack<int> copy_construct(left);
  EXPECT_TRUE(stack_values_equal(left, copy_construct));

  ds::stack<int> assignment;
  assignment = copy_construct;
  EXPECT_TRUE(stack_values_equal(left, assignment));
}

TEST_F(DsStackTest, SavesValues)
{
  ds::stack<int> s;
  std::vector<int> values {1,2,3,4,5};

  for(auto i : values)
  {
    s.push(i);
    EXPECT_EQ(i, s.top());
  }

  for(auto i = values.rbegin(); i != values.rend(); ++i)
  {
    EXPECT_EQ(*i, s.top());
    s.pop();
  }

  EXPECT_THROW(s.pop(), std::out_of_range);
}


}


