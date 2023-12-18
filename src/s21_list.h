#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {

template <typename T>
class List {
 public:
  using ValueType = T;
  using Rerefence = T&;
  using ConstReference = const T&;
  class ListIterator;
  class ConstListIterator;
  using Iterator = ListIterator;
  using ConstIterator = ConstListIterator;
  using SizeType = std::size_t;
  List();
  explicit List(SizeType n);
  explicit List(std::initializer_list<T> const& items);
  List(const List& other);
  List(List&& other);
  List& operator=(const List& other);
  List& operator=(List&& other);
  ~List();

  T& Front();
  T& Back();
  const T& Front() const;
  const T& Back() const;

  Iterator begin() { return ListIterator(first_node_ptr_); }
  Iterator end() { return ListIterator(pseudo_node_ptr_); }

  ConstIterator begin() const { return ConstListIterator(first_node_ptr_); }
  ConstIterator end() const { return ConstListIterator(pseudo_node_ptr_); }

  bool Empty() const { return list_size_ == 0; }
  SizeType Size() const { return list_size_; }
  SizeType MaxSize() const { return std::numeric_limits<SizeType>::max(); }
  void Clear();
  Iterator Insert(Iterator pos, const T& value);
  void Erase(Iterator pos);
  void PushBack(const T& value);
  void PopBack();
  void PushFront(const T& value);
  void PopFront();
  void Swap(List& other);
  void Merge(List& other);
  void Splice(ConstIterator pos, List& other);
  void Reverse();
  void Unique();
  void Sort();

  template <typename... Args>
  Iterator Emplace(ConstIterator pos, Args&&... args);
  template <typename... Args>
  void EmplaceFront(Args&&... args);
  template <typename... Args>
  void EmplaceBack(Args&&... args);

 private:
  struct Node {
    T value{};
    Node* prev{nullptr};
    Node* next{nullptr};
  };
  void SwapNodes(Iterator first, Iterator Second);
  void BindNodes(Node* first, Node* second);
  void SwapNodesByPointers(Node* first, Node* second);
  void SwapNeighboringNodes(Node* first, Node* second);
  void SwapDistantingNodes(Node* first, Node* second);
  void SetFirstAndLastNodePointers(Node* first, Node* second);
  Node* first_node_ptr_{};
  Node* last_node_ptr_{};
  Node* pseudo_node_ptr_{};
  SizeType list_size_{};
};

template <typename T>
class List<T>::ListIterator {
 public:
  ListIterator()
      : node_ptr_ {nullptr} {}
  explicit ListIterator(Node* node)
      : node_ptr_{node} {}
  ListIterator(const ListIterator& other)
      : node_ptr_ {other.node_ptr_} {}
  ListIterator(ListIterator&& other)
      : node_ptr_ {nullptr} {
    std::swap(node_ptr_, other.node_ptr_);
  }
  ListIterator& operator=(const ListIterator& other) {
    node_ptr_ = other.node_ptr_;
    return *this;
  }
  ListIterator& operator=(ListIterator&& other) {
    node_ptr_ = other.node_ptr_;
    other.node_ptr_ = nullptr;
    return *this;
  }
  ~ListIterator() {}
  T& operator*() const {
    return node_ptr_->value;
  }
  ListIterator& operator++() {
    node_ptr_ = node_ptr_->next;
    return *this;
  }
  ListIterator& operator--() {
    node_ptr_ = node_ptr_->prev;
    return *this;
  }
  ListIterator operator++(int) {
    ListIterator tmp {*this};
    ++(*this);
    return tmp;
  }
  ListIterator operator--(int) {
    ListIterator tmp {*this};
    --(*this);
    return tmp;
  }
  bool operator==(const ListIterator& iter) const {
    return (iter.node_ptr_ == node_ptr_);
  }
  bool operator!=(const ListIterator& iter) const {
    return !(*this == iter);
  }
  operator ConstListIterator() const { return ConstListIterator(node_ptr_); }
  Node* node_ptr_{};
};

template <typename T>
class List<T>::ConstListIterator : public List<T>::Iterator {
 public:
  explicit ConstListIterator(Node* node) : Iterator { node } {}
  const T& operator*() const {
    return this->node_ptr_->value;
  }
};

template <typename T>
List<T>::List() : list_size_ {0} {
  pseudo_node_ptr_ = new Node {T{}, last_node_ptr_, nullptr};
  first_node_ptr_ = pseudo_node_ptr_;
}

template <typename T>
List<T>::List(SizeType n) : List() {
  for (SizeType i {0}; i < n; ++i) {
    PushBack(T{});
  }
}

template <typename T>
List<T>::List(std::initializer_list<T> const& items) : List() {
  for (const auto& item : items) {
    PushBack(item);
  }
}

