#include "s21_stack.h"

#include <gtest/gtest.h>

TEST(Stack, Default) {
  s21::Stack<int> s{};
  ASSERT_TRUE(s.Empty());
}

TEST(Stack, Constructor) {
  s21::Stack<int> s{1, 2, 3, 4, 5, 6, 7};
  s21::Stack<int> s1 = s;
  ASSERT_EQ(s.Size(), s1.Size());
  ASSERT_EQ(s.Top(), s1.Top());
}

TEST(Stack, Constructor1) {
  s21::Stack<int> s{1, 2, 3, 4, 5, 6, 7};
  s21::Stack<int> s1(s);
  ASSERT_EQ(s.Size(), s1.Size());
  ASSERT_EQ(s.Top(), s1.Top());
}

TEST(Stack, Constructor2) {
  s21::Stack<int> s{1, 2, 3, 4, 5, 6, 7, 77, -0};
  s = s;
  ASSERT_EQ(s.Size(), 9);
  ASSERT_EQ(s.Top(), -0);
}

TEST(Stack, Constructor3) {
  s21::Stack<int> s{1, 2, 3, 4, 5, 6, 7, 77, 88};
  s21::Stack<int> s1{1, 1, 3, 3};
  s.Swap(s1);
  ASSERT_EQ(s.Size(), 4);
  ASSERT_EQ(s.Top(), 3);
  ASSERT_EQ(s1.Size(), 9);
  ASSERT_EQ(s1.Top(), 88);
}

TEST(Stack, Push) {
  s21::Stack<int> s{1, 2, 3, 4, 5, 6, 7};
  s21::Stack<int> s1{};
  s1.Push(7);
  ASSERT_EQ(s.Top(), s1.Top());
}

TEST(Stack, Pop) {
  s21::Stack<int> s{1, 2, 3, 4, 5, 6, 7};
  s21::Stack<int> s1{1, 2, 3, 4};
  s.Pop();
  s.Pop();
  s.Pop();
  ASSERT_EQ(s.Size(), s1.Size());
  ASSERT_EQ(s.Top(), s1.Top());
}

TEST(Stack, Pop1) {
  s21::Stack<int> s{1, 2, 3};
  s.Pop();
  s.Pop();
  s.Pop();
  s.Pop();
  ASSERT_EQ(s.Size(), 0);
  ASSERT_EQ(s.Top(), 0);
  s.Push(-7);
  ASSERT_EQ(s.Size(), 1);
  ASSERT_EQ(s.Top(), -7);
}

TEST(Stack, Swap) {
  s21::Stack<int> s{4, 3, 2, 1, 0};
  s21::Stack<int> s1{1, 2, 3, 4};
  s.Pop();
  s.Swap(s1);
  ASSERT_EQ(s.Size(), s1.Size());
  ASSERT_EQ(s.Top(), 4);
  ASSERT_EQ(s1.Top(), 1);
}

TEST(Stack, Top) {
  s21::Stack<int> s{4, 3, 2, 1, 0};
  s21::Stack<int> s1{1, 2, 3, 4, 0};
  ASSERT_EQ(s.Top(), s1.Top());
}

TEST(Stack, Empty) {
  s21::Stack<int> s{1, 2, 3, 4};
  s.Pop();
  s.Pop();
  s.Pop();
  ASSERT_FALSE(s.Empty());
  s.Pop();
  ASSERT_TRUE(s.Empty());
}

TEST(Stack, Size) {
  s21::Stack<int> s{1, 2, 3, 4};
  s21::Stack<int> s1{11, 22, 33, 44};
  ASSERT_EQ(s.Size(), s1.Size());
  s.Push(2);
  ASSERT_EQ(s.Size(), 5);
}
