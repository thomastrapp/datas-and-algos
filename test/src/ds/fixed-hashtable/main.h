#include <algorithm>

#include "gtest/gtest.h"
#include "ds/fixed-hashtable.h"
#include "data/random-number-array.h"

namespace {

TEST(DsFixedHashtableTest, GetSetValue)
{
  ds::fixed_hashtable<int, int> table(10);

  table.set(5, 55);
  table.set(1, 55);
  table.set(3, 77);

  EXPECT_EQ(*(table.get(5)), 55);
  EXPECT_EQ(*(table.get(1)), 55);
  EXPECT_EQ(*(table.get(3)), 77);
}

TEST(DsFixedHashtableTest, Holds10KValues)
{
  ds::fixed_hashtable<unsigned int, unsigned int> table(
    data::random_numbers.size()
  );
  unsigned int i = 0;
  for(unsigned int value : data::random_numbers)
  {
    table.set(i++, value);
  }

  for(unsigned int n = 0; n < i; ++n)
  {
    boost::optional<unsigned int> result = table.get(n);
    ASSERT_TRUE(result);
    EXPECT_TRUE(
      std::binary_search(
        data::random_numbers_sorted.begin(),
        data::random_numbers_sorted.end(),
        *result
      )
    );
  }
}

}

