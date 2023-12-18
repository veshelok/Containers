#include "s21_vector.h"

#include <gtest/gtest.h>

TEST(Vector, Default) {
  s21::Vector<int> MyVector;
  s21::Vector<int> MyVector1(35);
  s21::Vector<int> MyVector2{1, 2, 4};
  ASSERT_EQ(MyVector.Size(), 0);
  ASSERT_EQ(MyVector1.Size(), 0);
  ASSERT_EQ(MyVector2.Size(), 3);
}

TEST(Vector, CopyConstructor) {
  const s21::Vector<int> a{1, 2, 3};
  const s21::Vector<int> b{a};
  ASSERT_EQ(a.Size(), 3);
  ASSERT_EQ(b.Size(), 3);
}

TEST(Vector, CopyConstructor2) {
  s21::Vector<int> v{1, 2, 3, 4, 5, 6, 7};
  s21::Vector<int> s = v;
  ASSERT_EQ(v.Size(), 7);
  ASSERT_EQ(s.Size(), 7);
  ASSERT_EQ(s[2], 3);
}

TEST(Vector, ConstructorMove) {
  s21::Vector<int> s {std::move(s21::Vector<int> {1, 2, 3, 4, 5})};
  ASSERT_EQ(s.Size(), 5);
  ASSERT_EQ(s[2], 3);
}

TEST(Vector, InitializerList) {
  s21::Vector<int> MyVector{1, 2, 3, 4, 5};
  s21::Vector<int> a(std::move(MyVector));
  ASSERT_EQ(a.Size(), 5);
}

TEST(Vector, AtBrackets) {
  s21::Vector<int> MyVector{1, 2, 3, 4, 5, 6, 7};
  ASSERT_EQ(MyVector.At(1), 2);
  ASSERT_EQ(MyVector.At(6), 7);
  ASSERT_EQ(MyVector[6], 7);
  EXPECT_THROW(MyVector.At(12), std::out_of_range);
}

TEST(Vector, FrontBack) {
  s21::Vector<int> MyVector{1, 2, 3, 4};
  s21::Vector<int> MyVector1{};
  ASSERT_EQ(MyVector.Front(), 1);
  ASSERT_EQ(MyVector.Back(), 4);
  EXPECT_THROW(MyVector1.Front(), std::out_of_range);
  EXPECT_THROW(MyVector1.Back(), std::out_of_range);
}

TEST(Vector, Empty) {
  s21::Vector<int> MyVector{1, 2, 3, 4, 5, 6, 7};
  s21::Vector<int> NewVector{};
  MyVector.Swap(NewVector);
  ASSERT_EQ(MyVector.Empty(), 1);
  ASSERT_EQ(NewVector.Empty(), 0);
}

TEST(Vector, Reserve) {
  s21::Vector<int> MyVector{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_EQ(MyVector.Capacity(), 9);
  MyVector.Reserve(50);
  ASSERT_EQ(MyVector.Capacity(), 50);
}

TEST(Vector, ShrinkToFit) {
  s21::Vector<int> MyVector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(MyVector.Capacity(), 10);
  MyVector.Reserve(50);
  EXPECT_EQ(MyVector.Capacity(), 50);
  MyVector.ShrinkToFit();
  EXPECT_EQ(MyVector.Capacity(), 10);
}

TEST(Vector, Insert) {
  s21::Vector<int> MyVector;
  for (int i = 1; i <= 10; i++) {
    MyVector.PushBack(i);
  }
  MyVector.Insert(MyVector.begin() + 2, 3);
  ASSERT_EQ(MyVector.Size(), 11);
}

TEST(Vector, Erase) {
  s21::Vector<int> myvector{};
  for (int i = 1; i <= 10; i++) {
    myvector.PushBack(i);
  }
  myvector.Erase(myvector.begin() + 2);
  ASSERT_EQ(myvector.Size(), 9);
  ASSERT_EQ(myvector.At(3), 5);
  myvector.Erase(++myvector.end());
  ASSERT_EQ(myvector.Size(), 9);
  myvector.Erase(--myvector.begin());
  ASSERT_EQ(myvector.Size(), 9);
}

TEST(Vector, PushBack) {
  s21::Vector<int> MyVector{1, 2, 3, 4};
  s21::Vector<int> MyVector1(5);
  s21::Vector<int> Vector{};
  MyVector.PushBack(2);
  ASSERT_EQ(MyVector.Size(), 5);
  ASSERT_EQ(MyVector1.Size(), 0);
  ASSERT_EQ(Vector.Size(), 0);
}

TEST(Vector, PopBack) {
  s21::Vector<int> MyVector{1, 2, 3, 4};
  MyVector.PopBack();
  MyVector.PopBack();
  ASSERT_EQ(MyVector[1], 2);
  ASSERT_EQ(MyVector.Size(), 2);
}

TEST(Vector, Swap) {
  s21::Vector<int> MyVector{1, 2, 3, 4, 5, 6, 7};
  s21::Vector<int> NewVector{2, 1};
  MyVector.Swap(NewVector);
  ASSERT_EQ(MyVector.Size(), 2);
  ASSERT_EQ(NewVector.Size(), 7);
}

TEST(Vector, Iterator) {
  s21::Vector<int> MyVector{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_EQ(*(MyVector.begin()), 1);
  auto iter = MyVector.end();
  ASSERT_EQ(*--iter, 9);
}


TEST(Vector, Emplace) {
  s21::Vector<int> vec{10, 20, 30};
  s21::Vector<int> vec1{1, 2, 3, 4, 5, 6};
  s21::Vector<int> vec2{10, 20, 30};
  s21::Vector<int> vec3{10, 20, 30};
  s21::Vector<int> vec4{10, 20, 30};
  vec.Emplace(vec.begin()+2, 1, 2, 3);
  vec1.Emplace(vec1.end(), 1, 2, 3);
  vec2.Emplace(vec2.begin()+2, 1, 2, 3);
  vec3.EmplaceBack(1, 2, 3);
  vec4.Emplace(vec4.begin());
  ASSERT_EQ(vec.Size(), 6);
  ASSERT_EQ(vec1.Size(), 9);
  ASSERT_EQ(vec2.Size(), 6);
  ASSERT_EQ(vec3.Size(), 6);
  ASSERT_EQ(vec4.Size(), 3);
}


TEST(Vector, IteratorsTesting) {
  s21::Vector<int> list{ 1, 2, 3, 4, 5 };
  list.Erase(list.begin() + 1);
  EXPECT_EQ(*(list.begin()), 1);
  list.Erase((list.begin()));
  EXPECT_EQ(*(++list.begin()), 4);
  EXPECT_EQ(*(list.begin()), 3);
  list.Erase((--list.end()));
  EXPECT_EQ(*(--list.end()), 4);
}
