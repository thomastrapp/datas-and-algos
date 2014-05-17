#ifndef AL_BOYER_MOORE_SUBSTRING_H
#define AL_BOYER_MOORE_SUBSTRING_H

// http://stackoverflow.com/questions/6207819/boyer-moore-algorithm-understanding-and-example#6209778
// http://stackoverflow.com/questions/19345263/boyer-moore-good-suffix-heuristics#19440319/
// http://www.iti.fh-flensburg.de/lang/algorithmen/pattern/bmen.htm

#include <iterator>
#include <vector>
#include <type_traits>
#include <limits>

#include "bm/static-skip-table.h"
#include "bm/dynamic-skip-table.h"

namespace al
{

template<
  typename p_iter,
  typename p_diff_type = typename std::iterator_traits<p_iter>::difference_type, 
  typename p_char_type = typename std::iterator_traits<p_iter>::value_type,
  // choose a static skip table (std::array) for small alphabets (e.g. char)
  // choose a dynamic skip table (std::unordered_map) for everything else
  typename table_type = typename std::conditional<
    std::is_integral<p_char_type>::value && sizeof(p_char_type) < 2,
    bm::static_skip_table<p_char_type, p_diff_type>,
    bm::dynamic_skip_table<p_char_type, p_diff_type>
  >::type
>
class boyer_moore_substring
{
  public:
    boyer_moore_substring(p_iter begin, p_iter end)
    : p_begin(begin),
      p_end(end),
      pattern_len(std::distance(begin, end)),
      skip(this->pattern_len, -1),
      suffix(this->pattern_len + 1U)
    {
      this->fill_skip(begin, end);
      this->fill_suffix(begin, end);
    }

    template<
      typename s_iter,
      // we can only work with strings having the same type as the pattern
      typename = typename std::enable_if<
        std::is_same<
          typename std::iterator_traits<s_iter>::value_type,
          p_char_type
        >::value
      >::type
    >
    s_iter strstr(s_iter s_begin, s_iter s_end) const
    {
      typedef typename std::iterator_traits<s_iter>::difference_type s_diff_type;

      const s_diff_type str_len = std::distance(s_begin, s_end);

      if( this->pattern_len > str_len || str_len < 1 )
        return s_end;

      if( this->pattern_len < 1 )
        return s_begin;

      s_iter current = s_begin;
      s_iter last = s_end - this->pattern_len;
      s_diff_type j, k, m;

      while( current <= last )
      {
        j = this->pattern_len;
        while( this->p_begin[j - 1] == current[j - 1] )
        {
          --j;
          if( j == 0 )
            return current;
        }

        k = this->skip.get(current[j - 1]);
        m = j - k - 1;
        if( k < j && m > this->suffix.at(j) )
        {
          current += m;
        }
        else
        {
          current += this->suffix.at(j);
        }
      }
      return s_end;
    }

  private:
    const p_iter p_begin;
    const p_iter p_end;
    const p_diff_type pattern_len;
    table_type skip;
    std::vector<p_diff_type> suffix;

    void fill_skip(p_iter begin, p_iter end)
    {
      p_diff_type i = 0;
      while( begin != end )
      {
        this->skip.set(*begin, i++);
        ++begin;
      }
    }

    void fill_suffix(p_iter begin, p_iter end)
    {
      if( this->pattern_len )
      {
        auto prefix = this->get_prefix(begin, end);
        auto reversed_prefix = this->get_prefix(
          std::reverse_iterator<p_iter>(end),
          std::reverse_iterator<p_iter>(begin)
        );

        for(p_diff_type i = 0; i <= this->pattern_len; ++i)
          this->suffix.at(i) = this->pattern_len - prefix.at(this->pattern_len - 1);

        for(p_diff_type i = 0; i < this->pattern_len; ++i)
        {
          p_diff_type j = this->pattern_len - reversed_prefix.at(i);
          p_diff_type k = i - reversed_prefix.at(i) + 1;

          if( this->suffix.at(j) > k )
            this->suffix.at(j) = k;
        }
      }
    }

    template<typename iter>
    std::vector<p_diff_type> get_prefix(iter begin, iter end)
    {
      std::vector<p_diff_type> prefix(begin, end);

      p_diff_type j = 0;
      prefix.at(0) = 0;
      for(p_diff_type i = 1; i < this->pattern_len; ++i)
      {
        while( j > 0 && (begin + j != begin + i) )
          j = prefix.at(j - 1);

        if( begin + j == begin + i )
          ++j;

        prefix.at(i) = j;
      }

      // performance assumption: prefix will be moved to the caller
      return prefix;
    }
};

}

#endif
