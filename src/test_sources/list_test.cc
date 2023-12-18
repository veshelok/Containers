#include "s21_list.h"

#include <gtest/gtest.h>

TEST(List, InitTest) {
  s21::List<int> list{};
  ASSERT_TRUE(list.Empty());
}

TEST(List, ConstructorWithSize) {
  s21::List<int> list(5);
  const s21::List<int> clist(5);
  ASSERT_EQ(list.Size(), 5);
  ASSERT_EQ(clist.Size(), 5);
}

TEST(List, CopyConstructor) {
  const s21::List<int> clist{1, 2, 3, 4, 5};
  const s21::List<int> copy_clist{clist};
  ASSERT_EQ(copy_clist.Size(), 5);
  ASSERT_EQ(clist.Size(), 5);
}

TEST(List, MoveAssignment) {
  s21::List<int> list;
  list = {s21::List<int> {1, 2, 3, 4, 5 }};
  ASSERT_EQ(list.Size(), 5);
  s21::List<int>::Iterator iter {list.begin()};
  ASSERT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 4);
  ++iter;
  EXPECT_EQ(*iter, 5);
}

TEST(List, MoveConstructor) {
  s21::List<int> list {std::move(s21::List<int> {1, 2, 3, 4, 5})};
  ASSERT_EQ(list.Size(), 5);
  s21::List<int>::Iterator iter {list.begin()};
  ASSERT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 4);
  ++iter;
  EXPECT_EQ(*iter, 5);
}

TEST(List, IterBegin) {
  s21::List<int> list{};
  list.PushBack(5);
  s21::List<int>::Iterator iter = list.begin();
  ASSERT_EQ(*iter, 5);
}

TEST(List, PopTest) {
  s21::List<int> list{};
  list.PushBack(5);
  list.PushBack(5);
  list.PopBack();
  list.PopBack();
  list.PopBack();
  ASSERT_EQ(list.Size(), 0);
}

TEST(List, ClearList) {
  s21::List<int> list(5);
  list.Clear();
  ASSERT_EQ(list.Size(), 0);
}

TEST(List, MaxSize) {
  s21::List<int> list;
  ASSERT_EQ(list.MaxSize(), std::numeric_limits<std::size_t>::max());
}

TEST(List, PushFront) {
  s21::List<int> list;
  list.PushFront(5);
  list.PushFront(5);
  ASSERT_EQ(list.Size(), 2);
  s21::List<int>::Iterator iter {list.begin()};
  ASSERT_EQ(*iter, 5);
  ++iter;
  ASSERT_EQ(*iter, 5);
}

TEST(List, PopFront) {
  s21::List<int> list;
  list.PushFront(5);
  list.PushFront(5);
  list.PopFront();
  list.PopFront();
  list.PopFront();
  ASSERT_EQ(list.Size(), 0);
}

TEST(List, FrontTest) {
  s21::List<int> list;
  list.PushFront(5);
  ASSERT_EQ(list.Front(), 5);
  list.PopFront();
  ASSERT_EQ(list.Front(), 0);
}

TEST(List, BackTest) {
  s21::List<int> list;
  list.PushFront(5);
  ASSERT_EQ(list.Back(), 5);
  list.PopFront();
  ASSERT_EQ(list.Back(), 0);
}

TEST(List, InitializerListTest) {
  s21::List<int> list {1, 2, 3, 4, 5};
  s21::List<int>::Iterator iter {list.begin()};
  ASSERT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 4);
  ++iter;
  EXPECT_EQ(*iter, 5);
}

TEST(List, ConstListTest) {
  const s21::List<int> list {1, 2, 3, 4, 5};
  s21::List<int>::ConstIterator iter {list.begin()};
  ASSERT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 4);
  ++iter;
  EXPECT_EQ(*iter, 5);
}

TEST(List, InsertTestEmptyList) {
  s21::List<int> list;
  EXPECT_EQ(*(list.Insert(list.begin(), 1)), 1);
  EXPECT_EQ(*(list.Insert(list.begin(), 2)), 2);
  EXPECT_EQ(*(list.Insert(list.begin(), 3)), 3);
  EXPECT_EQ(*(list.begin()), 3);
  EXPECT_EQ(*(--list.end()), 1);
  list.Clear();
  list.Insert(list.end(), 8);
  EXPECT_EQ(*(list.begin()), 8);
}

