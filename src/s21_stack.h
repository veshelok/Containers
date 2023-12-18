#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <cstddef>
#include <initializer_list>
#include <utility>

#include "s21_list.h"

namespace s21 {

template <typename T>
class Stack {
 public:
  using ValueType = T;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = std::size_t;
  Stack() {}
  explicit Stack(std::initializer_list<T> const& items) : list_{items} {}
  Stack(const Stack& other) { *this = other; }
  Stack(Stack&& other) { *this = std::move(other); }
  Stack& operator=(const Stack& other);
  Stack& operator=(Stack&& other);
  ~Stack() {}
  T& Top() { return list_.Back(); }
  const T& Top() const { return list_.Back(); }
  bool Empty() const { return list_.Empty(); }
  SizeType Size() { return list_.Size(); }
  void Push(const T& value) { list_.PushBack(value); }
  void Pop() { list_.PopBack(); }
  void Swap(Stack& other) {
    if (this == &other) {
      return;
    }
    list_.Swap(other.list_);
  }

 private:
    List<T> list_{};
};

template <typename T>
typename Stack<T>::Stack& Stack<T>::operator=(const Stack& other) {
  if (this == &other) {
    return *this;
  }
  list_ = other.list_;
  return *this;
}

template <typename T>
typename Stack<T>::Stack& Stack<T>::operator=(Stack&& other) {
  if (this == &other) {
    return *this;
  }
  list_.Swap(other);
  return *this;
}

}  // namespace s21

#endif  // SRC_S21_STACK_H_
