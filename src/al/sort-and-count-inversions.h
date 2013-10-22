#ifndef AL_SORT_AND_COUNT_INVERSIONS_H
#define AL_SORT_AND_COUNT_INVERSIONS_H

#include <cstddef>
#include <cstring>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdint>

namespace al {

// Maximum amount of inversions in an array with length n: n * (n - 1) / 2
// Possible defense (not implemented): 
//  if( std::numeric_limits<counter>::is_specialized )
//  {
//    // If provided type cannot hold amount of possible inversions
//    if( std::numeric_limits<counter>::max() < size * (size - 1) / 2 )
//    {
//      throw std::out_of_range("provide wider counter type");
//    }
//  }

template<typename in_iter, typename out_iter, typename counter = uint64_t>
counter sort_and_count_inversions_merge(
  in_iter left, 
  in_iter left_end,
  in_iter right,
  in_iter right_end,
  out_iter out
)
{
  counter inversions = 0;
  while( left != left_end || right != right_end )
  {
    if( left != left_end && right != right_end )
    {
      if( *left <= *right )
      {
        *out = *left;
        ++out;
        ++left;
      }
      else
      {
        typename std::iterator_traits<in_iter>::difference_type
          left_to_go = left_end - left;
        inversions += static_cast<counter>(left_to_go);

        *out = *right;
        ++out;
        ++right;
      }
    }
    else if( left != left_end )
    {
      *out = *left;
      ++out;
      ++left;
    }
    else
    {
      *out = *right;
      ++out;
      ++right;
    }
  }

  return inversions;
}

template<typename iter, typename counter = uint64_t>
counter sort_and_count_inversions(iter begin, iter end)
{
  typedef typename std::iterator_traits<iter>::difference_type iter_range;
  iter_range size = end - begin;

  if( size < 2 )
    return 0;

  counter inversions = 0;
  iter_range center = size / 2;
  inversions += sort_and_count_inversions(begin, begin + center);
  inversions += sort_and_count_inversions(begin + center, end);

  std::vector<typename std::iterator_traits<iter>::value_type> v;
  v.reserve(static_cast<size_t>(size));

  inversions += sort_and_count_inversions_merge(
    begin, begin + center, 
    begin + center, end,
    std::back_inserter(v)
  );

  std::copy(v.begin(), v.end(), begin);

  return inversions;
}


}

#endif
