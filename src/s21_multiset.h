#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include <initializer_list>

#include "binary_search_tree.h"
#include "s21_vector.h"

namespace s21 {

template <typename T>
class Multiset : public BinarySearchTree<T> {
 public:
  using KeyType = T;
  using ValueType = T;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
  using Iterator = typename BinarySearchTree<ValueType>::Iterator;
  using ConstIterator = typename BinarySearchTree<ValueType>::ConstIterator;
  using SizeType = typename BinarySearchTree<ValueType>::SizeType;
  explicit Multiset(std::initializer_list<T> const& items);
  void Merge(Multiset& other);  // NOLINT(runtime/references)
  SizeType Count(const T& key) const;
  std::pair<Iterator, Iterator> EqualRange(const T& key) const;
  Iterator LowerBound(const T& key) const;
  Iterator UpperBound(const T& key) const;

  template <typename... Args>
  s21::Vector<Iterator> Emplace(Args&&... args);
};

template <typename T>
Multiset<T>::Multiset(std::initializer_list<T> const& items) {
  for (auto item : items) {
    this->Insert(item);
  }
}

template <typename T>
void Multiset<T>::Merge(Multiset& other) {  // NOLINT(runtime/references)
  if (this == &other) {
    return;
  }
  for (auto iter {other.begin()}; iter != other.end(); ) {
    this->MoveNodeFromOtherTree(iter++, other);
  }
}

template <typename T>
typename Multiset<T>::SizeType Multiset<T>::Count(const T& key) const {
  auto range_pair {EqualRange(key)};
  SizeType counter{0};
  for (; range_pair.first != range_pair.second; ++range_pair.first) {
    ++counter;
  }
  return counter;
}

template <typename T>
auto Multiset<T>::EqualRange(const T& key) const ->
    std::pair<typename Multiset<T>::Iterator, typename Multiset<T>::Iterator> {
  auto first_iter {this->Find(key)};
  auto second_iter {first_iter};
  if (first_iter != this->end()) {
    while (second_iter != this->end()) {
      if (*second_iter != key) {
        break;
      }
      ++second_iter;
    }
  }
  return {first_iter, second_iter};
}

template <typename T>
typename Multiset<T>::Iterator Multiset<T>::LowerBound(const T& key) const {
  return EqualRange(key).first;
}

template <typename T>
typename Multiset<T>::Iterator Multiset<T>::UpperBound(const T& key) const {
  return EqualRange(key).second;
}

template <typename T>
template <typename... Args>
Vector<typename Multiset<T>::Iterator> Multiset<T>::Emplace(Args&&... args) {
  s21::Vector<Iterator> returnable_vector;
  const ValueType args_data[sizeof...(args)] {args...};
  for (SizeType i {0}; i < sizeof...(args); ++i) {
    returnable_vector.PushBack(this->Insert(args_data[i]));
  }
  return returnable_vector;
}

}  // namespace s21

#endif  // SRC_S21_MULTISET_H_