TEST(List, InsertTestInTheMiddle) {
  s21::List<int> list {1, 2, 3, 4, 5};
  auto iter = list.begin();
  ++iter;
  ++iter;
  EXPECT_EQ(*(list.Insert(iter, 999)), 999);
}

TEST(List, EraseTest) {
  s21::List<int> list{1, 2, 3, 4, 5};
  list.Erase(list.begin());
  EXPECT_EQ(*(list.begin()), 2);
  list.Erase((list.begin()));
  EXPECT_EQ(*(list.begin()), 3);
  list.Erase((--list.end()));
  EXPECT_EQ(*(--list.end()), 4);
}

TEST(List, EraseTestAllList) {
  s21::List<int> list{1, 2, 3, 4, 5};
  for (auto iter = list.begin(); iter != list.end(); ) {
    auto tmp_iter {iter++};  // To avoid dangling iterator
    list.Erase(tmp_iter);
  }
  EXPECT_EQ(list.Size(), 0);
}

TEST(List, UniqueTest1) {
  s21::List<int> list{1, 2, 3, 2, 2};
  list.Unique();
  auto iter = list.begin();
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
}

TEST(List, UniqueTest2) {
  s21::List<int> list{2, 2, 2, 2, 2, 2};
  list.Unique();
  auto iter = list.begin();
  EXPECT_EQ(*iter, 2);
  EXPECT_EQ(list.Size(), 1);
}

TEST(List, ReverseList1) {
  s21::List<int> list{1, 2, 3};
  list.Reverse();
  auto iter = list.begin();
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 1);
}

TEST(List, ReverseList2) {
  s21::List<int> list{};
  list.Reverse();
  EXPECT_EQ(list.Size(), 0);
}

TEST(List, SwapListTest1) {
  s21::List<int> list1{1, 2, 3};
  s21::List<int> list2{1};
  list1.Swap(list2);
  auto iter {list1.begin()};
  EXPECT_EQ(*iter++, 1);
  iter = list2.begin();
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
}

TEST(List, SwapListTest2) {
  s21::List<int> list1{1, 2, 3};
  s21::List<int> list2;
  list1.Swap(list2);
  auto iter {list2.begin()};
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(list1.Size(), 0);
}

TEST(List, SpliceTest) {
  s21::List<int> list1{1, 2, 3};
  s21::List<int> list2{9, 8};
  s21::List<int>::Iterator iter = list1.begin();
  s21::List<int>::Iterator iter_to_list_2 = list2.begin();
  list1.Splice(++iter, list2);
  EXPECT_EQ(*iter, 2);
  iter = list1.begin();
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 9);
  EXPECT_EQ(*iter++, 8);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(list1.Size(), 5);
  EXPECT_EQ(*iter_to_list_2++, 9);
  EXPECT_EQ(*iter_to_list_2, 8);
}

TEST(List, SpliceTestBegin) {
  s21::List<int> list1{1, 2, 3};
  s21::List<int> list2{9, 8};
  s21::List<int>::Iterator iter = list1.begin();
  s21::List<int>::Iterator iter_to_list_2 = list2.begin();
  list1.Splice(iter, list2);
  EXPECT_EQ(*iter, 1);
  iter = list1.begin();
  EXPECT_EQ(*iter++, 9);
  EXPECT_EQ(*iter++, 8);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(list1.Size(), 5);
  EXPECT_EQ(*iter_to_list_2++, 9);
  EXPECT_EQ(*iter_to_list_2, 8);
}

TEST(List, SpliceTestEnd) {
  s21::List<int> list1{1, 2, 3};
  s21::List<int> list2{9, 8};
  s21::List<int>::Iterator iter = list1.end();
  s21::List<int>::Iterator iter_to_list_2 = list2.begin();
  list1.Splice(iter, list2);
  EXPECT_EQ(*(--iter), 3);
  iter = list1.begin();
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 9);
  EXPECT_EQ(*iter++, 8);
  EXPECT_EQ(list1.Size(), 5);
  EXPECT_EQ(*iter_to_list_2++, 9);
  EXPECT_EQ(*iter_to_list_2, 8);
}

