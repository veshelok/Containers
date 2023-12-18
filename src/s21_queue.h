#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include <cstddef>
#include <initializer_list>
#include <utility>

#include "s21_list.h"

namespace s21 {

template <typename T>
class Queue {
 public:
  using ValueType = T;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = std::size_t;
  Queue() {}
  explicit Queue(std::initializer_list<T> const& items) : list_{items} {}
  Queue(const Queue& other) { *this = other; }
  Queue(Queue&& other) { *this = std::move(other); }
  Queue& operator=(const Queue& other);
  Queue& operator=(Queue&& other);
  ~Queue() {}
  T& Front() { return list_.Front(); }
  T& Back() { return list_.Back(); }
  const T& Front() const { return list_.Front(); }
  const T& Back() const { return list_.Back(); }
  bool Empty() const { return list_.Empty(); }
  SizeType Size() const { return list_.Size(); }
  void Push(const T& value) { list_.PushBack(value); }
  void Pop() { list_.PopFront(); }
  void Swap(Queue& other) {
    if (this == &other) {
      return;
    }
    list_.Swap(other.list_);
  }

 private:
  List<T> list_{};
};

template <typename T>
typename Queue<T>::Queue& Queue<T>::operator=(const Queue& other) {
  if (this == &other) {
    return *this;
  }
  list_ = other.list_;
  return *this;
}

template <typename T>
typename Queue<T>::Queue& Queue<T>::operator=(Queue&& other) {
  if (this == &other) {
    return *this;
  }
  list_.Swap(other.list_);
  return *this;
}

}  // namespace s21

#endif  // SRC_S21_QUEUE_H_
