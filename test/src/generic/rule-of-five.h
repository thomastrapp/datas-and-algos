#ifndef GENERIC_RULE_OF_FIVE_H
#define GENERIC_RULE_OF_FIVE_H

#include "gtest/gtest.h"

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

TYPED_TEST_P(RuleOfFiveTest, isMoveConstructible)
{
  TypeParam left(std::move(TypeParam()));
}

TYPED_TEST_P(RuleOfFiveTest, isAssignable)
{
  TypeParam left;
  TypeParam right;

  left = right;
}

TYPED_TEST_P(RuleOfFiveTest, AssignmentReturnsReference)
{
  TypeParam left;
  TypeParam right;
  TypeParam third;

  left = right = third;
}

TYPED_TEST_P(RuleOfFiveTest, isMoveAssignable)
{
  TypeParam left;
  TypeParam right;

  left = std::move(right);
}

REGISTER_TYPED_TEST_CASE_P(RuleOfFiveTest, 
  isCopyConstructible, isMoveConstructible, AssignmentReturnsReference, 
  isAssignable, isMoveAssignable);

#endif // GENERIC_RULE_OF_FIVE_H