TEST(List, SpliceTestEmpty) {
  s21::List<int> list1{1, 2, 3};
  s21::List<int> list2;
  s21::List<int>::Iterator iter = list1.end();
  list1.Splice(iter, list2);
  EXPECT_EQ(*(--iter), 3);
  iter = list1.begin();
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(list1.Size(), 3);
}

TEST(List, SortFirstLast) {
  s21::List<int> list1{1, 2, 3, 2, 0};
  list1.Sort();
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
}

TEST(List, SortWithoutSwaps) {
  s21::List<int> list1{0, 1, 2, 3, 4};
  list1.Sort();
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
}

TEST(List, SortReverse) {
  s21::List<int> list1{0, 1, 2, 3, 4};
  list1.Reverse();
  list1.Sort();
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
}

TEST(List, SortSameElements) {
  s21::List<int> list1{0, 0, 0, 0, 0};
  list1.Sort();
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
}

TEST(List, MergeTwoDifferentLists) {
  s21::List<int> list1{2, 4};
  s21::List<int> list2{0, 1, 3};
  list1.Merge(list2);
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
}

TEST(List, MergeTwoZeroLists) {
  s21::List<int> list1{0, 0, 0};
  s21::List<int> list2{0, 0, 0, 0};
  list1.Merge(list2);
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
}

TEST(List, MergeTwoSameLists) {
  s21::List<int> list1{0, 1, 2, 3, 4};
  s21::List<int> list2{0, 1, 2, 3, 4};
  list1.Merge(list2);
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
  EXPECT_EQ(*iter++, 4);
}

TEST(List, EmplaceTest) {
  s21::List<int> list1{0, 1, 2, 3, 4};
  list1.Emplace(++list1.begin(), 9, 8, 7, 6);
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 9);
  EXPECT_EQ(*iter++, 8);
  EXPECT_EQ(*iter++, 7);
  EXPECT_EQ(*iter++, 6);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
}

TEST(List, EmplaceBegin) {
  s21::List<int> list1{0, 1, 2, 3, 4};
  list1.Emplace(list1.begin(), 9, 8, 7, 6);
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 9);
  EXPECT_EQ(*iter++, 8);
  EXPECT_EQ(*iter++, 7);
  EXPECT_EQ(*iter++, 6);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
}

TEST(List, EmplaceEnd) {
  s21::List<int> list1{0, 1, 2, 3, 4};
  list1.Emplace(list1.end(), 9, 8, 7, 6);
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
  EXPECT_EQ(*iter++, 9);
  EXPECT_EQ(*iter++, 8);
  EXPECT_EQ(*iter++, 7);
  EXPECT_EQ(*iter++, 6);
}

TEST(List, EmplaceFrontTest) {
  s21::List<int> list1{0, 1, 2, 3, 4};
  list1.EmplaceFront(9, 8, 7, 6);
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 9);
  EXPECT_EQ(*iter++, 8);
  EXPECT_EQ(*iter++, 7);
  EXPECT_EQ(*iter++, 6);
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
}

TEST(List, EmplaceBack) {
  s21::List<int> list1{0, 1, 2, 3, 4};
  list1.EmplaceBack(9, 8, 7, 6);
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
  EXPECT_EQ(*iter++, 9);
  EXPECT_EQ(*iter++, 8);
  EXPECT_EQ(*iter++, 7);
  EXPECT_EQ(*iter++, 6);
}

TEST(List, EmplaceEmpty) {
  s21::List<int> list1{0, 1, 2, 3, 4};
  list1.Emplace(++list1.begin());
  auto iter = list1.begin();
  EXPECT_EQ(*iter++, 0);
  EXPECT_EQ(*iter++, 1);
  EXPECT_EQ(*iter++, 2);
  EXPECT_EQ(*iter++, 3);
  EXPECT_EQ(*iter++, 4);
}
