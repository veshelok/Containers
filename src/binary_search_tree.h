#ifndef SRC_BINARY_SEARCH_TREE_H_
#define SRC_BINARY_SEARCH_TREE_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {

template <typename T>
class BinarySearchTree {
 public:
  using SizeType = std::size_t;
  class BinarySearchTreeIterator;
  using Iterator = BinarySearchTreeIterator;
  using ConstIterator = BinarySearchTreeIterator;
  BinarySearchTree() {}
  explicit BinarySearchTree(std::initializer_list<T> const& items);
  BinarySearchTree(const BinarySearchTree& other) { *this = other; }
  BinarySearchTree(BinarySearchTree&& other) { *this = std::move(other); }
  BinarySearchTree& operator=(const BinarySearchTree& other);
  BinarySearchTree& operator=(BinarySearchTree&& other);
  ~BinarySearchTree() { Clear(); }
  Iterator begin() const { return Iterator(this, MinimumNode(root_)); }
  Iterator end() const { return Iterator(this, nullptr); }
  Iterator Insert(const T& value);
  Iterator Find(const T& key) const;
  void Erase(Iterator pos);
  void Swap(BinarySearchTree& other);  // NOLINT(runtime/references)
  void Clear();
  bool Contains(const T& key) const { return Find(key) != this->end(); }
  bool Empty() const { return Size() == 0; }
  SizeType Size() const { return tree_size_; }
  SizeType MaxSize() const { return std::numeric_limits<SizeType>::max(); }

 protected:
  struct Node {
    Node* parent{};
    Node* left_child{};
    Node* right_child{};
    T value{};
  };
  void MoveNodeFromOtherTree(Iterator other_pos, BinarySearchTree& other);  // NOLINT(runtime/references)
  Node* root_{};
  SizeType tree_size_{};

 private:
  void InsertNode(Node* node_to_insert);
  Node* Successor(Node* node) const;
  Node* Predecessor(Node* node) const;
  Node* MaximumNode(Node* subtree) const;
  Node* MinimumNode(Node* subtree) const;
  void DeleteSubtree(Node* tree_to_delete);
  void ShiftNodes(Node* node_to_replace);
  void ReplaceNodeByNode(Node* replaceable, Node* replacement);
};

template <typename T>
class BinarySearchTree<T>::BinarySearchTreeIterator {
 public:
  BinarySearchTreeIterator() {}
  BinarySearchTreeIterator(const BinarySearchTree* tree, Node* node)
      : tree_ {tree}, node_ {node} {}
  BinarySearchTreeIterator(const BinarySearchTreeIterator& other)
      : tree_ {other.tree_}, node_ {other.node_} {}
  BinarySearchTreeIterator(BinarySearchTreeIterator&& other) {
    *this = std::move(other);
  }
  BinarySearchTreeIterator& operator=(const BinarySearchTreeIterator& other) {
    tree_ = other.tree_;
    node_ = other.node_;
    return *this;
  }
  BinarySearchTreeIterator& operator=(BinarySearchTreeIterator&& other) {
    tree_ = nullptr;
    node_ = nullptr;
    std::swap(node_, other.node_);
    std::swap(tree_, other.tree_);
    return *this;
  }
  ~BinarySearchTreeIterator() {}
  const T& operator*() const {
    return node_->value;
  }
  BinarySearchTreeIterator& operator++() {
    node_ = tree_->Successor(node_);
    return *this;
  }
  BinarySearchTreeIterator& operator--() {
    node_ = tree_->Predecessor(node_);
    return *this;
  }
  BinarySearchTreeIterator operator++(int) {
    BinarySearchTreeIterator tmp {*this};
    ++(*this);
    return tmp;
  }
  BinarySearchTreeIterator operator--(int) {
    BinarySearchTreeIterator tmp {*this};
    --(*this);
    return tmp;
  }
  bool operator==(const BinarySearchTreeIterator& other) const {
    return node_ == other.node_;
  }
  bool operator!=(const BinarySearchTreeIterator& other) const {
    return node_ != other.node_;
  }