template <typename T>
List<T>::List(const List& other) : List() {
  *this = other;
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
  if (this == &other) {
    return *this;
  }
  Clear();
  for (const auto& i : other) {
    PushBack(i);
  }
  return *this;
}

template <typename T>
List<T>::List(List&& other) : List() {
  *this = std::move(other);
}

template <typename T>
List<T>& List<T>::operator=(List&& other) {
  if (this == &other) {
    return *this;
  }
  Swap(other);
  return *this;
}

template <typename T>
List<T>::~List() {
  Clear();
  delete pseudo_node_ptr_;
}

template <typename T>
T& List<T>::Front() {
  if (first_node_ptr_ != nullptr) {
    return first_node_ptr_->value;
  }
  return pseudo_node_ptr_->value;
}

template <typename T>
T& List<T>::Back() {
  if (last_node_ptr_ != nullptr) {
    return last_node_ptr_->value;
  }
  return pseudo_node_ptr_->value;
}

template <typename T>
const T& List<T>::Front() const {
  if (first_node_ptr_ != nullptr) {
    return first_node_ptr_->value;
  }
  return pseudo_node_ptr_->value;
}

template <typename T>
const T& List<T>::Back() const {
  if (last_node_ptr_ != nullptr) {
    return last_node_ptr_->value;
  }
  return pseudo_node_ptr_->value;
}

template <typename T>
void List<T>::Clear() {
  while (last_node_ptr_ != nullptr) {
    PopBack();
  }
}

template <typename T>
typename List<T>::Iterator List<T>::Insert(Iterator pos, const T& value) {
  if (pos == begin()) {
    PushFront(value);
    return begin();
  }
  if (pos == end()) {
    PushBack(value);
    return --end();
  }
  Node* new_node {new Node {value, nullptr, nullptr}};
  BindNodes(pos.node_ptr_->prev, new_node);
  BindNodes(new_node, pos.node_ptr_);
  ++list_size_;
  return --pos;
}

template <typename T>
void List<T>::Erase(Iterator pos) {
  if (pos == begin()) {
    PopFront();
  } else if (pos == --end()) {
    PopBack();
  } else {
    Node* iterator_node_ptr {pos.node_ptr_};
    BindNodes(iterator_node_ptr->prev, iterator_node_ptr->next);
    delete iterator_node_ptr;
    iterator_node_ptr = nullptr;
    --list_size_;
  }
}

template <typename T>
void List<T>::PushBack(const T& value) {
  Node* new_node {new Node {value, nullptr, nullptr}};
  BindNodes(new_node, pseudo_node_ptr_);
  if (last_node_ptr_ == nullptr) {
    first_node_ptr_ = new_node;
  } else {
    BindNodes(last_node_ptr_, new_node);
  }
  last_node_ptr_ = new_node;
  ++list_size_;
}

template <typename T>
void List<T>::PopBack() {
  if (last_node_ptr_ != nullptr) {
    if (last_node_ptr_->prev != nullptr) {
      last_node_ptr_ = last_node_ptr_->prev;
      delete last_node_ptr_->next;
      BindNodes(last_node_ptr_, pseudo_node_ptr_);
    } else {
      delete last_node_ptr_;
      last_node_ptr_ = nullptr;
      first_node_ptr_ = nullptr;
    }
    --list_size_;
  }
}

template <typename T>
void List<T>::PushFront(const T& value) {
  Node* new_node {new Node {value, nullptr, nullptr}};
  BindNodes(new_node, first_node_ptr_);
  first_node_ptr_ = new_node;
  if (last_node_ptr_ == nullptr) {
    BindNodes(first_node_ptr_, pseudo_node_ptr_);
    last_node_ptr_ = new_node;
  }
  ++list_size_;
}

template <typename T>
void List<T>::PopFront() {
  if (first_node_ptr_ != nullptr) {
    if (first_node_ptr_->next != pseudo_node_ptr_) {
      first_node_ptr_ = first_node_ptr_->next;
      delete first_node_ptr_->prev;
      first_node_ptr_->prev = nullptr;
    } else {
      delete first_node_ptr_;
      first_node_ptr_ = nullptr;
      last_node_ptr_ = nullptr;
    }
    --list_size_;
  }
}

template <typename T>
void List<T>::Swap(List& other) {
  if (this == &other) {
    return;
  }
  std::swap(first_node_ptr_, other.first_node_ptr_);
  std::swap(last_node_ptr_, other.last_node_ptr_);
  std::swap(pseudo_node_ptr_, other.pseudo_node_ptr_);
  std::swap(list_size_, other.list_size_);
}

