#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>

class Vector {
 public:
  using ValueType = T;
  using Reference = T&;
  using ConstReference = const T&;
  class VectorIterator;
  class ConstVectorIterator;
  using Iterator = VectorIterator;
  using ConstIterator = ConstVectorIterator;
  using SizeType = std::size_t;
  Vector();
  explicit Vector(SizeType n);
  explicit Vector(std::initializer_list<T> const& items);
  Vector(const Vector& other);
  Vector(Vector&& other);
  Vector& operator=(const Vector& other);
  Vector& operator=(Vector&& other);
  ~Vector();

  T& At(SizeType pos);
  const T& At(SizeType pos) const;
  T& operator[](SizeType pos);
  const T& operator[] (SizeType pos) const;
  T& Front();
  T& Back();
  const T& Front() const;
  const T& Back() const;
  Iterator Data() { return Iterator(begin()); }
  ConstIterator Data() const { return ConstIterator(begin()); }

  Iterator begin() { return Iterator(arr_); }
  Iterator end() { return Iterator(arr_ + arr_size_); }

  ConstIterator begin() const { return ConstIterator(arr_); }
  ConstIterator end() const { return ConstIterator(arr_ + arr_size_); }

  bool Empty() const { return Size() == 0; }
  SizeType Size() const { return arr_size_; }
  SizeType MaxSize() const { return std::numeric_limits<SizeType>::max(); }
  void Reserve(SizeType size);
  SizeType Capacity() const { return capacity_; }
  void ShrinkToFit();

  void Clear();
  Iterator Insert(Iterator pos, ConstReference value);
  void Erase(Iterator pos);
  void PushBack(ConstReference value);
  void PopBack();
  void Swap(Vector& other);

  template <class... Args>
  Iterator Emplace(ConstIterator pos, Args&&... args);
  template <class... Args>
  void EmplaceBack(Args&&... args);

 private:
  void DeepCopy(const Vector& other);
  void ChangeCapacity(SizeType size);
  void FreeVector();
  SizeType arr_size_{0};
  SizeType capacity_{0};
  T* arr_{nullptr};
};

