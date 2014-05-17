#include <cstring>

#include "gtest/gtest.h"
#include "al/boyer-moore-substring.h"

#include "data/sample-text.h"

namespace {

namespace hlp {

  template<typename iter>
  using it_val_t = typename std::iterator_traits<iter>::value_type;

  template<typename iter>
  using it_diff_t = typename std::iterator_traits<iter>::difference_type;

  template<
    typename table_type,
    typename p_iter,
    typename s_iter
  >
  s_iter bm_strstr(p_iter p_begin, p_iter p_end, s_iter s_begin, s_iter s_end)
  {
    al::boyer_moore_substring<
      p_iter,
      it_diff_t<p_iter>,
      it_val_t<p_iter>,
      table_type
    > bm(p_begin, p_end);
    return bm.strstr(s_begin, s_end);
  }

  template<typename table_type>
  const char * bm_cc_strstr(const char * pattern, const char * corpus)
  {
    return bm_strstr<table_type>(pattern, pattern + strlen(pattern), corpus, corpus + strlen(corpus));
  }

  // boyer_moore_substring with forced skip table type static
  template<typename iter>
  using bm_static_table_type = 
  al::boyer_moore_substring<
    iter, 
    it_diff_t<iter>,
    it_val_t<iter>,
    al::bm::static_skip_table<
      it_val_t<iter>,
      it_diff_t<iter>
    >
  >;

