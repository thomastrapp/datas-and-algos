#ifndef DS_BINARY_SEARCH_TREE_H
#define DS_BINARY_SEARCH_TREE_H

#include <stdexcept>
#include <utility>
#include <memory>
#include <iomanip>
#include <vector>

namespace ds
{

template<typename value_type>
class binary_search_tree
{
public:
  binary_search_tree()
  : parent(nullptr),
    left(nullptr),
    right(nullptr),
    val(value_type())
  {
  }

  explicit binary_search_tree(
    const value_type& value, 
    ds::binary_search_tree<value_type> * parent_tree = nullptr
  )
  : parent(parent_tree),
    left(nullptr),
    right(nullptr),
    val(value)
  {
  }

  binary_search_tree(ds::binary_search_tree<value_type>&& tree)
  : parent(std::move(tree.parent)),
    left(std::move(tree.left)),
    right(std::move(tree.right)),
    val(std::move(tree.val))
  {
  }

  binary_search_tree(const ds::binary_search_tree<value_type>& tree)
  : parent(nullptr),
    left(
      tree.left == nullptr ? nullptr :
      new ds::binary_search_tree<value_type>(*tree.left)
    ),
    right(
      tree.right == nullptr ? nullptr :
      new ds::binary_search_tree<value_type>(*tree.right)
    ),
    val(tree.val)
  {
    if( this->left )
      this->left->parent = this;
    if( this->right )
      this->right->parent = this;
  }

  explicit binary_search_tree(
    const std::vector<value_type>& values, 
    bool is_sorted
  )
  : parent(nullptr),
    left(nullptr),
    right(nullptr),
    val()
  {
    if( is_sorted )
      this->construct_from_sorted(values);
    else
      this->construct_from_unsorted(values);
  }

  ds::binary_search_tree<value_type>& 
  operator=(ds::binary_search_tree<value_type> tree)
  {
    this->swap(tree);
    return *this;
  }

  std::vector<value_type> to_vector() const
  {
    std::vector<value_type> vec;
    vec.push_back(this->val);

    if( this->left )
    {
      std::vector<value_type> vec_left = this->left->to_vector();
      vec.insert(vec.end(), vec_left.begin(), vec_left.end());
    }

    if( this->right )
    {
      std::vector<value_type> vec_right = this->right->to_vector();
      vec.insert(vec.end(), vec_right.begin(), vec_right.end());
    }

    return vec;
  }

  void print(std::ostream& out = std::cout) const
  {
    out << this->val << ": ";

    if( this->left )
      out << "L: " << this->left->val << "   ";
    if( this->right )
      out << "R: " << this->right->val << "   ";

    out << "\n";

    if( this->left )
      this->left->print(out);
    if( this->right )
      this->right->print(out);
  }

  value_type get_value() const
  {
    return this->val;
  }

  void set_value(const value_type& value)
  {
    this->val = value;
  }

  ds::binary_search_tree<value_type> * find(const value_type& value)
  {
    if( value == this->val )
    {
      return this;
    }
    else if( this->left && value < this->val ) 
    {
      return this->left->find(value);
    }
    else if( this->right && value > this->val )
    {
      return this->right->find(value);
    }
    else
    {
      return nullptr;
    }
  }

  void destroy()
  {
    if( !this->parent && !this->right && !this->left )
    {
      throw std::domain_error("cannot destroy last element");
    }

    if( !this->right && !this->left )
    {
      this->parent->swap_child(
        this, 
        nullptr
      );
    }
    else if( this->right && this->left )
    {
      ds::binary_search_tree<value_type> * right_min = this->right->find_min();
      this->val = right_min->val;
      right_min->destroy();
    }
    else if( this->right )
    {
      if( this->parent )
      {
        this->parent->swap_child(this, &(this->right));
        this->right.reset(nullptr);
      }
      else
      {
        ds::binary_search_tree<value_type> * right_min = this->right->find_min();
        this->val = right_min->val;
        right_min->destroy();
      }
    }
    else // if( this->left )
    {
      if( this->parent )
      {
        this->parent->swap_child(this, &(this->left));
        this->left.reset(nullptr);
      }
      else
      {
        ds::binary_search_tree<value_type> * left_max = this->left->find_max();
        this->val = left_max->val;
        left_max->destroy();
      }
    }
  }

