//
// Created by gsiekaniec on 10/20/19.
//

#ifndef SORTED_VECTOR_SORTED_VECTOR_H
#define SORTED_VECTOR_SORTED_VECTOR_H

#include <vector>
#include <algorithm>

template <typename T, bool RemoveDuplicates = true, typename Less = std::less<T>>
class sorted_vector
{
public:

    typedef typename std::vector<T>::iterator                   iterator;
    typedef typename std::vector<T>::const_iterator             const_iterator;
    typedef typename std::vector<T>::reverse_iterator           reverse_iterator;
    typedef typename std::vector<T>::const_reverse_iterator	    const_reverse_iterator;
    typedef typename std::vector<T>::size_type                  size_type;
    typedef typename std::vector<T>::value_type                 value_type;

    virtual ~sorted_vector() = default;

    /**
     *  @brief  Creates a %vector with no elements.
     */
    sorted_vector() = default;

    /**
     *  @brief  Builds a %vector from a range.
     *  @param  first  An input iterator.
     *  @param  ast  An input iterator.
     *
     *  Create a %vector consisting of copies of the elements from
     *  [first,last).
    */
    sorted_vector(iterator first, iterator last)
    : vec_(first, last)
    {
        if(RemoveDuplicates) { erase_duplicates_and_sort_(); }
        else { sort_(); }
    }

    /**
     *  @brief  %Vector copy constructor.
     *  @param  other  A %vector of identical element and allocator types.
     *
     *  All the elements of @a other are copied, but any unused capacity in
     *  @a other  will not be copied
     *  (i.e. capacity() == size() in the new %vector).
     *
     *  The newly-created %vector uses a copy of the allocator object used
     *  by @a other (unless the allocator traits dictate a different object).
     */
    sorted_vector(sorted_vector &) = default;

    /**
     *  @brief  %Vector move constructor.
     *
     *  The newly-created %vector contains the exact contents of the
     *  moved instance.
     *  The contents of the moved instance are a valid, but unspecified
     *  %vector.
     */
    sorted_vector(sorted_vector &&) noexcept = default;

    /**
     *  @brief  Builds a %vector from an initializer list.
     *  @param  l  An initializer_list.
     *
     *  Create a %vector consisting of copies of the elements in the
     *  initializer_list @a l.
     *
     *  This will call the element type's copy constructor N times
     *  (where N is @a l.size()) and do no memory reallocation.
     */
    sorted_vector(std::initializer_list<T> l)
    : vec_(l)
    {}

    sorted_vector& operator=(const sorted_vector & other) = default;

    /**
     *  @brief  %Vector move assignment operator.
     *  @param  other  A %vector of identical element and allocator types.
     *
     *  The contents of @a other are moved into this %vector (without copying,
     *  if the allocators permit it).
     *  Afterwards @a other is a valid, but unspecified %vector.
     *
     *  Whether the allocator is moved depends on the allocator traits.
     */
    sorted_vector& operator=(sorted_vector && other) noexcept = default;

    void insert(T & el)
    {
        if(RemoveDuplicates && contains(el)) { return; }
        vec_.push_back(el);
        sort_();
    }

    void insert(T && el)
    {
        if(RemoveDuplicates && contains(el)) { return; }
        vec_.emplace_back(el);
        sort_();
    }

    void insert(iterator first, iterator last)
    {
        vec_.insert(
                vec_.end(),
                first, last
                );
        if(RemoveDuplicates) { erase_duplicates_and_sort_(); }
        else { sort_(); }
    }

    /**
     *  @brief  Inserts an object in %vector.
     *  @param  el  Element to be inserted.
     *
     *  This function will insert a copy of the given rvalue of @a el.
     *  Vector will be sorted after operation finishes.
     */
    void emplace_back(value_type && el)
    {
        if(RemoveDuplicates && contains(el)) { return; }
        vec_.emplace_back(el);
        sort_();
    }

    /**
     *  @brief Checks if sorted vector contains element.
     *  @param el value of the element to search for
     *  Return `true` if sorted vector contains an element @a el, otherwise `false`.
     */
    bool contains(const value_type & el) const
    {
        return std::binary_search(
                vec_.cbegin(), vec_.cend(),
                el,
                Less());
    }

    /**
     *  Returns a read/write iterator that points to the first
     *  element in the %vector.  Iteration is done in ordinary
     *  element order.
     */
    iterator begin()
    {
        return vec_.begin();
    }

