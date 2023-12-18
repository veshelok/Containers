#include <gtest/gtest.h>

#include "s21_queue.h"

TEST(Queue, Default) {
  s21::Queue<int> s{};
  ASSERT_TRUE(s.Empty());
}

TEST(Queue, Constructor) {
  s21::Queue<int> s{1, 2, 3, 4, 5, 6, 7};
  s21::Queue<int> s1 = s;
  ASSERT_EQ(s.Size(), s1.Size());
}

TEST(Queue, Constructor1) {
  s21::Queue<int> s{1, 2, 3, 4, 5, 6, 7};
  s21::Queue<int> s1(s);
  ASSERT_EQ(s.Size(), s1.Size());
}

TEST(Queue, Constructor2) {
  s21::Queue<int> s{1, 2, 3, 4, 5, 6, 7, 77, -0};
  s = s;
  ASSERT_EQ(s.Size(), 9);
}

TEST(Queue, Constructor3) {
  s21::Queue<int> s{1, 2, 3, 4, 5, 6, 7, 77, 88};
  s21::Queue<int> s1{1, 1, 3, 3};
  s.Swap(s1);
  ASSERT_EQ(s.Size(), 4);
  ASSERT_EQ(s1.Size(), 9);
}

TEST(Queue, Push) {
  s21::Queue<int> s{1, 2, 3, 4, 5, 6, 7};
  s21::Queue<int> s1{};
  s1.Push(7);
}

TEST(Queue, Push1) {
  s21::Queue<int> q{};
  ASSERT_EQ(q.Size(), 0);
  for (int i = 0; i < 99; ++i) {
    q.Push(i);
    ASSERT_EQ(q.Size(), i + 1);
  }
  ASSERT_EQ(q.Size(), 99);
  ASSERT_FALSE(q.Empty());
}

TEST(Queue, Pop) {
  s21::Queue<int> s{1, 2, 3, 4, 5, 6, 7};
  s21::Queue<int> s1{1, 2, 3, 4};
  s.Pop();
  s.Pop();
  s.Pop();
  ASSERT_EQ(s.Size(), s1.Size());
}

TEST(Queue, Pop1) {
  s21::Queue<int> s{1, 2, 3};
  s.Pop();
  s.Pop();
  s.Pop();
  s.Pop();
  ASSERT_EQ(s.Size(), 0);
  s.Push(-7);
  ASSERT_EQ(s.Size(), 1);
}

TEST(Queue, Swap) {
  s21::Queue<int> s{4, 3, 2, 1, 0};
  s21::Queue<int> s1{1, 2, 3, 4};
  s.Pop();
  s.Swap(s1);
  ASSERT_EQ(s.Size(), s1.Size());
}

TEST(Queue, Swap1) {
  s21::Queue<int> q{};
  for (int i = 0; i < 10; ++i) {
    q.Push(i);
  }
  s21::Queue<int> s{};
  s.Swap(q);
  ASSERT_EQ(s.Size(), 10);
  ASSERT_EQ(q.Size(), 0);
}

TEST(Queue, Empty) {
  s21::Queue<int> s{1, 2, 3, 4};
  s.Pop();
  s.Pop();
  s.Pop();
  ASSERT_FALSE(s.Empty());
  s.Pop();
  ASSERT_TRUE(s.Empty());
}

TEST(Queue, Size) {
  s21::Queue<int> s{1, 2, 3, 4};
  s21::Queue<int> s1{11, 22, 33, 44};
  ASSERT_EQ(s.Size(), s1.Size());
  s.Push(2);
  ASSERT_EQ(s.Size(), 5);
}

TEST(Queue, Front) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  ASSERT_EQ(q.Size(), 5);
  ASSERT_TRUE(!q.Empty());
  ASSERT_EQ(q.Front(), 1);
}

TEST(Queue, Back) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> s(q);
  ASSERT_EQ(s.Size(), 5);
  ASSERT_EQ(s.Back(), 5);
  ASSERT_TRUE(!q.Empty());
}

TEST(Queue, FrontBack) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> s(std::move(q));
  ASSERT_EQ(s.Size(), 5);
  ASSERT_EQ(s.Front(), 1);
  ASSERT_EQ(s.Back(), 5);
  ASSERT_EQ(q.Size(), 0);
}

TEST(Queue, FrontBack1) {
  s21::Queue<int> q{1, 2, 3, 4, 5};
  s21::Queue<int> s = q;
  ASSERT_EQ(s.Size(), 5);
  ASSERT_EQ(s.Front(), 1);
  ASSERT_EQ(s.Back(), 5);
  ASSERT_EQ(q.Size(), 5);
}

TEST(Queue, FrontBack2) {
  s21::Queue<int> q{1, 2, 3, 110};
  ASSERT_EQ(q.Size(), 4);
  ASSERT_EQ(q.Front(), 1);
  ASSERT_EQ(q.Back(), 110);
  q.Pop();
  ASSERT_EQ(q.Size(), 3);
  ASSERT_EQ(q.Front(), 2);
  ASSERT_EQ(q.Back(), 110);
  q.Pop();
  ASSERT_EQ(q.Size(), 2);
  ASSERT_EQ(q.Front(), 3);
  ASSERT_EQ(q.Back(), 110);
  q.Pop();
  ASSERT_EQ(q.Size(), 1);
  ASSERT_EQ(q.Front(), 110);
  ASSERT_EQ(q.Back(), 110);
  q.Push(-999);
  ASSERT_EQ(q.Size(), 2);
  ASSERT_EQ(q.Front(), 110);
  ASSERT_EQ(q.Back(), -999);
}

TEST(Queue, FrontBack3) {
  s21::Queue<double> q{1.2, 2.3, 3.444, 4.543, -5.7};
  ASSERT_EQ(q.Size(), 5);
  ASSERT_FALSE(q.Empty());
  EXPECT_DOUBLE_EQ(q.Front(), 1.2);
  EXPECT_DOUBLE_EQ(q.Back(), -5.7);
  q.Pop();
  ASSERT_EQ(q.Size(), 4);
  EXPECT_DOUBLE_EQ(q.Front(), 2.3);
  EXPECT_DOUBLE_EQ(q.Back(), -5.7);
}