  ds::binary_search_tree<value_type> * insert(const value_type& value)
  {
    if( value < this->val )
    {
      if( this->left )
      {
        return this->left->insert(value);
      }
      else
      {
        this->left.reset(new ds::binary_search_tree<value_type>(value, this));
        return this->left.get();
      }
    }
    else if( value > this->val )
    {
      if( this->right )
      {
        return this->right->insert(value);
      }
      else
      {
        this->right.reset(new ds::binary_search_tree<value_type>(value, this));
        return this->right.get();
      }
    }
    else
    {
      throw std::domain_error("cannot add duplicate");
    }
  }

private:
  void swap_child(
    ds::binary_search_tree<value_type> * child, 
    std::unique_ptr<ds::binary_search_tree<value_type>> * replacement
  )
  {
    if( this->left && this->left.get() == child )
    {
      if( replacement )
        this->left.swap(*replacement);
      else
        this->left.reset(nullptr);

      if( this->left )
        this->left->parent = this;
    }
    else if( this->right && this->right.get() == child )
    {
      if( replacement )
        this->right.swap(*replacement);
      else
        this->right.reset(nullptr);

      if( this->right )
        this->right->parent = this;
    }
    else 
    {
      throw std::domain_error("unknown child, unable to replace");
    }
  }

  template<typename input_iter>
  void append_sorted(
    input_iter left_start, input_iter left_stop,
    input_iter right_start, input_iter right_stop
  )
  {
    typedef typename std::iterator_traits<input_iter>::difference_type diff_type;

    if( left_start != left_stop )
    {
      const diff_type size = left_stop - left_start;
      const input_iter center = left_start + size / 2;

      if( *center >= this->val )
        throw std::domain_error("input is unsorted");

      this->left.reset(
        new ds::binary_search_tree<value_type>(*center, this)
      );
      if( size > 1 )
      this->left->append_sorted(
        left_start, center, 
        center + 1, left_stop
      );
    }

    if( right_start != right_stop )
    {
      const diff_type size = right_stop - right_start;
      const input_iter center = right_start + size / 2;

      if( *center <= this->val )
        throw std::domain_error("input is unsorted");

      this->right.reset(
        new ds::binary_search_tree<value_type>(*center, this)
      );
      if( size > 1 )
      this->right->append_sorted(
        right_start, center, 
        center + 1, right_stop
      );
    }
  }

  void construct_from_unsorted(const std::vector<value_type>& values)
  {
    typename std::vector<value_type>::const_iterator iter(values.begin());
    if( iter != values.end() )
    {
      this->val = *iter;
      ++iter;
    }

    for(; iter != values.end(); ++iter)
    {
      this->insert(*iter);
    }
  }

  void construct_from_sorted(const std::vector<value_type>& values)
  {
    typedef typename std::iterator_traits<
      typename std::vector<value_type>::const_iterator
    >::difference_type diff_type;

    const diff_type size = values.end() - values.begin();
    const diff_type half = size / 2;

    if( size > 0 )
    {
      this->val = *(values.begin() + half);
      this->append_sorted(
        values.begin(), values.begin() + half,
        values.begin() + half + 1, values.end()
      );
    }
  }

  ds::binary_search_tree<value_type> * find_max()
  {
    return this->right ? this->right->find_max() : this;
  }

  ds::binary_search_tree<value_type> * find_min()
  {
    return this->left ? this->left->find_min() : this;
  }

  void swap(ds::binary_search_tree<value_type>& tree)
  {
    std::swap(this->parent, tree.parent);
    std::swap(this->left, tree.left);
    std::swap(this->right, tree.right);
    std::swap(this->val, tree.val);
  }

  ds::binary_search_tree<value_type> * parent;
  std::unique_ptr<ds::binary_search_tree<value_type>> left;
  std::unique_ptr<ds::binary_search_tree<value_type>> right;

  value_type val;
};


}

#endif // DS_BINARY_SEARCH_TREE_H
