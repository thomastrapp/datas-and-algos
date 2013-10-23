#include <algorithm>
#include <functional>

#include "gtest/gtest.h"
#include "ds/priority-queue.h"
#include "generic/rule-of-five.h"

namespace {

typedef ::testing::Types<ds::priority_queue<int>> pq;
INSTANTIATE_TYPED_TEST_CASE_P(RuleOfFivePriorityQueue, RuleOfFiveTest, pq);

TEST(DsPriorityQueueTest, PushPopValues)
{
  std::vector<int> values {4,5,7,2,3,99,100,55,98,123};
  ds::priority_queue<int> queue;

  for(const auto& v : values)
  {
    queue.push(v);
  }

  while( values.size() )
  {
    std::vector<int>::iterator max = 
      std::max_element(values.begin(), values.end());
    EXPECT_EQ(queue.top(), *max);
    queue.pop();
    values.erase(max);
  }

  EXPECT_EQ(values.size(), 0);
}

TEST(DsPriorityQueueTest, MinQueue)
{
  std::vector<int> values {4,5,7,2,3,99,100,55,98,123};
  ds::priority_queue<int, std::vector<int>, std::greater<int>> 
    min_queue(values);

  while( values.size() )
  {
    std::vector<int>::iterator min = 
      std::min_element(values.begin(), values.end());
    EXPECT_EQ(min_queue.top(), *min);
    min_queue.pop();
    values.erase(min);
  }
}

TEST(DsPriorityQueueTest, ConstructByVector)
{
  std::vector<int> values {4,5,7,2,3,99,100,55,98,123};
  ds::priority_queue<int> queue(values);

  while( values.size() )
  {
    std::vector<int>::iterator max = 
      std::max_element(values.begin(), values.end());
    EXPECT_EQ(queue.top(), *max);
    queue.pop();
    values.erase(max);
  }
}

}

