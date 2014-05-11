#include "gtest/gtest.h"

#include "al/counting-sort.h"

namespace {

TEST(AlCountingSort, ZeroElements)
{
  std::vector<unsigned int> v;

  al::counting_sort(v.begin(), v.end());

  EXPECT_EQ(0, v.size());
}

TEST(AlCountingSort, OneElement)
{
  unsigned int my_value = 0;
  std::vector<unsigned int> v {my_value};

  al::counting_sort(v.begin(), v.end());

  EXPECT_EQ(my_value, v.back());
  EXPECT_EQ(1, v.size());
}

TEST(AlCountingSort, TwoElements)
{
  std::vector<unsigned int> v = {99,66};

  al::counting_sort(v.begin(), v.end());

  EXPECT_EQ(2, v.size());
  EXPECT_EQ(66, v.front());
  EXPECT_EQ(99, v.back());
}

TEST(AlCountingSort, Duplicates)
{
  unsigned int unsorted[] = {999,999,999,980,980,970,100,100,999,100,100,109};
  unsigned int sorted[] = {100,100,100,100,109,970,980,980,999,999,999,999};
  size_t size = sizeof(unsorted) / sizeof(unsorted[0]);

  al::counting_sort(unsorted, unsorted + size);

  EXPECT_EQ(0, std::memcmp(unsorted, sorted, sizeof(unsorted)));
}

TEST(AlCountingSort, UnsignedIntMax)
{
  uint8_t max = std::numeric_limits<uint8_t>::max();
  std::vector<uint8_t> v = {
    static_cast<uint8_t>(max - 1), 
    static_cast<uint8_t>(max - 2)
  };

  al::counting_sort(v.begin(), v.end());

  EXPECT_EQ(2, v.size());
  EXPECT_EQ(max-2, v.front());
  EXPECT_EQ(max-1, v.back());
}

TEST(AlCountingSort, MaxInInputThrows)
{
  typedef size_t count_type;
  typedef std::vector<count_type>::iterator iterator_type;

  count_type max = std::numeric_limits<count_type>::max();
  std::vector<count_type> v = {max};

  // EXPECT_THROW fails with template parameters
  auto sort_f = [](std::vector<count_type>& v){
    al::counting_sort<iterator_type, count_type, count_type>(v.begin(), v.end());
  };

  EXPECT_THROW(sort_f(v), std::overflow_error);

  EXPECT_EQ(1, v.size());
  EXPECT_EQ(max, v.front());
}

TEST(AlCountingSort, SortsValues)
{
  unsigned int unsorted[] = {12, 1, 15, 4, 15, 61, 2, 3, 4, 2, 1, 1};
  unsigned int sorted[] = {1, 1, 1, 2, 2, 3, 4, 4, 12, 15, 15, 61};
  size_t size = sizeof(unsorted) / sizeof(unsorted[0]);

  al::counting_sort(unsorted, unsorted + size);

  EXPECT_EQ(0, std::memcmp(unsorted, sorted, sizeof(unsorted)));
}


}

