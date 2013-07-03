#ifndef AL_MERGESORT_H
#define AL_MERGESORT_H

#include <iterator>
#include <algorithm>
#include <vector>

namespace al
{

template<typename in_iter, typename out_iter>
void mergesort_merge(
  in_iter left, 
  in_iter left_end, 
  in_iter right, 
  in_iter right_end,
  out_iter out
)
{
  while( left < left_end || right < right_end )
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
    else if( right != right_end )
    {
      *out = *right;
      ++out;
      ++right;
    }
  }
}

template<typename iter>
void mergesort(iter begin, iter end)
{
  ssize_t size = end - begin;

  if( size < 2 )
    return;

  ssize_t center = size / 2;

  mergesort(begin, begin + center);
  mergesort(begin + center, end);

  std::vector<typename std::iterator_traits<iter>::value_type> values;
  values.reserve(static_cast<size_t>(size));

  mergesort_merge(
    begin, begin + center, 
    begin + center, end, 
    std::back_inserter(values)
  );

  std::copy(values.begin(), values.end(), begin);
}


}

#endif // AL_MERGESORT_H
