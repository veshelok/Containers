#include <utility>

#include <gtest/gtest.h>

#include "s21_set.h"

TEST(Set, InitTest) {
  s21::Set<int> int_set {1, 2, 3, 4, 3, 2, 1};
  EXPECT_EQ(int_set.Size(), 4);
}

TEST(Set, CopyConstructorTest) {
  s21::Set<int> int_set1 {1, 2, 3, 4, 3, 2, 1};
  s21::Set<int> int_set2 {int_set1};
  EXPECT_EQ(int_set1.Size(), 4);
  EXPECT_EQ(int_set2.Size(), 4);
}

TEST(Set, MoveConstructorTest) {
  s21::Set<int> int_set1 {1, 2, 3, 4, 3, 2, 1};
  s21::Set<int> int_set2 {std::move(int_set1)};
  EXPECT_EQ(int_set1.Size(), 0);
  EXPECT_EQ(int_set2.Size(), 4);
}

TEST(Set, CopyAssignmentTest) {
  s21::Set<int> int_set1 {1, 2, 3, 4, 3, 2, 1};
  s21::Set<int> int_set2 {};
  int_set2 = int_set1;
  EXPECT_EQ(int_set1.Size(), 4);
  EXPECT_EQ(int_set2.Size(), 4);
}

TEST(Set, MoveAssignmentTest) {
  s21::Set<int> int_set1 {1, 2, 3, 4, 3, 2, 1};
  s21::Set<int> int_set2 {};
  int_set2 = std::move(int_set1);
  EXPECT_EQ(int_set1.Size(), 0);
  EXPECT_EQ(int_set2.Size(), 4);
}

TEST(Set, Empty) {
  s21::Set<int> int_set {};
  EXPECT_TRUE(int_set.Empty());
}

TEST(Set, ClearTest) {
  s21::Set<int> int_set {1, 2, 3, 4, 3, 2, 1};
  int_set.Clear();
  EXPECT_EQ(int_set.Size(), 0);
}

TEST(Set, InsertTest1) {
  s21::Set<int> int_set {1, 2, 3, 4, 3, 2, 1};
  auto returnable_pair {int_set.Insert(2)};
  EXPECT_FALSE(returnable_pair.second);
  EXPECT_EQ(*(returnable_pair.first), 2);
  EXPECT_EQ(int_set.Size(), 4);
}

TEST(Set, InsertTest2) {
  s21::Set<int> int_set {1, 2, 3, 4, 3, 2, 1};
  auto returnable_pair {int_set.Insert(5)};
  EXPECT_TRUE(returnable_pair.second);
  EXPECT_EQ(*(returnable_pair.first), 5);
  EXPECT_EQ(int_set.Size(), 5);
}

TEST(Set, EraseTest) {
  s21::Set<int> int_set {1, 2, 3, 4, 3, 2, 1};
  EXPECT_EQ(int_set.Size(), 4);
  int_set.Erase(int_set.begin());
  EXPECT_EQ(int_set.Size(), 3);
  EXPECT_EQ(*int_set.begin(), 2);
}

TEST(Set, SwapTest) {
  s21::Set<int> int_set1 {1, 2, 3, 4, 5, 6};
  s21::Set<int> int_set2 {5, 6, 7, 8};
  int_set1.Swap(int_set2);
  EXPECT_EQ(int_set1.Size(), 4);
  EXPECT_EQ(int_set2.Size(), 6);
  EXPECT_EQ(*int_set1.begin(), 5);
  EXPECT_EQ(*int_set2.begin(), 1);
}

TEST(Set, MergeTest) {
  s21::Set<int> int_set1 {1, 2, 3, 4, 5, 6};
  s21::Set<int> int_set2 {1, 2, 3, 4, 5, 6, 7, 8};
  int_set1.Merge(int_set2);
  EXPECT_EQ(int_set1.Size(), 8);
  EXPECT_EQ(int_set2.Size(), 6);
  EXPECT_EQ(*int_set1.begin(), 1);
  EXPECT_EQ(*int_set2.begin(), 1);
}

TEST(Set, FindTest) {
  s21::Set<int> int_set1 {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(*int_set1.Find(4), 4);
  EXPECT_TRUE(int_set1.Find(999) == int_set1.end());
}

TEST(Set, EmplaceTest) {
  s21::Set<int> int_set1 {1, 2, 3, 4, 5, 6};
  auto vector {int_set1.Emplace(1, 2, 3, 4, 5, 6, 7, 8)};
  EXPECT_EQ(int_set1.Size(), 8);
  EXPECT_EQ(*int_set1.begin(), 1);
  EXPECT_FALSE(vector.Front().second);
  EXPECT_TRUE(vector.Back().second);
}

