#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

#include "binary_search_tree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class Map : public BinarySearchTree<std::pair<const Key, T>> {
 public:
  using KeyType = Key;
  using MappedType = T;
  using ValueType = std::pair<const Key, T>;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
  using Iterator = typename BinarySearchTree<ValueType>::Iterator;
  using ConstIterator = typename BinarySearchTree<ValueType>::ConstIterator;
  using SizeType = typename BinarySearchTree<ValueType>::SizeType;
  explicit Map(std::initializer_list<ValueType> items);
  std::pair<Iterator, bool> Insert(const ValueType& value);
  std::pair<Iterator, bool> Insert(const Key& key, const T& obj);
  std::pair<Iterator, bool> InsertOrAssign(const Key& key, const T& obj);
  Iterator Find(const Key& key) const;
  void Merge(Map& other);  // NOLINT(runtime/references)

  T& At(const Key& key);
  const T& At(const Key& key) const;
  T& operator[](const Key& key);
  bool Contains(const Key& key) const { return Find(key) != this->end(); }

  template <typename...  Args>
  s21::Vector<std::pair<Iterator, bool>> Emplace(Args&&... args);
};

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<ValueType> items) {
  for (const auto& item : items) {
    Insert(item);
  }
}

template <typename Key, typename T>
auto Map<Key, T>::Insert(const ValueType& value) ->
    std::pair<typename Map<Key, T>::Iterator, bool> {
  return Insert(value.first, value.second);
}

template <typename Key, typename T>
auto Map<Key, T>::Insert(const Key& key, const T& obj) ->
    std::pair<typename Map<Key, T>::Iterator, bool> {
  auto iter {Find(key)};
  if (iter == this->end()) {
    iter = BinarySearchTree<ValueType>::Insert({key, obj});
    return {iter, true};
  }
  return  {iter, false};
}

template <typename Key, typename T>
auto Map<Key, T>::InsertOrAssign(const Key& key, const T& obj) ->
    std::pair<typename Map<Key, T>::Iterator, bool> {
  auto returnable_pair {Insert(key, obj)};
  if (returnable_pair.second == false) {
    returnable_pair.first.node_->value.second = obj;
  }
  return returnable_pair;
}

template <typename Key, typename T>
auto Map<Key, T>::Find(const Key& key) const ->
    typename Map<Key, T>::Iterator {
  typename BinarySearchTree<ValueType>::Node* node {this->root_};
  while (node != nullptr && node->value.first != key) {
    if (key < node->value.first) {
      node = node->left_child;
    } else {
      node = node->right_child;
    }
  }
  return Iterator(this, node);
}

template <typename Key, typename T>
void Map<Key, T>::Merge(Map& other) {  // NOLINT(runtime/references)
  if (this == &other) {
    return;
  }
  for (auto iter {other.begin()}; iter != other.end(); ) {
    if (!Contains((*iter).first)) {
      this->MoveNodeFromOtherTree(iter++, other);
    } else {
      ++iter;
    }
  }
}

template <typename Key, typename T>
T& Map<Key, T>::At(const Key& key) {
  auto iter {Find(key)};
  if (iter == this->end()) {
    throw std::out_of_range("There is no key");
  }
  return iter.node_->value.second;
}

template <typename Key, typename T>
const T& Map<Key, T>::At(const Key& key) const {
  auto iter {Find(key)};
  if (iter == this->end()) {
    throw std::out_of_range("There is no key");
  }
  return iter.node_->value.second;
}

template <typename Key, typename T>
T& Map<Key, T>::operator[](const Key& key) {
  auto iter {Find(key)};
  if (iter == this->end()) {
    iter = BinarySearchTree<ValueType>::Insert({key, T{}});
  }
  return iter.node_->value.second;
}

template <typename Key, typename T>
template <typename...  Args>
auto s21::Map<Key, T>::Emplace(Args&&... args) ->
    s21::Vector<std::pair<typename s21::Map<Key, T>::Iterator, bool>> {
  s21::Vector<std::pair<Iterator, bool>> returnable_vector{};
  const ValueType args_data[sizeof...(args)] {args...};
  for (SizeType i {0}; i < sizeof...(args); ++i) {
    returnable_vector.PushBack(Insert(args_data[i]));
  }
  return returnable_vector;
}

}  // namespace s21
#endif  // SRC_S21_MAP_H_
