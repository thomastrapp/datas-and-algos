#ifndef AL_COUNTING_SORT_H
#define AL_COUNTING_SORT_H

#include <type_traits>
#include <iterator>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <limits>

namespace al
{

template<
  typename iter,
  typename value_type = typename std::iterator_traits<iter>::value_type,
  // count_type must be able to hold the maximum number of duplicate occurrences of a single value
  typename count_type = size_t,
  typename = std::enable_if<
    // only allow types that are losslessly convertable to std::vector::size_type,
    // because each member of the input sequence will be used as an index
    std::is_integral<value_type>::value && 
    std::is_unsigned<value_type>::value, 
    void
  >
>
void counting_sort(iter begin, iter end)
{
  // create a bucket with size 'max element from input sequence' + 1
  // this bucket is then able to hold all possible inputs as its index
  auto max = std::max_element(begin, end);

  // empty sequence
  if( max == end )
    return;

  // since we need an index for each representable value, we have to exclude the maximum
  if( *max == std::numeric_limits<typename std::vector<count_type>::size_type>::max() )
  {
    throw std::overflow_error("member of input sequence equal to maximum of "
        "std::vector<count_type>::size_type");
  }
  
  std::vector<count_type> bucket(*max + 1, 0);

  auto elem_counter = [&bucket](value_type i) {
    bucket.at(i) += 1;
  };

  // count number of occurences of each bucket-index in the input sequence
  std::for_each(begin, end, elem_counter);

  value_type bucket_index = 0;
  while( bucket_index < bucket.size() && begin != end )
  {
    // for each bucket-value > 0, put its bucket-index into the input sequence,
    // until bucket-value amount of elements were put back
    for(value_type elem_count = 0; elem_count < bucket.at(bucket_index); ++elem_count)
    {
      *begin = bucket_index;
      ++begin;
    }
    ++bucket_index;
  }
}


}

#endif // AL_COUNTING_SORT_H
