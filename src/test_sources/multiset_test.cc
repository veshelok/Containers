#include "s21_multiset.h"

#include <gtest/gtest.h>

TEST(Multiset, InitTest) {
  s21::Multiset<int> multiset {1, 2, 3, 2, 1};
  EXPECT_EQ(multiset.Size(), 5);
}

TEST(Multiset, CopyConstructorTest) {
  s21::Multiset<int> int_set1 {1, 2, 3, 4, 3, 2, 1};
  s21::Multiset<int> int_set2 {int_set1};
  EXPECT_EQ(int_set1.Size(), 7);
  EXPECT_EQ(int_set2.Size(), 7);
}

TEST(Multiset, MoveConstructorTest) {
  s21::Multiset<int> int_set1 {1, 2, 3, 4, 3, 2, 1};
  s21::Multiset<int> int_set2 {std::move(int_set1)};
  EXPECT_EQ(int_set1.Size(), 0);
  EXPECT_EQ(int_set2.Size(), 7);
}

TEST(Multiset, CopyAssignmentTest) {
  s21::Multiset<int> int_set1 {1, 2, 3, 4, 3, 2, 1};
  s21::Multiset<int> int_set2 {};
  int_set2 = int_set1;
  EXPECT_EQ(int_set1.Size(), 7);
  EXPECT_EQ(int_set2.Size(), 7);
}

TEST(Multiset, MoveAssignmentTest) {
  s21::Multiset<int> int_set1 {1, 2, 3, 4, 3, 2, 1};
  s21::Multiset<int> int_set2 {};
  int_set2 = std::move(int_set1);
  EXPECT_EQ(int_set1.Size(), 0);
  EXPECT_EQ(int_set2.Size(), 7);
}

TEST(Multiset, Empty) {
  s21::Multiset<int> int_set {};
  EXPECT_TRUE(int_set.Empty());
}

TEST(Multiset, ClearTest) {
  s21::Multiset<int> int_set {1, 2, 3, 4, 3, 2, 1};
  int_set.Clear();
  EXPECT_EQ(int_set.Size(), 0);
}

TEST(Multiset, InsertTest) {
  s21::Multiset<int> multiset {1, 2, 3, 2, 1};
  multiset.Insert(1);
  EXPECT_EQ(multiset.Size(), 6);
}

TEST(Multiset, EraseTest) {
  s21::Multiset<int> int_set {1, 2, 3, 4, 3, 2, 1};
  EXPECT_EQ(int_set.Size(), 7);
  int_set.Erase(int_set.begin());
  EXPECT_EQ(int_set.Size(), 6);
  EXPECT_EQ(*int_set.begin(), 1);
  int_set.Erase(int_set.begin());
  EXPECT_EQ(*int_set.begin(), 2);
}

TEST(Multiset, SwapTest) {
  s21::Multiset<int> int_set1 {1, 2, 3, 4, 5, 6};
  s21::Multiset<int> int_set2 {5, 6, 7, 8};
  int_set1.Swap(int_set2);
  EXPECT_EQ(int_set1.Size(), 4);
  EXPECT_EQ(int_set2.Size(), 6);
  EXPECT_EQ(*int_set1.begin(), 5);
  EXPECT_EQ(*int_set2.begin(), 1);
}

TEST(Multiset, MergeTest) {
  s21::Multiset<int> int_set1 {1, 2, 3, 4, 5, 6};
  s21::Multiset<int> int_set2 {1, 2, 3, 4, 5, 6, 7, 8};
  int_set1.Merge(int_set2);
  EXPECT_EQ(int_set1.Size(), 14);
  EXPECT_EQ(int_set2.Size(), 0);
  EXPECT_EQ(*int_set1.begin(), 1);
  EXPECT_TRUE(int_set2.begin() == int_set2.end());
}

TEST(Multiset, EqualRangeTest) {
  s21::Multiset<int> int_set {1, 2, 2, 2, 3, 4, 5, 6};
  auto pair{int_set.EqualRange(2)};
  for (; pair.first != pair.second; ++pair.first) {
    EXPECT_EQ(*pair.first, 2);
  }
  EXPECT_EQ(*pair.second, 3);
}

TEST(Multiset, CounterTest) {
  s21::Multiset<int> int_set {1, 2, 2, 2, 3, 4, 5, 6};
  EXPECT_EQ(int_set.Count(2), 3);
  EXPECT_EQ(int_set.Count(999), 0);
}

TEST(Multiset, EmplaceTest) {
  s21::Multiset<int> int_set {1, 2, 3, 4, 5, 6};
  auto vector {int_set.Emplace(1, 2, 3, 4, 5, 6, 7, 8)};
  EXPECT_EQ(int_set.Size(), 14);
  EXPECT_EQ(*int_set.begin(), 1);
  EXPECT_EQ(*(--int_set.end()), 8);
}

