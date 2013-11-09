#ifndef GENERIC_RULE_OF_FIVE_H
#define GENERIC_RULE_OF_FIVE_H

#include <type_traits>

#include "gtest/gtest.h"

namespace
{

template<typename T>
class RuleOfFiveTest : public ::testing::Test
{
  public:
    typedef T target;
};

TYPED_TEST_CASE_P(RuleOfFiveTest);

TYPED_TEST_P(RuleOfFiveTest, isCopyConstructible)
{
  TypeParam right;
  TypeParam left(right);
}

TYPED_TEST_P(RuleOfFiveTest, isNothrowMoveConstructible)
{
  EXPECT_TRUE(std::is_nothrow_move_constructible<TypeParam>::value);
}

TYPED_TEST_P(RuleOfFiveTest, isAssignable)
{
  TypeParam left;
  TypeParam right;

  left = right;

  // EXPECT_TRUE is a macro, therefore chokes on commas
  bool b = std::is_assignable<TypeParam, TypeParam>::value;
  EXPECT_TRUE(b);
}

TYPED_TEST_P(RuleOfFiveTest, AssignmentReturnsReference)
{
  TypeParam left;
  TypeParam right;
  TypeParam third;

  left = right = third;
}

REGISTER_TYPED_TEST_CASE_P(RuleOfFiveTest, 
  isCopyConstructible, isNothrowMoveConstructible, AssignmentReturnsReference,
  isAssignable);

}

#endif // GENERIC_RULE_OF_FIVE_H
