#include "s21_array.h"

#include <gtest/gtest.h>

TEST(Array, Default) {
  s21::Array<int, 5> MyArray1{1, 2, 3, 4, 5};
  s21::Array<int, 5> MyArray;
  ASSERT_EQ(MyArray.Size(), 5);
  ASSERT_EQ(MyArray1.Size(), 5);
}

TEST(Array, Move) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  s21::Array<int, 5> a1(a);
  ASSERT_EQ(a.Size(), a1.Size());
}

TEST(Array, Copy) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  s21::Array<int, 5> a1{a};
  ASSERT_EQ(a.Front(), a1.Front());
}

TEST(Array, Front) {
  s21::Array<int, 5> a1{5, 4, 3, 2};
  ASSERT_EQ(5, a1.Front());
}

TEST(Array, Back) {
  s21::Array<int, 5> a1{5, 4, 3, 2};
  a1.Fill(1);
  ASSERT_EQ(1, a1.Back());
}

TEST(Array, Empty) {
  s21::Array<int, 5> a{5, 4, 3, 2};
  s21::Array<int, 2> a1{5, 4};
  ASSERT_EQ(a.Empty(), a1.Empty());
}

TEST(Array, Position) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  ASSERT_EQ(a[2], 3);
}

TEST(Array, Filling) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  a.Fill(77);
  ASSERT_EQ(a[0], 77);
  ASSERT_EQ(a[2], 77);
  ASSERT_EQ(a[4], 77);
}

TEST(Array, At) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  ASSERT_EQ(a.At(1), 4);
}

TEST(Array, Copy1) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  s21::Array<int, 5> a1 = a;
  ASSERT_EQ(a.Front(), a1.Front());
}

TEST(Array, Swap) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  s21::Array<int, 5> a1 {1, 2, 3, 4, 5};
  a.Swap(a1);
  ASSERT_EQ(a.At(0), 1);
  ASSERT_EQ(a1.At(0), 5);
}

TEST(Array, Swap1) {
  s21::Array<int, 11> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::Array<int, 11> a1{};
  s21::Array<int, 11> a2{11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  a.Swap(a2);
  ASSERT_EQ(a.Front(), 11);
  a1 = a2;
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(a1[i], i);
  }
}


TEST(Array, Begin) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  int samp = *(a.begin());
  ASSERT_EQ(samp, 5);
  int samp1 = *(++a.begin());
  ASSERT_EQ(samp1, 4);
}

TEST(Array, End) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  int samp = *(--a.end());
  ASSERT_EQ(samp, 1);
}

TEST(Array, Data) {
  s21::Array<int, 5> a{5, 4, 3, 2, 1};
  int samp = *(a.Data());
  ASSERT_EQ(samp, 5);
  int samp1 = *((a.Data()) + 2);
  ASSERT_EQ(samp1, 3);
}