    /**
     *  Returns a read-only (constant) iterator that points to the
     *  first element in the %vector.  Iteration is done in ordinary
     *  element order.
     */
    const_iterator begin() const
    {
        return vec_.begin();
    }

    iterator end()
    {
        return vec_.end();
    }

    const_iterator end() const
    {
        return vec_.end();
    }

    /**
     *  Returns a read/write reverse iterator that points to the
     *  last element in the %vector.  Iteration is done in reverse
     *  element order.
     */
    reverse_iterator rbegin()
    {
        return vec_.rbegin();
    }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to the last element in the %vector.  Iteration is done in
     *  reverse element order.
     */
    const_reverse_iterator rbegin() const
    {
        return vec_.rbegin();
    }

    /**
     *  Returns a read/write reverse iterator that points to one
     *  before the first element in the %vector.  Iteration is done
     *  in reverse element order.
     */
    reverse_iterator rend()
    {
        return vec_.rend();
    }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to one before the first element in the %vector.  Iteration
     *  is done in reverse element order.
     */
    const_reverse_iterator rend() const
    {
        return vec_.end();
    }

    /**
     *  Returns a read-only (constant) iterator that points to the
     *  first element in the %vector.  Iteration is done in ordinary
     *  element order.
     */
    const_iterator cbegin() const noexcept
    {
        return vec_.cbegin();
    }

    /**
     *  Returns a read-only (constant) iterator that points one past
     *  the last element in the %vector.  Iteration is done in
     *  ordinary element order.
     */
    const_iterator cend() const noexcept
    {
        return vec_.cend();
    }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to the last element in the %vector.  Iteration is done in
     *  reverse element order.
     */
    const_reverse_iterator crbegin() const noexcept
    {
        return vec_.crbegin();
    }

    /**
     *  Returns a read-only (constant) reverse iterator that points
     *  to one before the first element in the %vector.  Iteration
     *  is done in reverse element order.
     */
    const_reverse_iterator crend() const noexcept
    {
        return vec_.crend();
    }

    iterator find(const value_type & el)
    {
        return std::lower_bound(
                vec_.begin(), vec_.end(),
                el,
                Less());
    }

    /**
     *  Returns true if the %vector is empty.  (Thus begin() would
     *  equal end().)
     */
    bool empty() const noexcept
    {
        return vec_.empty();
    }

    iterator erase(iterator itr)
    {
        return vec_.erase(itr);
    }

    size_type erase(const value_type & el)
    {
        auto it = find(el);
        if(it != vec_.end()) {
          vec_.erase(it);
          return 1;
        }
        return 0;
    }

    void clear() noexcept
    {
        vec_.clear();
    }

    /**  Returns the number of elements in the %vector.  */
    size_type size() const noexcept
    {
        return vec_.size();
    }

    /**  A non-binding request to reduce capacity() to size().  */
    void shrink_to_fit()
    {
        vec_.shrink_to_fit();
    }

    const value_type* data() const noexcept
    {
        return vec_.data();
    }

    T* data() noexcept
    {
        return vec_.data();
    }

    struct Equal
    {
        bool operator()(const value_type & el_lhs, const T & el_rhs) const
        {
            return !Less()(el_lhs, el_rhs) && !Less()(el_rhs, el_lhs);
        }
    };

private:

    void sort_()
    {
        std::sort(vec_.begin(), vec_.end(), Less());
    }

    void erase_duplicates_and_sort_()
    {
        sort_();

        vec_.erase(
                std::unique(vec_.begin(), vec_.end(), Equal()),
                vec_.end()
        );
    }

    std::vector<T> vec_;
};

template <typename T, bool SetLike = true, typename Compare = std::less<T>>
bool operator==(const sorted_vector<T, SetLike, Compare> & lhs, const sorted_vector<T, SetLike, Compare> & rhs)
{
    return std::equal(
            std::cbegin(lhs), std::cend(lhs),
            std::cbegin(rhs), std::cend(rhs),
            typename sorted_vector<T, SetLike, Compare>::Equal()
    );
}

template <typename T, bool SetLike = true, typename Compare = std::less<T>>
bool operator!=(const sorted_vector<T, SetLike, Compare> & lhs, const sorted_vector<T, SetLike, Compare> & rhs) {
    return !(lhs == rhs);
}

#endif //SORTED_VECTOR_SORTED_VECTOR_H