template <typename T>
void List<T>::Reverse() {
  List<T> tmp_list;
  for (const auto& iter : *this) {
    tmp_list.PushFront(iter);
  }
  Swap(tmp_list);
}

template <typename T>
void List<T>::Merge(List& other) {  // NOLINT(runtime/references)
  if (this == &other) {
    return;
  }
  Sort();
  other.Sort();
  for (auto iter {begin()}; !(other.Empty());) {
    if (*iter > other.Front()) {
      Insert(iter, other.Front());
      other.PopFront();
    } else if (iter != end()) {
      ++iter;
    } else {
      Insert(iter, other.Front());
      other.PopFront();
    }
  }
}

template <typename T>
void List<T>::Splice(ConstIterator pos, List& other) {  // NOLINT(runtime/references)
  if (this == &other) {
    return;
  }
  if (other.Empty()) {
    return;
  }
  if (pos == begin()) {
    first_node_ptr_ = other.first_node_ptr_;
  }
  if (pos == end()) {
    BindNodes(last_node_ptr_, other.first_node_ptr_);
    last_node_ptr_ = other.last_node_ptr_;
  } else {
    BindNodes(pos.node_ptr_->prev, other.first_node_ptr_);
    BindNodes(other.last_node_ptr_, pos.node_ptr_);
  }
  list_size_ += other.list_size_;
  other.last_node_ptr_ = nullptr;
}

template <typename T>
void List<T>::Unique() {
  for (auto iter {begin()}; iter != end(); ++iter) {
    auto inner_iter {iter};
    ++inner_iter;
    for (; inner_iter != end(); ) {
      if (*iter == *inner_iter) {
        Erase(inner_iter++);
      } else {
        ++inner_iter;
      }
    }
  }
}

template <typename T>
void List<T>::Sort() {
  for (auto iter {begin()}; iter != end(); ) {
    bool no_swap {true};
    for (auto inner_iter {iter}; inner_iter != end(); ++inner_iter) {
      if (*inner_iter < *iter) {
        SwapNodes(iter, inner_iter);
        std::swap(iter, inner_iter);
        no_swap = false;
      }
    }
    if (no_swap) {
      ++iter;
    }
  }
}

template <typename T>
void List<T>::SwapNodes(Iterator first, Iterator second) {
  // first must be before second, otherwise the list will be looped
  SwapNodesByPointers(first.node_ptr_, second.node_ptr_);
}

template <typename T>
template <typename... Args>
typename List<T>::Iterator List<T>::Emplace(ConstIterator pos, Args&&... args) {
  T args_data[sizeof...(Args)] {args...};
  for (SizeType i {0}; i < sizeof...(Args); ++i) {
    Insert(pos, args_data[i]);
  }
  return pos;
}

template <typename T>
template <typename... Args>
void List<T>::EmplaceFront(Args&&... args) {
  Emplace(begin(), args...);
}

template <typename T>
template <typename... Args>
void List<T>::EmplaceBack(Args&&... args) {
  Emplace(end(), args...);
}

template <typename T>
void List<T>::BindNodes(Node* first, Node* second) {
  if (first != nullptr) {
    first->next = second;
  }
  if (second != nullptr) {
    second->prev = first;
  }
}

template <typename T>
void List<T>::SwapNodesByPointers(Node* first, Node* second) {
  // first must be before second, otherwise the list will be looped
  if (Size() < 2) {
    return;
  }
  if (first == pseudo_node_ptr_ || second == pseudo_node_ptr_) {
    return;
  }
  if (first == second) {
    return;
  }
  if (first->next == second) {
    SwapNeighboringNodes(first, second);
  } else {
    SwapDistantingNodes(first, second);
  }
  SetFirstAndLastNodePointers(first, second);
}

template <typename T>
void List<T>::SwapNeighboringNodes(Node* first, Node* second) {
  first->next = second->next;
  first->next->prev = first;
  second->prev = first->prev;
  if (second->prev != nullptr) {
    second->prev->next = second;
  }
  first->prev = second;
  second->next = first;
}

template <typename T>
void List<T>::SwapDistantingNodes(Node* first, Node* second) {
  if (first->prev != nullptr) {
    std::swap(first->prev->next, second->prev->next);
  } else {
    second->prev->next = first;
  }
  std::swap(first->prev, second->prev);
  std::swap(first->next->prev, second->next->prev);
  std::swap(first->next, second->next);
}

template <typename T>
void List<T>::SetFirstAndLastNodePointers(Node* first, Node* second) {
  if (first_node_ptr_ == first) {
    first_node_ptr_ = second;
  }
  if (last_node_ptr_ == second) {
    last_node_ptr_ = first;
  }
}

}  // namespace s21

#endif  // SRC_S21_LIST_H_
