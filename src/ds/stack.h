#ifndef DS_STACK_H
#define DS_STACK_H

#include <utility>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace ds {

template<
  class T, 
  class C = std::vector<T>
>
class stack
{
  public:
    stack()
      : cont()
    {}

    stack(const stack<T, C>& other)
      : cont(other.cont)
    {
    }

    stack(stack<T, C>&& other)
      : cont(std::move(other.cont))
    {
      other.cont.clear();
    }

    stack<T, C>& operator=(stack<T, C> other)
    {
      this->swap(*this, other);
      return *this;
    }

    bool empty() const
    {
      return this->cont.empty();
    }

    typename C::size_type size() const
    {
      return this->cont.size();
    }

    typename C::value_type top() const
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

    void push(const typename C::value_type& elem)
    {
      this->cont.push_back(elem);
    }

  private:
    void swap(stack<T, C>& left, stack<T, C>& right)
    {
      using std::swap;
      swap(left.cont, right.cont);
    }

    C cont;
};


}

#endif // DS_STACK_H
