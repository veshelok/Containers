#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <initializer_list>

#include "binary_search_tree.h"
#include "s21_vector.h"

namespace s21 {

template <typename T>
class Set : public BinarySearchTree<T> {
 public:
  using KeyType = T;
  using ValueType = T;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
  using Iterator = typename BinarySearchTree<ValueType>::Iterator;
  using ConstIterator = typename BinarySearchTree<ValueType>::ConstIterator;
  using SizeType = typename BinarySearchTree<ValueType>::SizeType;
  explicit Set(std::initializer_list<T> items);
  std::pair<Iterator, bool> Insert(const T& value);
  void Merge(Set& other);  // NOLINT(runtime/references)

  template<typename... Args>
  s21::Vector<std::pair<Iterator, bool>> Emplace(Args&&... args);
};

template <typename T>
Set<T>::Set(std::initializer_list<T> items) {
  for (const auto& item : items) {
    Insert(item);
  }
}

template <typename T>
auto Set<T>::Insert(const T& value) ->
    std::pair<typename Set<T>::Iterator, bool> {
  auto iter {this->Find(value)};
  if (iter == this->end()) {
    return {BinarySearchTree<T>::Insert(value), true};
  }
  return {iter, false};
}

template <typename T>
void Set<T>::Merge(Set& other) {  // NOLINT(runtime/references)
  if (this == &other) {
    return;
  }
  for (auto iter {other.begin()}; iter != other.end(); ) {
    if (!this->Contains(*iter)) {
      this->MoveNodeFromOtherTree(iter++, other);
    } else {
      ++iter;
    }
  }
}

template <typename T>
template <typename... Args>
Vector<std::pair<typename s21::Set<T>::Iterator, bool>> Set<T>::Emplace(
    Args&&... args) {
  s21::Vector<std::pair<Iterator, bool>> returnable_vector{};
  const ValueType args_data[sizeof...(args)] {args...};
  for (SizeType i {0}; i < sizeof...(args); ++i) {
    returnable_vector.PushBack(Insert(args_data[i]));
  }
  return returnable_vector;
}

}  // namespace s21

#endif  // SRC_S21_SET_H_
