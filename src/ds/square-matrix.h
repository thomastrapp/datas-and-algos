#ifndef DS_SQUARE_MATRIX_H
#define DS_SQUARE_MATRIX_H

#include <algorithm>
#include <array>
#include <vector>
#include <exception>
#include <iostream>
#include <iterator>
#include <cmath>

#include "al/strassen-matrix-multiply.h"

namespace ds {

template<typename value_type = int>
class square_matrix 
{
  public:
    typedef std::vector<value_type> container;
    typedef std::array<square_matrix, 4> split_result;

    explicit square_matrix(size_t matrix_width)
      : width(matrix_width),
        data(matrix_width * matrix_width, 0)
    {
      if( matrix_width < 1 )
        throw std::out_of_range("width must be at least 1");
    }

    square_matrix(const square_matrix& other)
      : width(other.width),
        data(other.data)
    {
    }

    square_matrix(square_matrix&& other)
      : width(other.width),
        data(std::move(other.data))
    {
      other.width = 0;
    }

    square_matrix(
      const square_matrix& top_left, 
      const square_matrix& top_right, 
      const square_matrix& bottom_left, 
      const square_matrix& bottom_right
    ) : width(top_left.width * 2),
        data(this->width * this->width, 0)
    {
      if( 
        top_left.width != top_right.width || 
        bottom_left.width != bottom_right.width || 
        top_right.width != bottom_right.width 
      )
      {
        throw std::out_of_range("inconsistent matrix size, combination impossible");
      }

      const size_t size = this->width * this->width;
      const size_t source_width = top_left.width;

      std::array<const square_matrix *, 4> source = {{
        &top_left,
        &top_right,
        &bottom_left,
        &bottom_right
      }};
      
      for(size_t i = 0; i < size; ++i)
      {
        // see also square_matrix<value_type>::square_split()
        
        // This is unneccessarily complex, but I wanted to remove all branches
        // just for kicks & giggles (and maybe speed :D)
        // If I wasn't the only one who cared for this code, I wouldn't do 
        // this without a (forged) benchmark, I promise!
        
        // the first pair of arrays (0 and 1) gets put into this matrix's
        // top half
        // the second pair of arrays (2 and 3) gets put into this matrix's
        // bottom half
        const bool top = i < size / 2;
        
        // the arrays on the left (0 and 2) get put into this matrix's left half
        // the arrays on the right (1 and 3) get put into this matrix's 
        // right half
        const bool odd = (i / source_width) & 1;
        
        // choose source_matrix 0 1 2 or 3
        const size_t source_matrix = 
          2 * static_cast<unsigned int>(!top) + 
          1 * static_cast<unsigned int>(odd)
        ;
        
        // index in the chosen source_matrix for this i
        const size_t index = (
            // map to row
            (i / this->width) * source_width 
            // map to column
            + (i % source_width) 
          ) 
          // map to the 4 input arrays
          % (size / 4)
        ;
        
        this->data[i] = source[source_matrix]->data[index];
      }
    }

    square_matrix& operator=(square_matrix other)
    {
      this->swap(*this, other);
      return *this;
    }

    value_type get(size_t row, size_t col) const
    {
      const size_t index = row * this->width + col;

      if( index >= data.size() )
        throw std::out_of_range("matrix index out of bounds");

      return data[index];
    }

    void set(size_t row, size_t col, value_type val)
    {
      const size_t index = row * this->width + col;

      if( index >= data.size() )
        throw std::out_of_range("matrix index out of bounds");

      data[index] = val;
    }

    square_matrix operator+(square_matrix other) const
    {
      if( other.width != this->width )
        throw std::out_of_range(
          "matrix width differs, addition impossible"
        );
      
      auto this_iter = this->data.begin();
      for(auto i = other.data.begin(); i != other.data.end(); ++i)
      {
        *i += *this_iter;
        ++this_iter;
      }

      return other;
    }

    square_matrix operator-(const square_matrix& right) const
    {
      if( right.width != this->width )
        throw std::out_of_range(
          "matrix width differs, subtraction impossible"
        );
      
      square_matrix left(*this);
      
      auto left_iter = left.data.begin();
      for(auto right_iter = right.data.begin(); right_iter != right.data.end(); ++right_iter)
      {
        *left_iter -= *right_iter;
        ++left_iter;
      }

      return left;
    }

    square_matrix operator*(const square_matrix& other) const
    {
      return al::strassen_matrix_multiply(*this, other);
    }
    
    bool operator==(const square_matrix& other) const
    {
      if( other.width != this->width )
        return false;
      
      return this->data == other.data;
    }
    
    bool operator!=(const square_matrix& other) const
    {
      return !this->operator==(other);
    }

    split_result square_split() const
    {
      if( this->width < 2 || (this->width & (this->width - 1)) != 0 )
        throw std::out_of_range("matrix width < 2 or not a power of two, "
          "square split impossible");

      const size_t size = this->width * this->width;
      const size_t result_width = this->width >> 1;

      split_result result = {{
        square_matrix<value_type>(result_width),
        square_matrix<value_type>(result_width),
        square_matrix<value_type>(result_width),
        square_matrix<value_type>(result_width)
      }};
      
      for(size_t i = 0; i < size; ++i)
      {
        // This is unneccessarily complex, but I wanted to remove all branches
        // just for kicks & giggles (and maybe speed :D)
        // If I wasn't the only one who cared for this code, I wouldn't do 
        // this without a (forged) benchmark, I promise!
        
        // the first half gets put into the first pair of arrays (0 and 1)
        // the second half gets put into the second pair of arrays (2 and 3)
        const bool top = i < size / 2;
        
        // map all odd half-rows to the left pair of arrays (0 and 2)
        // map all even half-rows to the rigth pair of arrays (1 and 3)
        const bool odd = (i / result_width) & 1;
        
        // choose result_matrix 0 1 2 or 3
        const size_t result_matrix = 
          2 * static_cast<unsigned int>(!top) + 
          1 * static_cast<unsigned int>(odd)
        ;
        
        // index in the chosen result_matrix for this i
        const size_t index = (
            // map to row
            (i / this->width) * result_width 
            // map to column
            + (i % result_width) 
          ) 
          // map to 4 arrays
          % (size / 4)
        ;
        
        result[result_matrix].data[index] = this->data[i];
      }
      
      return result;
    }

    void print(std::ostream& out = std::cout) const
    {
      for(size_t i = 0; i < this->data.size(); ++i)
      {
        if( i % this->width == 0 )
          out << "\n";

        out << this->data[i] << "\t";
      }

      out << "\n";
    }

    size_t get_width() const
    {
      return this->width;
    }

  private:
    void swap(square_matrix& left, square_matrix& right) const
    {
      using std::swap;
      swap(left.width, right.width);
      swap(left.data, right.data);
    }

    size_t width;
    container data;
};


}

#endif
