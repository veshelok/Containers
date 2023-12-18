#include "binary_search_tree.h"

#include <gtest/gtest.h>

TEST(BinarySearchTree, InsertToTree) {
  s21::BinarySearchTree<int> tree{};
  tree.Insert(5);
}

TEST(BinarySearchTree, CopyConstructorTest) {
  s21::BinarySearchTree<int> tree_to_copy{1, 2};
  s21::BinarySearchTree<int> tree{tree_to_copy};
  auto iter {tree.begin()};
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(tree.Size(), 2);
}

TEST(BinarySearchTree, MoveConstructorTest) {
  s21::BinarySearchTree<int> tree{s21::BinarySearchTree<int> {1, 2}};
  auto iter {tree.begin()};
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(tree.Size(), 2);
}

TEST(BinarySearchTree, CopyTest) {
  s21::BinarySearchTree<int> tree{};
  s21::BinarySearchTree<int> tree_to_copy{1, 2};
  tree = tree_to_copy;
  auto iter {tree.begin()};
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(tree.Size(), 2);
}

TEST(BinarySearchTree, MoveTest) {
  s21::BinarySearchTree<int> tree{};
  s21::BinarySearchTree<int> tree_to_move{1, 2};
  tree = std::move(tree_to_move);
  auto iter {tree.begin()};
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(tree.Size(), 2);
  EXPECT_EQ(tree_to_move.Size(), 0);
}

TEST(BinarySearchTree, IteratorsTests) {
  s21::BinarySearchTree<int> tree{5, 4, 3, 2, 1, 0};
  auto iter {tree.begin()};
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
  EXPECT_EQ(*iter++, 5);
  EXPECT_EQ(*++iter, 0);
  EXPECT_EQ(*iter--, 0);
  EXPECT_EQ(*--iter, 5);
  EXPECT_EQ(*--iter, 4);
  EXPECT_EQ(*--iter, 3);
  EXPECT_EQ(*--iter, 2);
  EXPECT_EQ(*--iter, 1);
  EXPECT_EQ(tree.Size(), 6);
}

TEST(BinarySearchTree, DeleteTest) {
  s21::BinarySearchTree<int> tree{1, 2, 3, 4, 5};
  EXPECT_EQ(tree.Size(), 5);
  tree.Erase(--(tree.end()));
  EXPECT_EQ(tree.Size(), 4);
  auto iter {tree.begin()};
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
  tree.Erase(tree.begin());
  EXPECT_EQ(*(tree.begin()), 2);
}

TEST(BinarySearchTree, EraseTest) {
  s21::BinarySearchTree<int> tree{3, 4, 5, 1, 2, 6, 5, 7, 6};
  tree.Erase(tree.Find(6));
  tree.Erase(tree.Find(6));
  tree.Erase(tree.Find(2));
  tree.Erase(tree.Find(3));
  tree.Insert(6);
  tree.Erase(tree.Find(7));
  EXPECT_EQ(tree.Size(), 5);
}

TEST(BinarySearchTree, DeleteTestEmpty) {
  s21::BinarySearchTree<int> tree{};
  tree.Erase(tree.begin());
  EXPECT_EQ(tree.Size(), 0);
}

TEST(BinarySearchTree, SearchTest) {
  s21::BinarySearchTree<int> tree{ 1, 2, 3, -1000 };
  EXPECT_EQ(*(tree.Find(3)), 3);
  EXPECT_TRUE(tree.Find(-1000) == tree.begin());
  EXPECT_TRUE(tree.Find(999) == tree.end());
}

TEST(BinarySearchTree, SwapTest) {
  s21::BinarySearchTree<int> tree{4, 5};
  s21::BinarySearchTree<int> tree1{1, 2, 3};
  EXPECT_EQ(tree.Size(), 2);
  EXPECT_EQ(tree1.Size(), 3);
  tree.Swap(tree1);
  auto iter {tree.begin()};
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  auto iter1 {tree1.begin()};
  EXPECT_EQ(*iter1++, 4);
  EXPECT_EQ(*iter1++, 5);
  EXPECT_EQ(tree.Size(), 3);
  EXPECT_EQ(tree1.Size(), 2);
}
