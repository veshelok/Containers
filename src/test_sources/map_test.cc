#include "s21_map.h"

#include <gtest/gtest.h>

TEST(Map, InitTest) {
  s21::Map<char, int> s21_map {};
  ASSERT_EQ(s21_map.Size(), 0);
}

TEST(Map, InitializerListConstructorTest) {
  s21::Map<char, int> s21_map {{'a', 1}, {'b', 2}, {'a', 3}};
  ASSERT_EQ(s21_map.Size(), 2);
}

TEST(Map, CopyConstructorTest) {
  s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'a', 3}};
  s21::Map<char, int> s21_map2 {s21_map1};
  ASSERT_EQ(s21_map2.Size(), 2);
}

TEST(Map, MoveConstructorTest) {
  s21::Map<char, int> s21_map2 {s21::Map<char, int> {{'a', 1}, {'b', 2},
                                                               {'a', 3}}};
  ASSERT_EQ(s21_map2.Size(), 2);
}

TEST(Map, CopyAssignmentTest) {
  s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'a', 3}};
  s21::Map<char, int> s21_map2 = s21_map1;
  ASSERT_EQ(s21_map2.Size(), 2);
}

TEST(Map, MoveAssignmentTest) {
  s21::Map<char, int> s21_map2 = s21::Map<char, int> {{ 'a', 1}, {'b', 2},
                                                                 {'a', 3}};
  ASSERT_EQ(s21_map2.Size(), 2);
}


TEST(Map, InsertTest) {
  s21::Map<char, int> s21_map {};
  s21_map.Insert('a', 1);
  s21_map.Insert('b', 2);
  s21_map.Insert({'a', 1});
  auto returnable_pair {s21_map.Insert({'b', 1})};
  ASSERT_EQ(s21_map.Size(), 2);
  EXPECT_FALSE(returnable_pair.second);
}

TEST(Map, InsertOrAssignTest) {
  s21::Map<char, int> s21_map {};
  s21_map.Insert('a', 1);
  s21_map.InsertOrAssign('a', 2);
  ASSERT_EQ(s21_map.Size(), 1);
  EXPECT_EQ((*s21_map.begin()).second, 2);
}

TEST(Map, EraseTest) {
  s21::Map<char, int> s21_map {};
  s21_map.Insert('a', 1);
  s21_map.Insert('b', 1);
  s21_map.Erase(s21_map.begin());
  EXPECT_EQ(s21_map.Size(), 1);
  EXPECT_EQ((*s21_map.begin()).first, 'b');
}

TEST(Map, SquareBraceTest) {
  s21::Map<char, int> s21_map {};
  s21_map.Insert('a', 1);
  s21_map['a'] = 5;
  ASSERT_EQ(s21_map.Size(), 1);
  EXPECT_EQ((*s21_map.begin()).second, 5);
  s21_map['b'] = 999;
  EXPECT_EQ((*(--s21_map.end())).second, 999);
}

TEST(Map, AtTest) {
  s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'c', 3}};
  EXPECT_EQ((*s21_map1.begin()).second, 1);
  s21_map1.At('a') = 5;
  EXPECT_EQ((*s21_map1.begin()).second, 5);
  EXPECT_THROW(s21_map1.At('d'), std::out_of_range);
}

TEST(Map, ConstAtTest) {
  const s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'c', 3}};
  EXPECT_EQ(s21_map1.At('a'), 1);
  EXPECT_THROW(s21_map1.At('d'), std::out_of_range);
}

TEST(Map, SwapTest) {
  s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'c', 3}};
  s21::Map<char, int> s21_map2 {{'d', 4}, {'e', 5}};
  s21_map1.Swap(s21_map2);
  EXPECT_EQ((*s21_map1.begin()).first, 'd');
  EXPECT_EQ((*s21_map2.begin()).first, 'a');
  EXPECT_EQ(s21_map2.Size(), 3);
  EXPECT_EQ(s21_map1.Size(), 2);
  EXPECT_EQ(s21_map2.Size(), 3);
}

TEST(Map, MergeTest) {
  s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'c', 3}};
  s21::Map<char, int> s21_map2 {{'d', 4}, {'e', 5}};
  s21_map1.Merge(s21_map2);
  EXPECT_EQ(s21_map1['d'], 4);
  EXPECT_EQ(s21_map1['e'], 5);
  EXPECT_EQ(s21_map1.Size(), 5);
  EXPECT_EQ(s21_map2.Size(), 0);
}

TEST(Map, MergeEmptyTest1) {
  s21::Map<char, int> s21_map1 {};
  s21::Map<char, int> s21_map2 {{'d', 4}, {'e', 5}};
  s21_map1.Merge(s21_map2);
  EXPECT_EQ(s21_map1['d'], 4);
  EXPECT_EQ(s21_map1['e'], 5);
  EXPECT_EQ(s21_map1.Size(), 2);
  EXPECT_EQ(s21_map2.Size(), 0);
}

TEST(Map, MergeEmptyTest2) {
  s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'c', 3}};
  s21::Map<char, int> s21_map2 {};
  s21_map1.Merge(s21_map2);
  EXPECT_EQ(s21_map1['a'], 1);
  EXPECT_EQ(s21_map1['b'], 2);
  EXPECT_EQ(s21_map1.Size(), 3);
  EXPECT_EQ(s21_map2.Size(), 0);
}

TEST(Map, MergeNotAllTest) {
  s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'c', 3}};
  s21::Map<char, int> s21_map2 {{'a', 5}, {'d', 4}};
  s21_map1.Merge(s21_map2);
  EXPECT_EQ(s21_map1['a'], 1);
  EXPECT_EQ(s21_map2['a'], 5);
  EXPECT_EQ(s21_map1['d'], 4);
  EXPECT_EQ(s21_map1.Size(), 4);
  EXPECT_EQ(s21_map2.Size(), 1);
}

TEST(Map, ContainsTest) {
  const s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'c', 3}};
  EXPECT_TRUE(s21_map1.Contains('a'));
}

TEST(Map, EmplaceTest) {
  s21::Map<char, int> s21_map1 {{'a', 1}, {'b', 2}, {'c', 3}};
  auto vector {s21_map1.Emplace(std::make_pair('a', 5),
                                std::make_pair('d', 4))};
  EXPECT_EQ(s21_map1['a'], 1);
  EXPECT_EQ(s21_map1['d'], 4);
  EXPECT_EQ(s21_map1.Size(), 4);
  EXPECT_FALSE(vector.Front().second);
}

