#ifndef AL_RADIXSORT_H
#define AL_RADIXSORT_H

#include <iterator>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <limits>

namespace al
{

template<typename cont>
// only allow containers containing unsigned integral types
typename std::enable_if<
  std::is_integral<typename cont::value_type>::value && 
  std::is_unsigned<typename cont::value_type>::value, 
  void
>::type radixsort(cont& values)
{
  typedef typename cont::value_type value_type;
  typedef std::numeric_limits<value_type> value_limits;
  typedef std::vector<std::vector<value_type>> bucket_container;
  constexpr unsigned int base_ten = 10U;
  constexpr value_type max_digits = value_limits::digits10 + 1;

  value_type shift_width = 1;
  for(value_type digit_index = 1; digit_index <= max_digits; ++digit_index)
  {
    // performance assumption: declaring the bucket_container inside the loop
    // is faster than placing it outside the loop and resetting its 
    // contents on every iteration
    bucket_container buckets(base_ten);

    bool is_all_done = true;
    for(const auto& value : values)
    {
      // shift value to the left by shift_width (base 10)
      const value_type base_ten_shifted = ( value / shift_width );

      // if we shifted so far that there's no value left we can 
      // return early
      is_all_done &= ( base_ten_shifted == 0 );

      const unsigned int bucket_index = static_cast<unsigned int>(
        // extract last digit
        base_ten_shifted % base_ten
      );

      buckets
        .at(bucket_index)
        .push_back(value)
      ;
    }

    typename cont::iterator it(values.begin());
    for(const auto& bucket : buckets)
    {
      it = std::copy(bucket.begin(), bucket.end(), it);
    }

    if( is_all_done )
      return;
    
    shift_width *= base_ten;
  }
}


}

#endif // AL_RADIXSORT_H