template <typename T>
class Vector<T>::VectorIterator {
 public:
  VectorIterator()
      : ptr_ {nullptr} {}
  explicit VectorIterator(T* ptr)
      : ptr_ {ptr} {}
  VectorIterator(const VectorIterator& other)
      : ptr_ {other.ptr_} {}
  VectorIterator(VectorIterator&& other) {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  VectorIterator& operator=(const VectorIterator& other) {
    ptr_ = other.ptr_;
    return *this;
  }
  VectorIterator& operator=(VectorIterator&& other) {
    ptr_ = other.ptr_;
    return *this;
  }
  ~VectorIterator() {}
  T& operator*() {
    return *ptr_;
  }
  VectorIterator operator+(SizeType n) {
      ptr_ += n;
      return *this;
  }
  VectorIterator operator-(SizeType n) {
      ptr_ -= n;
      return *this;
  }
  VectorIterator& operator++() {
    ++ptr_;
    return *this;
  }
  VectorIterator&  operator--() {
    --ptr_;
    return *this;
  }
  VectorIterator operator++(int) {
    VectorIterator temp {*this};
    ++(*this);
    return temp;
  }
  VectorIterator operator--(int) {
    VectorIterator temp {*this};
    --(*this);
    return temp;
  }
  long long operator-(Iterator pos) const {
    return ptr_ - pos.ptr_;
  }
  bool operator!=(const Iterator& other) const {
    return ptr_ != other.ptr_;
  }
  bool operator==(const Iterator& other) const {
    return ptr_ == other.ptr_;
  }
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
  operator ConstVectorIterator() const { return ConstVectorIterator(ptr_); }
  T* ptr_ {nullptr};
};

template <typename T>
class Vector<T>::ConstVectorIterator {
 public:
  ConstVectorIterator()
      : ptr_ {nullptr} {}
  explicit ConstVectorIterator(const T* ptr)
      : ptr_ {ptr} {}
  ConstVectorIterator(const ConstVectorIterator& other)
      : ptr_ {other.ptr_} {}
  ConstVectorIterator(ConstVectorIterator&& other) {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  ConstVectorIterator& operator=(const ConstVectorIterator& other) {
    ptr_ = other.ptr_;
    return *this;
  }
  ConstVectorIterator& operator=(ConstVectorIterator&& other) {
    ptr_ = other.ptr_;
    return *this;
  }
  ~ConstVectorIterator() {}
  const T& operator*() const {
    return *ptr_;
  }
  ConstVectorIterator operator+(SizeType n) {
      ptr_ += n;
      return *this;
  }
  ConstVectorIterator operator-(SizeType n) {
      ptr_ -= n;
      return *this;
  }
  ConstVectorIterator& operator++() {
    ++ptr_;
    return *this;
  }
  ConstVectorIterator&  operator--() {
    --ptr_;
    return *this;
  }
  ConstVectorIterator operator++(int) {
    ConstVectorIterator temp {*this};
    ++(*this);
    return temp;
  }
  ConstVectorIterator operator--(int) {
    ConstVectorIterator temp {*this};
    --(*this);
    return temp;
  }
  long long operator-(ConstIterator pos) const {
    return ptr_ - pos.ptr_;
  }
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
  operator VectorIterator() const { return VectorIterator(ptr_); }
  const T* ptr_ {nullptr};
};

template <typename T>
Vector<T>::Vector() : arr_size_{0}, capacity_{0}, arr_{nullptr} {}

template <typename T>
Vector<T>::Vector(SizeType n) : arr_size_{0}, capacity_{n} {
  arr_ = new T[capacity_]{};
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> const& items)
    : Vector(items.size()) {
  for (auto const& item : items) {
    PushBack(item);
  }
}

template <typename T>
Vector<T>::Vector(const Vector& other) {
  *this = other;
}

template <typename T>
Vector<T>::Vector(Vector&& other) {
  *this = std::move(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
  if (this == &other) {
    return *this;
  }
  FreeVector();
  Swap(other);
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
  if (this == &other) {
    return *this;
  }
  ChangeCapacity(other.capacity_);
  DeepCopy(other);
  return *this;
}

template <typename T>
Vector<T>::~Vector() {
  FreeVector();
}

template <typename T>
T& Vector<T>::At(SizeType pos) {
  if (pos > Size()) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[pos];
}

template <typename T>
const T& Vector<T>::At(SizeType pos) const {
  if (pos > Size()) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[pos];
}

template <typename T>
T& Vector<T>::operator[](SizeType pos) {
  return arr_[pos];
}

template <typename T>
const T& Vector<T>::operator[] (SizeType pos) const {
  return arr_[pos];
}

template <typename T>
T& Vector<T>::Front() {
  if (Empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return arr_[0];
}

template <typename T>
T& Vector<T>::Back() {
  if (Empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return arr_[arr_size_ - 1];
}

template <typename T>
const T& Vector<T>::Front() const {
  if (Empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return arr_[0];
}

template <typename T>
const T& Vector<T>::Back() const {
  if (Empty()) {
    throw std::out_of_range("Vector is empty");
  }
  return arr_[arr_size_ - 1];
}

template <typename T>
void Vector<T>::Reserve(SizeType size) {
  if (arr_size_ <= capacity_) {
    ChangeCapacity(size);
  }
}

template <typename T>
void Vector<T>::ShrinkToFit() {
  ChangeCapacity(arr_size_);
}

template <typename T>
void Vector<T>::Clear() {
  for (SizeType i {0}; i < arr_size_; ++i) {
    arr_[i] = T{};
  }
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Insert(Iterator pos, const T& value) {
  return Emplace(pos, value);
}

template <typename T>
void Vector<T>::Erase(Iterator pos) {
  if (pos < begin() || pos >= end()) {
    return;
  }
  for (SizeType i = pos - begin() + 1; i < arr_size_; ++i) {
    arr_[i - 1] = arr_[i];
  }
  --arr_size_;
}

template <typename T>
void Vector<T>::PushBack(const T& value) {
  if (arr_size_ >= capacity_) {
    if (arr_size_ == 0) {
      capacity_ = 1;
    }
    ChangeCapacity(capacity_ * 2);
  }
  arr_[arr_size_++] = value;
}

template <typename T>
void Vector<T>::PopBack() {
  --arr_size_;
}

template <typename T>
void Vector<T>::Swap(Vector& other) {
  std::swap(arr_size_, other.arr_size_);
  std::swap(capacity_, other.capacity_);
  std::swap(arr_, other.arr_);
}

template <typename T>
template <typename... Args>
typename Vector<T>::Iterator Vector<T>::Emplace(ConstIterator pos, Args&&... args) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Position is out of array size");
  }
  SizeType index_of_pos {static_cast<SizeType>(pos - begin())};
  const SizeType args_size {sizeof...(Args)};
  if (args_size == 0) {
    return Iterator(arr_ + index_of_pos);
  }
  SizeType index_of_last {arr_size_ - 1};
  SizeType shifted_elements {index_of_last - index_of_pos + 1};
  const ValueType args_data[args_size] {args...};
  if (arr_size_ + args_size > capacity_) {
    ChangeCapacity(capacity_ * 2);
  }
  for (SizeType i {0}; i <= shifted_elements; ++i) {
    arr_[index_of_last + args_size - i] = arr_[index_of_last - i];
  }
  for (SizeType i {0}; i < args_size; ++i)  {
    arr_[index_of_pos + i] = args_data[i];
  }
  arr_size_ += args_size;
  return Iterator(arr_ + index_of_pos);
}

template <typename T>
template <class... Args>
void Vector<T>::EmplaceBack(Args&&... args) {
  Emplace(end(), args...);
}

template <typename T>
void Vector<T>::DeepCopy(const Vector& other) {
  for (SizeType i {0}; i < other.arr_size_; ++i) {
    arr_[i] = other.arr_[i];
  }
  arr_size_ = other.arr_size_;
}

template <typename T>
void Vector<T>::ChangeCapacity(SizeType size) {
  if (arr_size_ <= size) {
    Vector<T> temp(size);
    temp.DeepCopy(*this);
    *this = std::move(temp);
  }
}

template <typename T>
void Vector<T>::FreeVector() {
  delete[] arr_;
  arr_ = nullptr;
  capacity_ = 0;
  arr_size_ = 0;
}

};  // namespace s21

#endif  // SRC_S21_VECTOR_H_
