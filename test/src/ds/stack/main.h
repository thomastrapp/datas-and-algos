#include "gtest/gtest.h"
#include "ds/stack.h"

namespace {

template<typename T>
class DsStackTest : public ::testing::Test
{
  public:
    typedef T value_type;

  protected:
    bool stack_values_equal(
      ds::stack<T> left, 
      ds::stack<T> right
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

typedef DsStackTest<int> DsStackTestInt;

typedef ::testing::Types<int, bool> TestElementTypes;
TYPED_TEST_CASE(DsStackTest, TestElementTypes);

TYPED_TEST(DsStackTest, EmptyRemoveFails)
{
  typedef typename TestFixture::value_type t;
  ds::stack<t> s;

  EXPECT_THROW(s.pop(), std::out_of_range);
}

TYPED_TEST(DsStackTest, AddRemoveToZero)
{
  typedef typename TestFixture::value_type t;
  ds::stack<t> s;

  s.push(static_cast<t>(0));
  s.push(static_cast<t>(1));
  s.push(static_cast<t>(2));
  s.pop();
  s.pop();
  s.pop();

  EXPECT_EQ(0, s.size());
}

TYPED_TEST(DsStackTest, AddRemoveConsistentSize)
{
  typedef typename TestFixture::value_type t;
  ds::stack<t> s;
  t my_val = static_cast<t>(0);

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

TYPED_TEST(DsStackTest, EmptyTopFails)
{
  typedef typename TestFixture::value_type t;
  ds::stack<t> s;

  EXPECT_THROW(s.top(), std::out_of_range);
}

TEST_F(DsStackTestInt, CopiesValues)
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

TEST_F(DsStackTestInt, MovesValues)
{
  ds::stack<int> left;
  std::vector<int> values {1,2,3,4,5};

  for(auto i : values)
  {
    left.push(i);
  }

  ds::stack<int> victim(left);
  ds::stack<int> move_construct(std::move(victim));
  EXPECT_TRUE(stack_values_equal(left, move_construct));
  EXPECT_EQ(0, victim.size());
}

TEST_F(DsStackTestInt, SavesValues)
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