  // boyer_moore_substring with forced skip table type dynamic
  template<typename iter>
  using bm_dynamic_table_type = 
  al::boyer_moore_substring<
    iter, 
    it_diff_t<iter>,
    it_val_t<iter>,
    al::bm::dynamic_skip_table<
      it_val_t<iter>,
      it_diff_t<iter>
    >
  >;
  
} // namespace hlp

// test skip table selection
template<typename T>
class AlBoyerMooreStaticTableTest : public ::testing::Test
{};
typedef ::testing::Types<const char *, std::string::iterator> types_for_static_table;
TYPED_TEST_CASE(AlBoyerMooreStaticTableTest, types_for_static_table);

TYPED_TEST(AlBoyerMooreStaticTableTest, UsesStaticTable)
{
  bool uses_static_table = std::is_same<
    // compare the type with automatic skip table selection
    al::boyer_moore_substring<TypeParam>,
    // to the type with forced static skip table
    hlp::bm_static_table_type<TypeParam>
  >::value;
  // if types are the same, the correct std::enable_if branch was chosen in 
  // boyer_moore_substring's template parameters
  EXPECT_TRUE(uses_static_table);

  bool uses_dynamic_table = std::is_same<
    al::boyer_moore_substring<TypeParam>,
    hlp::bm_dynamic_table_type<TypeParam>
  >::value;
  EXPECT_FALSE(uses_dynamic_table);
}

template<typename T>
class AlBoyerMooreDynamicTableTest : public ::testing::Test
{};
typedef ::testing::Types<uint16_t *, uint32_t *, uint64_t *> types_for_dynamic_table;
TYPED_TEST_CASE(AlBoyerMooreDynamicTableTest, types_for_dynamic_table);

TYPED_TEST(AlBoyerMooreDynamicTableTest, UsesDynamicTable)
{
  bool uses_dynamic_table = std::is_same<
    al::boyer_moore_substring<TypeParam>,
    hlp::bm_dynamic_table_type<TypeParam>
  >::value;
  EXPECT_TRUE(uses_dynamic_table);

  bool uses_static_table = std::is_same<
    al::boyer_moore_substring<TypeParam>,
    hlp::bm_static_table_type<TypeParam>
  >::value;
  EXPECT_FALSE(uses_static_table);
}

// test the substring algorithm
// run each test with the static skip table and the dynamic skip table
template<typename T>
class AlBoyerMooreSubstringTest : public ::testing::Test
{};
typedef ::testing::Types<
  al::bm::static_skip_table<hlp::it_val_t<const char *>, hlp::it_diff_t<const char *>>,
  al::bm::dynamic_skip_table<hlp::it_val_t<const char *>, hlp::it_diff_t<const char *>>
> table_types;
TYPED_TEST_CASE(AlBoyerMooreSubstringTest, table_types);

TYPED_TEST(AlBoyerMooreSubstringTest, EmptyPattern)
{
  const char * pattern = "";
  const char * corpus = "abababa";
  auto iter = hlp::bm_cc_strstr<TypeParam>(pattern, corpus);

  EXPECT_EQ(iter, corpus);
}

TYPED_TEST(AlBoyerMooreSubstringTest, EmptyCorpus)
{
  const char * pattern = "abababa";
  const char * corpus = "";
  auto iter = hlp::bm_cc_strstr<TypeParam>(pattern, corpus);

  EXPECT_EQ(iter, corpus);
}

TYPED_TEST(AlBoyerMooreSubstringTest, SingleCharPattern)
{
  const char * pattern = "a";

  const char * corpus = "a";
  auto iter = hlp::bm_cc_strstr<TypeParam>(pattern, corpus);
  EXPECT_EQ(iter, corpus);

  const char * corpus2 = "abbabbaabbba";
  auto iter2 = hlp::bm_cc_strstr<TypeParam>(pattern, corpus2);
  EXPECT_EQ(iter2, corpus2);
}

TYPED_TEST(AlBoyerMooreSubstringTest, FindsAllPatterns)
{
  const char * pattern = "pattern";
  const char * pattern_end = pattern + strlen(pattern);
  al::boyer_moore_substring<
    const char *,
    hlp::it_diff_t<const char *>,
    hlp::it_val_t<const char *>,
    TypeParam
  >
  bm(pattern, pattern_end);
  
  const char * corpus = 
    "pattern" 
    "ttern" 
    "pattern" 
    "pa" 
    "pattern" 
    "asdasdasder" 
    "pattern" 
    "pattt" 
    "lattern"
    "pattern" 
    "kattern";
  const char * corpus_end = corpus + strlen(corpus);
  size_t corpus_offsets[] = {
    0, 12, 21, 39, 58
  };
  int expected_matches = sizeof(corpus_offsets) / sizeof(corpus_offsets[0]);
  int matches = 0;

  const char * iter = corpus;
  while( (iter = bm.strstr(iter, iter + strlen(iter)) ) != corpus_end )
  {
    EXPECT_EQ(iter, corpus + corpus_offsets[matches]);
    EXPECT_EQ(strncmp(iter, pattern, strlen(pattern)), 0);
    iter += strlen(pattern);
    ++matches;
  }

  EXPECT_EQ(matches, expected_matches);
}

TYPED_TEST(AlBoyerMooreSubstringTest, BehavesLikeStdStringFind)
{
  const char * pattern = "Program";

  std::string std_sample(data::sample_text);
  al::boyer_moore_substring<
    const char *,
    hlp::it_diff_t<const char *>,
    hlp::it_val_t<const char *>,
    TypeParam
  > bm(pattern, pattern + strlen(pattern));

  size_t offset = 0;
  int matches = 0;

  const char * iter = data::sample_text;
  const char * iter_end = iter + strlen(data::sample_text);

  while( true )
  {
    offset = std_sample.find(pattern, offset);
    iter = bm.strstr(iter, iter_end);
    
    if( offset == std::string::npos || iter == iter_end )
    {
      EXPECT_EQ(iter, iter_end);
      EXPECT_EQ(offset, std::string::npos);
      break;
    }

    EXPECT_EQ(iter - data::sample_text, offset);
    EXPECT_EQ(std_sample.compare(offset, strlen(pattern), iter, strlen(pattern)), 0);

    offset += strlen(pattern);
    iter += strlen(pattern);
    matches++;
  }

  // if data::sample_text is broken, this will fail
  EXPECT_GE(matches, /* match at least */ 20);
}


}

