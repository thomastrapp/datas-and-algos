#ifndef DS_STACK_H
#define DS_STACK_H

#include <utility>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace ds {

template<
  class value_type, 
  class container_type = std::vector<value_type>
>
class stack
{
public:
  stack()
  : cont()
  {
  }

  stack(const stack<value_type, container_type>& other)
  : cont(other.cont)
  {
  }

  stack(stack<value_type, container_type>&& other)
  : cont(std::move(other.cont))
  {
  }

  stack<value_type, container_type>& 
  operator=(stack<value_type, container_type> other)
  {
    this->swap(*this, other);
    return *this;
  }

  bool empty() const
  {
    return this->cont.empty();
  }

  typename container_type::size_type size() const
  {
    return this->cont.size();
  }

  const value_type& top() const
  {
    if( this->cont.empty() )
      throw std::out_of_range("cannot top, stack is empty");

    return this->cont.back();
  }

  value_type& top()
  {
    if( this->cont.empty() )
      throw std::out_of_range("cannot top, stack is empty");

    return this->cont.back();
  }

  void pop()
  {
    if( this->cont.empty() )
      throw std::out_of_range("cannot pop, stack is empty");

    this->cont.pop_back();
  }

  void push(const value_type& elem)
  {
    this->cont.push_back(elem);
  }

private:
  void swap(
    stack<value_type, container_type>& left, 
    stack<value_type, container_type>& right
  )
  {
    using std::swap;
    swap(left.cont, right.cont);
  }

  container_type cont;
};


}

#endif // DS_STACK_H
