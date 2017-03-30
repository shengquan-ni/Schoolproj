#include <string>
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include <vector>
#include <algorithm>    // std::random_shuffle
#include "q2solution.hpp"

class SetTest : public ::testing::Test {
protected:
    virtual void SetUp()    {}
    virtual void TearDown() {}
};


template<class T>
LN<T>* build_linked_list_fast(T values[], int length) {  //O(N)
  if (length == 0)
    return nullptr;

  LN<T>* front      = new LN<T>(values[0]);
  LN<T>* rear_cache = front;
  for (int i=1; i<length; ++i)
    rear_cache = rear_cache->next = new LN<T>(values[i]);

  return front;
}


template<class T>
bool all_in_order(LN<T>* l, T values[]) {
  int i = 0;
  for (LN<T>* p = l; p != nullptr; p = p->next)
    if (p->value != values[i++])
      return false;

   return true;
}


TEST_F(SetTest, relation) {
  ASSERT_EQ('=',relation("",""));
  ASSERT_EQ('>',relation("a",""));
  ASSERT_EQ('<',relation("","a"));
  ASSERT_EQ('=',relation("ant","ant"));
  ASSERT_EQ('<',relation("ant","anteater"));
  ASSERT_EQ('>',relation("anteater","ant"));
  ASSERT_EQ('>',relation("x","ant"));
}


TEST_F(SetTest, remove_all_i) {
  LN<int>* test = build_linked_list_fast(new int[3]{7,8,9},3);
  remove_all_i(test,7);
  ASSERT_TRUE(all_in_order(test, new int[2]{8,9}));

  test = build_linked_list_fast(new int[3]{5,6,7},3);
  remove_all_i(test,7);
  ASSERT_TRUE(all_in_order(test, new int[2]{5,6}));

  test = build_linked_list_fast(new int[3]{8,7,6},3);
  remove_all_i(test,7);
  ASSERT_TRUE(all_in_order(test, new int[2]{8,6}));

  test = build_linked_list_fast(new int[6]{7,5,7,7,2,7},6);
  remove_all_i(test,7);
  ASSERT_TRUE(all_in_order(test, new int[2]{5,2}));

  test = build_linked_list_fast(new int[8]{7,7,2,7,7,2,7,5},8);
  remove_all_i(test,7);
  ASSERT_TRUE(all_in_order(test, new int[3]{2,2,5}));
}


TEST_F(SetTest, remove_all_r) {
  LN<int>* test = build_linked_list_fast(new int[3]{7,8,9},3);
  remove_all_r(test,7);
  ASSERT_TRUE(all_in_order(test, new int[2]{8,9}));

  test = build_linked_list_fast(new int[3]{5,6,7},3);
  remove_all_r(test,7);
  ASSERT_TRUE(all_in_order(test, new int[2]{5,6}));

  test = build_linked_list_fast(new int[3]{8,7,6},3);
  remove_all_r(test,7);
  ASSERT_TRUE(all_in_order(test, new int[2]{8,6}));

  test = build_linked_list_fast(new int[6]{7,5,7,7,2,7},6);
  remove_all_r(test,7);
  ASSERT_TRUE(all_in_order(test, new int[2]{5,2}));

  test = build_linked_list_fast(new int[8]{7,7,2,7,7,2,7,5},8);
  remove_all_r(test,7);
  ASSERT_TRUE(all_in_order(test, new int[3]{2,2,5}));
}





int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
