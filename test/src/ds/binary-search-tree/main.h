#include <algorithm>
#include <cstring>
#include <stdexcept>

#include "gtest/gtest.h"
#include "ds/binary-search-tree.h"
#include "generic/rule-of-five.h"

namespace {

typedef ::testing::Types<ds::binary_search_tree<int>> bst;
INSTANTIATE_TYPED_TEST_CASE_P(RuleOfFiveBinarySearchTree, RuleOfFiveTest, bst);

namespace helper {

template<typename container>
bool is_equal(const container& left, const container& right)
{
  return 
    left.size() == right.size() && 
    std::memcmp(left.data(), right.data(), left.size() * sizeof(typename container::value_type)) == 0;
}

}

TEST(DsBinarySearchTreeTest, InputEqualsToVector)
{
  std::vector<int> values {1,2,3,4,5,6,7,8,9,10};

  ds::binary_search_tree<int> from_sorted(values, true);
  ds::binary_search_tree<int> from_unsorted(values, false);
  auto it = values.begin();
  ds::binary_search_tree<int> from_for_each(*it);
  ++it;
  for(; it != values.end(); ++it)
  {
    from_for_each.insert(*it);
  }

  std::vector<int> to_vec_from_sorted(from_sorted.to_vector());
  std::vector<int> to_vec_from_unsorted(from_unsorted.to_vector());
  std::vector<int> to_vec_from_for_each(from_for_each.to_vector());

  std::sort(to_vec_from_sorted.begin(), to_vec_from_sorted.end());
  std::sort(to_vec_from_unsorted.begin(), to_vec_from_unsorted.end());
  std::sort(to_vec_from_for_each.begin(), to_vec_from_for_each.end());

  EXPECT_TRUE(helper::is_equal(values, to_vec_from_sorted));
  EXPECT_TRUE(helper::is_equal(values, to_vec_from_unsorted));
  EXPECT_TRUE(helper::is_equal(values, to_vec_from_for_each));
}

TEST(DsBinarySearchTreeTest, InsertDuplicateThrows)
{
  ds::binary_search_tree<int> tree(5);
  EXPECT_THROW(tree.insert(5), std::domain_error);
}

TEST(DsBinarySearchTreeTest, UnsortedFlagMisuseThrows)
{
  std::vector<int> values {{ 1,2,3,4,5,6,7,8,9,32,10 }};
  EXPECT_THROW(
    ds::binary_search_tree<int> tree(values, true), 
    std::domain_error
  );
}

TEST(DsBinarySearchTreeTest, DestroyRootThrows)
{
  ds::binary_search_tree<int> tree(5);
  EXPECT_THROW(tree.destroy(), std::domain_error);
}

TEST(DsBinarySearchTreeTest, DestroyRemovesElement)
{
  std::vector<int> values {{ 1,2,42,3,99,7,4,5,66,17,8,119,32,102 }};
  ds::binary_search_tree<int> tree(values, false);

  {
    ds::binary_search_tree<int> * node(tree.find(2));
    ASSERT_NE(node, nullptr); 
    node->destroy();
  }

  EXPECT_EQ(tree.find(2), nullptr);
}

TEST(DsBinarySearchTreeTest, GetSetValue)
{
  std::vector<int> values {{ 1,2,42,3,99,7,4,5,66,17,8,119,32,102 }};
  ds::binary_search_tree<int> tree(values, false);

  {
    ds::binary_search_tree<int> * node(tree.find(2));
    ASSERT_NE(node, nullptr);
    node->set_value(900);
    EXPECT_EQ(node->get_value(), 900);
  }
  {
    ds::binary_search_tree<int> * node(tree.find(900));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->get_value(), 900);
  }
}

TEST(DsBinarySearchTreeTest, FindsAllElements)
{
  std::vector<int> values {{ 1,2,42,3,99,7,4,5,66,17,8,119,32,102 }};
  ds::binary_search_tree<int> tree(values, false);
  
  for(const auto& value : values)
  {
    ds::binary_search_tree<int> * node = tree.find(value);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->get_value(), value);
  }
}

TEST(DsBinarySearchTreeTest, DestroyIsConsistent)
{
  std::vector<int> values {{ 1,2,42,3,99,7,4,5,66,17,8,119,32,102 }};
  const size_t values_size = values.size();
  ds::binary_search_tree<int> tree(values, false);
  std::vector<int> deleted_values;
  deleted_values.reserve(values_size);

  for(std::vector<int>::iterator it = values.begin(); it != values.end(); ++it)
  {
    ds::binary_search_tree<int> * node = tree.find(*it);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->get_value(), *it);

    if( it == values.end() - 1 )
    {
      EXPECT_THROW(node->destroy(), std::domain_error);
      EXPECT_NE(tree.find(*it), nullptr);
    }
    else
    {
      EXPECT_NO_THROW(node->destroy());
      EXPECT_EQ(tree.find(*it), nullptr);
      deleted_values.push_back(*it);
    }

    it = values.erase(it);
    --it;

    // check if remaining values are still in tree
    for(const auto& value : values)
    {
      ds::binary_search_tree<int> * check = tree.find(value);
      ASSERT_NE(check, nullptr);
      EXPECT_EQ(check->get_value(), value);
    }
    // check if deleted_values are gone from tree
    for(const auto& value : deleted_values)
    {
      ds::binary_search_tree<int> * check = tree.find(value);
      ASSERT_EQ(check, nullptr);
    }
  }

  EXPECT_EQ(tree.to_vector().size(), 1);
  EXPECT_EQ(values.size(), 0);
  EXPECT_EQ(deleted_values.size(), values_size - 1);
}

TEST(DsBinarySearchTreeTest, CopiesTree)
{
  std::vector<int> values_left 
    {{ 102,44,55,54,53,1,2,42,3,99,7,4,5,66,17,8,119,32 }};
  ds::binary_search_tree<int> tree_left(values_left, false);

  std::vector<int> values_right 
    {{ 102,44,98,55,54,53,100,43,21,2,42,3,99 }};
  ds::binary_search_tree<int> tree_right(values_right, false);

  tree_left = tree_right;
  ds::binary_search_tree<int> tree_copy_construct(tree_left);

  auto vec_left = tree_left.to_vector();
  auto vec_right = tree_right.to_vector();
  auto vec_copy = tree_copy_construct.to_vector();

  std::sort(vec_left.begin(), vec_left.end());
  std::sort(vec_right.begin(), vec_right.end());
  std::sort(vec_copy.begin(), vec_copy.end());

  EXPECT_TRUE(helper::is_equal(vec_left, vec_right));
  EXPECT_TRUE(helper::is_equal(vec_copy, vec_right));
}


}

