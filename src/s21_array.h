#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {

template <class T, std::size_t N>
class Array {
 public:
  using ValueType = T;
  using Reference = T&;
  using ConstReference = const T&;
  class ArrayIterator;
  class ConstArrayIterator;
  using Iterator = ArrayIterator;
  using ConstIterator = ConstArrayIterator;
  using SizeType = std::size_t;

  Array() {}
  explicit Array(std::initializer_list<ValueType> const& items);
  Array(const Array& other) { *this = other; }
  Array(Array&& other) { *this = std::move(other); }
  Array& operator=(const Array& other);
  Array& operator=(Array&& other);
  ~Array() {}

  T& At(SizeType pos);
  const T& At(SizeType pos) const;
  T& operator[](SizeType pos) { return arr_[pos]; }
  const T& operator[](SizeType pos) const { return arr_[pos]; }

  T& Front() { return arr_[0]; }
  T& Back() { return arr_[N - 1]; }
  const T& Front() const { return arr_[0]; }
  const T& Back() const { return arr_[N - 1]; }

  Iterator Data() { return Iterator(begin()); }
  Iterator begin() { return Iterator(arr_); }
  Iterator end() { return Iterator(arr_ + Size()); }

  ConstIterator Data() const { return ConstIterator(begin()); }
  ConstIterator begin() const { return ConstIterator(arr_); }
  ConstIterator end() const { return ConstIterator(arr_ + Size()); }

  bool Empty() const { return N != 0; }
  SizeType Size() const { return N; }
  SizeType MaxSize() const { return N; }
  void Swap(Array& other) { std::swap(arr_, other.arr_); }
  void Fill(const T& value);

 private:
  void DeepCopy(const Array& other);
  T arr_[N]{};
};

template <typename T, std::size_t N>
class Array<T, N>::ArrayIterator {
 public:
  ArrayIterator() : ptr_{nullptr} {}
  explicit ArrayIterator(T* ptr) : ptr_{ptr} {}
  ArrayIterator(const ArrayIterator& other) : ptr_{other.ptr_} {}
  ArrayIterator(ArrayIterator&& other) {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  ArrayIterator& operator=(const ArrayIterator& other) {
    ptr_ = other.ptr_;
    return *this;
  }
  ArrayIterator& operator=(ArrayIterator&& other) {
    ptr_ = other.ptr_;
    return *this;
  }
  ~ArrayIterator() {}
  T& operator*() { return *ptr_; }
  ArrayIterator operator+(SizeType n) {
    ptr_ += n;
    return *this;
  }
  ArrayIterator operator-(SizeType n) {
    ptr_ -= n;
    return *this;
  }
  ArrayIterator& operator++() {
    ++ptr_;
    return *this;
  }
  ArrayIterator& operator--() {
    --ptr_;
    return *this;
  }
  ArrayIterator operator++(int) {
    ArrayIterator temp{*this};
    ++(*this);
    return temp;
  }
  ArrayIterator operator--(int) {
    ArrayIterator temp{*this};
    --(*this);
    return temp;
  }
  long long operator-(Iterator pos) const { return ptr_ - pos.ptr_; }
  bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }
  bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
  bool operator>(Iterator const& other) const {
    return (ptr_ - other.ptr_) > 0;
  }
  bool operator>=(Iterator const& other) const {
    return (ptr_ - other.ptr_) >= 0;
  }
  bool operator<(Iterator const& other) const {
    return (ptr_ - other.ptr_) < 0;
  }
  bool operator<=(Iterator const& other) const {
    return (ptr_ - other.ptr_) <= 0;
  }
  operator ConstArrayIterator() const { return ConstArrayIterator(ptr_); }
  T* ptr_{nullptr};
};

template <typename T, std::size_t N>
class Array<T, N>::ConstArrayIterator {
 public:
  ConstArrayIterator() : ptr_{nullptr} {}
  explicit ConstArrayIterator(const T* ptr) : ptr_{ptr} {}
  ConstArrayIterator(const ConstArrayIterator& other) : ptr_{other.ptr_} {}
  ConstArrayIterator(ConstArrayIterator&& other) {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  ConstArrayIterator& operator=(const ConstArrayIterator& other) {
    ptr_ = other.ptr_;
    return *this;
  }
  ConstArrayIterator& operator=(ConstArrayIterator&& other) {
    ptr_ = other.ptr_;
    return *this;
  }
  ~ConstArrayIterator() {}
  const T& operator*() const { return *ptr_; }
  ConstArrayIterator operator+(SizeType n) {
    ptr_ += n;
    return *this;
  }
  ConstArrayIterator operator-(SizeType n) {
    ptr_ -= n;
    return *this;
  }
  ConstArrayIterator& operator++() {
    ++ptr_;
    return *this;
  }
  ConstArrayIterator& operator--() {
    --ptr_;
    return *this;
  }
  ConstArrayIterator operator++(int) {
    ConstArrayIterator temp{*this};
    ++(*this);
    return temp;
  }
  ConstArrayIterator operator--(int) {
    ConstArrayIterator temp{*this};
    --(*this);
    return temp;
  }
  long long operator-(ConstIterator pos) const { return ptr_ - pos.ptr_; }
  bool operator!=(const ConstIterator& other) const {
    return ptr_ != other.ptr_;
  }
  bool operator==(const ConstIterator& other) const {
    return ptr_ == other.ptr_;
  }
  bool operator>(const Iterator& other) const {
    return (ptr_ - other.ptr_) > 0;
  }
  bool operator>=(const Iterator& other) const {
    return (ptr_ - other.ptr_) >= 0;
  }
  bool operator<(const Iterator& other) const {
    return (ptr_ - other.ptr_) < 0;
  }
  bool operator<=(const Iterator& other) const {
    return (ptr_ - other.ptr_) <= 0;
  }
  operator ArrayIterator() const { return ArrayIterator(ptr_); }
  const T* ptr_{ nullptr };
};

template <typename T, std::size_t N>
Array<T, N>::Array(std::initializer_list<ValueType> const& items) {
  SizeType i { 0 };
  for (auto const& item : items) {
    arr_[i] = item;
    ++i;
    if (i >= N) {
      break;
    }
  }
}

template <typename T, std::size_t N>
Array<T, N>& Array<T, N>::operator=(Array&& other) {
  if (this == &other) {
    return *this;
  }
  Swap(other);
  return *this;
}

template <typename T, std::size_t N>
Array<T, N>& Array<T, N>::operator=(const Array& other) {
  if (this == &other) {
    return *this;
  }
  DeepCopy(other);
  return *this;
}

template <typename T, std::size_t N>
T& Array<T, N>::At(SizeType pos) {
  if (pos >= Size()) {
    throw std::out_of_range("Out of range");
  }
  return arr_[pos];
}

template <typename T, std::size_t N>
const T& Array<T, N>::At(SizeType pos) const {
  if (pos >= Size()) {
    throw std::out_of_range("Out of range");
  }
  return arr_[pos];
}

template <typename T, std::size_t N>
void Array<T, N>::Fill(const T& value) {
  for (SizeType i { 0 }; i < N; ++i) {
    arr_[i] = value;
  }
}

template <typename T, std::size_t N>
void Array<T, N>::DeepCopy(const Array& other) {
  for (SizeType i { 0 }; i < N; ++i) {
    arr_[i] = other.arr_[i];
  }
}

}  // namespace s21

#endif  // SRC_S21_ARRAY_H_
