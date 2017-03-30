#include <iostream>
#include <sstream>
#include "ics46goody.hpp"
#include "gtest/gtest.h"
#include "linear_array_queue.hpp"


//Simplified Queue testing for Program #0

typedef ics::LinearArrayQueue<std::string> QueueType;


class QueueTest : public ::testing::Test {
protected:
    virtual void SetUp()    {}
    virtual void TearDown() {}
};


void load(QueueType& q, std::string values) {
  std::string* v = new std::string[values.size()];
  for (unsigned i=0; i<values.size(); ++i)
    v[i] = values[i];
  for (unsigned i=0; i<values.size(); ++i)
    q.enqueue(v[i]);
  delete[] v;
}


::testing::AssertionResult unload(QueueType& q, std::string values) {
  std::string* v = new std::string[values.size()];
  for (unsigned i=0; i<values.size(); ++i)
    v[i] = values[i];
  for (unsigned i=0; i<values.size(); ++i)
    if (v[i] != q.dequeue())
      return ::testing::AssertionFailure();
  delete[] v;
  return ::testing::AssertionSuccess();
}




TEST_F(QueueTest, empty) {
  QueueType q;
  ASSERT_TRUE(q.empty());
}


TEST_F(QueueTest, size) {
  QueueType q;
  ASSERT_EQ(0,q.size());
}


TEST_F(QueueTest, peek) {
  QueueType q;
  ASSERT_THROW(q.peek(),ics::EmptyError);
}


TEST_F(QueueTest, enqueue) {
  QueueType q;
  ASSERT_EQ(1,q.enqueue("a"));
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(1, q.size());
  ASSERT_EQ("a",q.peek());

  ASSERT_EQ(1,q.enqueue("b"));
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(2, q.size());
  ASSERT_EQ("a",q.peek());

  ASSERT_EQ(1,q.enqueue("c"));
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(3, q.size());
  ASSERT_EQ("a",q.peek());

  ASSERT_EQ(1,q.enqueue("d"));
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(4, q.size());
  ASSERT_EQ("a",q.peek());

  ASSERT_EQ(1,q.enqueue("e"));
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(5, q.size());
  ASSERT_EQ("a",q.peek());
}


TEST_F(QueueTest, operator_eq_ne) {// == and !=
  QueueType q1,q2;
  ASSERT_EQ(q1,q2);

  q1.enqueue("a");
  ASSERT_NE(q1,q2);

  q1.enqueue("b");
  ASSERT_NE(q1,q2);

  q1.enqueue("c");
  ASSERT_NE(q1,q2);

  q2.enqueue("a");
  ASSERT_NE(q1,q2);

  q2.enqueue("b");
  ASSERT_NE(q1,q2);

  q2.enqueue("c");
  ASSERT_EQ(q1,q2);

  q2.enqueue("d");
  ASSERT_NE(q1,q2);

  q2.enqueue("e");
  ASSERT_NE(q1,q2);

  q1.enqueue("d");
  ASSERT_NE(q1,q2);

  q1.enqueue("e");
  ASSERT_EQ(q1,q2);


  ASSERT_EQ(q1,q1);
  ASSERT_EQ(q2,q2);
}


TEST_F(QueueTest, operator_stream_insert) {// <<
  std::ostringstream value;
  QueueType q;
  value << q;
  ASSERT_EQ("queue[]:rear", value.str());

  value.str("");
  q.enqueue("a");
  value << q;
  ASSERT_EQ("queue[a]:rear", value.str());

  value.str("");
  q.enqueue("b");
  value << q;
  ASSERT_EQ("queue[a,b]:rear", value.str());

  value.str("");
  q.enqueue("c");
  value << q;
  ASSERT_EQ("queue[a,b,c]:rear", value.str());

  value.str("");
  q.enqueue("d");
  value << q;
  ASSERT_EQ("queue[a,b,c,d]:rear", value.str());

  value.str("");
  q.enqueue("e");
  value << q;
  ASSERT_EQ("queue[a,b,c,d,e]:rear", value.str());
}


TEST_F(QueueTest, enqueue_all) {
  QueueType q,q1;
  load(q1,"abcde");
  q.enqueue_all(q1);
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(5, q.size());
  ASSERT_EQ(q,q1);
}


TEST_F(QueueTest, clear) {
  QueueType q;
  q.clear();
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0, q.size());
  ASSERT_THROW(q.peek(),ics::EmptyError);

  load(q,"a");
  q.clear();
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0, q.size());
  ASSERT_THROW(q.peek(),ics::EmptyError);

  load(q,"ab");
  q.clear();
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0, q.size());
  ASSERT_THROW(q.peek(),ics::EmptyError);

  load(q,"abc");
  q.clear();
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0, q.size());
  ASSERT_THROW(q.peek(),ics::EmptyError);

  load(q,"abcd");
  q.clear();
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0, q.size());
  ASSERT_THROW(q.peek(),ics::EmptyError);

  load(q,"abcde");
  q.clear();
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0, q.size());
  ASSERT_THROW(q.peek(),ics::EmptyError);
}


TEST_F(QueueTest, dequeue1) {
  QueueType q;
  load(q,"abcde");
  ASSERT_EQ("a",q.dequeue());
  ASSERT_EQ("b",q.dequeue());
  ASSERT_EQ("c",q.dequeue());
  ASSERT_EQ("d",q.dequeue());
  ASSERT_EQ("e",q.dequeue());
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0, q.size());
  ASSERT_THROW(q.peek(),ics::EmptyError);
}


TEST_F(QueueTest, dequeue2) {
  QueueType q;
  load(q,"abcde");
  ASSERT_EQ("a",q.dequeue());
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(4, q.size());
  ASSERT_EQ("b", q.peek());

  ASSERT_EQ("b",q.dequeue());
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(3, q.size());
  ASSERT_EQ("c", q.peek());

  ASSERT_EQ("c",q.dequeue());
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(2, q.size());
  ASSERT_EQ("d", q.peek());

  ASSERT_EQ("d",q.dequeue());
  ASSERT_FALSE(q.empty());
  ASSERT_EQ(1, q.size());
  ASSERT_EQ("e", q.peek());

  ASSERT_EQ("e",q.dequeue());
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0, q.size());
  ASSERT_THROW(q.peek(),ics::EmptyError);
}


TEST_F(QueueTest, assignment) {
  QueueType q1,q2;
  load(q2,"abcde");
  q1 = q2;
  ASSERT_EQ(q1,q2);

  q2.clear();
  load(q2,"ab");
  q1 = q2;
  ASSERT_EQ(q1,q2);

  q2.clear();
  load(q2,"abcdefghi");
  q1 = q2;
  ASSERT_EQ(q1,q2);

}


TEST_F(QueueTest, iterator_simple) {
  QueueType q;
  q.enqueue("a");
  q.enqueue("b");
  q.enqueue("c");

  std::string qvalues[] ={"a","b","c"};
  int i = 0;
  for (std::string x : q)
    ASSERT_EQ(qvalues[i++],x);

  i = 0;
  for (auto it = q.begin(); it != q.end(); ++it)
    ASSERT_EQ(qvalues[i++],*it);

  for (auto it = q.begin(); it != q.end(); ++it)
    it.erase();
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(0,q.size());
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