  const BinarySearchTree* tree_{};
  Node* node_{};
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(std::initializer_list<T> const& items) {
  for (auto item : items) {
    Insert(item);
  }
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(
    const BinarySearchTree& other) {
  for (auto item : other) {
    Insert(item);
  }
  return *this;
}

template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(
    BinarySearchTree&& other) {
  Clear();
  std::swap(root_, other.root_);
  std::swap(tree_size_, other.tree_size_);
  return *this;
}

template <typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Insert(
    const T& value) {
  Node* node_to_insert {new Node {nullptr, nullptr, nullptr, value}};
  InsertNode(node_to_insert);
  return Iterator(this, node_to_insert);
}

template <typename T>
typename BinarySearchTree<T>::Iterator BinarySearchTree<T>::Find(
    const T& key) const {
  Node* node {root_};
  while (node != nullptr && node->value != key) {
    if (key < node->value) {
      node = node->left_child;
    } else {
      node = node->right_child;
    }
  }
  return Iterator(this, node);
}

template <typename T>
void BinarySearchTree<T>::Erase(Iterator pos) {
  if (pos.node_ == nullptr) {
    return;
  }
  ShiftNodes(pos.node_);
  delete pos.node_;
  --tree_size_;
}

template <typename T>
void BinarySearchTree<T>::MoveNodeFromOtherTree(Iterator other_pos,
                                                BinarySearchTree& other) {  // NOLINT(runtime/references)
  if (other_pos.node_ == nullptr) {
    return;
  }
  other.ShiftNodes(other_pos.node_);
  --other.tree_size_;
  InsertNode(other_pos.node_);
}

template <typename T>
void BinarySearchTree<T>::Swap(BinarySearchTree& other) {
  if (this == &other) {
    return;
  }
  std::swap(root_, other.root_);
  std::swap(tree_size_, other.tree_size_);
}

template <typename T>
void BinarySearchTree<T>::Clear() {
  DeleteSubtree(root_);
  root_ = nullptr;
  tree_size_ = 0;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::Successor(
    Node* node) const {
  if (node == nullptr) {
    return MinimumNode(root_);
  }
  if (node->right_child != nullptr) {
    return MinimumNode(node->right_child);
  }
  Node* successor {node->parent};
  while (successor != nullptr && node == successor->right_child) {
    node = successor;
    successor = successor->parent;
  }
  return successor;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::Predecessor(
    Node* node) const {
  if (node == nullptr) {
    return MaximumNode(root_);
  }
  if (node->left_child != nullptr) {
    return MaximumNode(node->left_child);
  }
  Node* predecessor {node->parent};
  while (predecessor != nullptr && node == predecessor->left_child) {
    node = predecessor;
    predecessor = predecessor->parent;
  }
  return predecessor;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::MaximumNode(
    Node* subtree) const {
  if (subtree == nullptr) {
    return nullptr;
  }
  while (subtree->right_child != nullptr) {
    subtree = subtree->right_child;
  }
  return subtree;
}

template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::MinimumNode(
    Node* subtree) const {
  if (subtree == nullptr) {
    return nullptr;
  }
  while (subtree->left_child != nullptr) {
    subtree = subtree->left_child;
  }
  return subtree;
}

template <typename T>
void BinarySearchTree<T>::InsertNode(Node* node_to_insert) {
  if (node_to_insert == nullptr) {
    return;
  }
  node_to_insert->left_child = nullptr;
  node_to_insert->right_child = nullptr;
  Node* current_node {root_};
  Node* prev_node {nullptr};
  while (current_node != nullptr) {
    prev_node = current_node;
    if (node_to_insert->value < current_node->value) {
      current_node = current_node->left_child;
    } else {
      current_node = current_node->right_child;
    }
  }
  node_to_insert->parent = prev_node;
  if (prev_node == nullptr) {
    root_ = node_to_insert;
  } else if (node_to_insert->value < prev_node->value) {
    prev_node->left_child = node_to_insert;
  } else {
    prev_node->right_child = node_to_insert;
  }
  ++tree_size_;
}

template <typename T>
void BinarySearchTree<T>::DeleteSubtree(Node* tree_to_delete) {
  if (tree_to_delete == nullptr) {
    return;
  }
  DeleteSubtree(tree_to_delete->left_child);
  DeleteSubtree(tree_to_delete->right_child);
  delete tree_to_delete;
}

template <typename T>
void BinarySearchTree<T>::ShiftNodes(Node* node_to_replace) {
  if (node_to_replace == nullptr) {
    return;
  }
  if (node_to_replace->left_child == nullptr) {
    ReplaceNodeByNode(node_to_replace, node_to_replace->right_child);
  } else if (node_to_replace->right_child == nullptr) {
    ReplaceNodeByNode(node_to_replace, node_to_replace->left_child);
  } else {
    Node* successor {Successor(node_to_replace)};
    if (successor->parent != node_to_replace) {
      ReplaceNodeByNode(successor, successor->right_child);
      successor->right_child = node_to_replace->right_child;
      successor->right_child->parent = successor;
    }
    ReplaceNodeByNode(node_to_replace, successor);
    successor->left_child = node_to_replace->left_child;
    successor->left_child->parent = successor;
  }
}

template <typename T>
void BinarySearchTree<T>::ReplaceNodeByNode(Node* replaceable,
                                            Node* replacement) {
  if (replaceable == nullptr) {
    return;
  }
  if (replaceable->parent == nullptr) {
    root_ = replacement;
  } else if (replaceable == replaceable->parent->left_child) {
    replaceable->parent->left_child = replacement;
  } else {
    replaceable->parent->right_child = replacement;
  }
  if (replacement != nullptr) {
    replacement->parent = replaceable->parent;
  }
}

}  // namespace s21

#endif  // SRC_BINARY_SEARCH_TREE_H_
