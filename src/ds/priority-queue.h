#ifndef DS_PRIORITY_QUEUE
#define DS_PRIORITY_QUEUE

#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

namespace ds 
{

template<
  typename value_type, 
  typename container_type = std::vector<value_type>, 
  typename comparison_type = std::less<value_type>
>
class priority_queue 
{
public:
  priority_queue()
  : container()
  {
  }

  explicit priority_queue(size_t content_size)
  : container(content_size)
  {
  }

  explicit priority_queue(const std::vector<value_type>& values)
  : container(values)
  {
    std::make_heap(
      this->container.begin(), 
      this->container.end(),
      comparison_type()
    );
  }

  priority_queue(
    const priority_queue<value_type, container_type, comparison_type>& queue
  )
  : container(queue.container)
  {
  }

  priority_queue(
    priority_queue<value_type, container_type, comparison_type>&& queue
  )
  : container(std::move(queue.container))
  {
  }

  priority_queue& operator=(
    priority_queue<value_type, container_type, comparison_type> queue
  )
  {
    this->swap(*this, queue);
    return *this;
  }

  bool empty() const
  {
    return this->container.empty();
  }

  size_t size() const
  {
    return this->container.size();
  }

  value_type top() const
  {
    return this->container.front();
  }

  void push(const value_type& value)
  {
    this->container.push_back(value);
    std::push_heap(
      this->container.begin(), 
      this->container.end(), 
      comparison_type()
    );
  }

  void pop()
  {
    std::pop_heap(
      this->container.begin(), 
      this->container.end(), 
      comparison_type()
    );
    this->container.pop_back();
  }

  void print(std::ostream& out = std::cout) const
  {
    for(const auto& v : this->container)
    {
      out << v << " ";
    }
    out << std::endl;
  }

private:
  void swap(
    priority_queue<value_type, container_type, comparison_type>& left,
    priority_queue<value_type, container_type, comparison_type>& right
  )
  {
    std::swap(left.container, right.container);
  }

  container_type container;
};


}

#endif // DS_PRIORITY_QUEUE
