#include <sstream>

#include "gtest/gtest.h"

#include "ds/infix-ostream-iterator.h"

namespace {

TEST(DsInfixOstreamIteratorTest, Concatenation)
{
  const char * args[] = {
    "one", "two", "three", "four"
  };

  std::stringstream ss;
  ds::infix_ostream_iterator<const char *> it(ss, ", ");

  it = args[0];
  EXPECT_EQ(ss.str(), "one");
  ++it = args[1];
  EXPECT_EQ(ss.str(), "one, two");
  ds::infix_ostream_iterator<const char *> it_other(it);
  it_other++ = args[2];
  EXPECT_EQ(ss.str(), "one, two, three");
  *(it_other++) = args[3];
  EXPECT_EQ(ss.str(), "one, two, three, four");
}

}

