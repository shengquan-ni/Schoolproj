// Shengquan Ni 46564157
#ifndef LINEAR_ARRAY_QUEUE_HPP_
#define LINEAR_ARRAY_QUEUE_HPP_

#include <string>
#include <iostream>
#include <initializer_list>
#include <sstream>
#include "ics_exceptions.hpp"


namespace ics {


template<class T> class LinearArrayQueue {
  public:
    //Destructor/Constructors
    ~LinearArrayQueue();

    LinearArrayQueue();
    explicit LinearArrayQueue(int initialLength);
    LinearArrayQueue         (const LinearArrayQueue<T>& to_copy);
    LinearArrayQueue         (std::initializer_list<T> il);

    //Iterable class must support "for-each" loop: .begin()/.end()/.size() and prefix ++ on returned result
    template <class Iterable>
    LinearArrayQueue (const Iterable& i);


    //Queries
    bool empty      () const;
    int  size       () const;
    T&   peek       () const;
    std::string str () const; //supplies useful debugging information; contrast to operator <<


    //Commands
    int  enqueue (const T& element);
    T    dequeue ();
    void clear   ();

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    int enqueue_all (const Iterable& i);


    //Operators
    LinearArrayQueue<T>& operator = (const LinearArrayQueue<T>& rhs);
    bool operator == (const LinearArrayQueue<T>& rhs) const;
    bool operator != (const LinearArrayQueue<T>& rhs) const;

    template<class T2>
    friend std::ostream& operator << (std::ostream& outs, const LinearArrayQueue<T2>& q);



    class Iterator {
      public:
        //Private constructor called in begin/end, which are friends of ArrayQueue<T>
        ~Iterator();
        T           erase();
        std::string str  () const;
        LinearArrayQueue<T>::Iterator& operator ++ ();
        LinearArrayQueue<T>::Iterator  operator ++ (int);
        bool operator == (const LinearArrayQueue<T>::Iterator& rhs) const;
        bool operator != (const LinearArrayQueue<T>::Iterator& rhs) const;
        T& operator *  () const;
        T* operator -> () const;
        friend std::ostream& operator << (std::ostream& outs, const LinearArrayQueue<T>::Iterator& i) {
          outs << i.str(); //Use the same meaning as the debugging .str() method
          return outs;
        }
        friend Iterator LinearArrayQueue<T>::begin () const;
        friend Iterator LinearArrayQueue<T>::end   () const;

      private:
        //If can_erase is false, current indexes the "next" value (must ++ to reach it)
        int                  current;
        LinearArrayQueue<T>* ref_queue;
        int                  expected_mod_count;
        bool                 can_erase = true;

        //Called in friends begin/end and postfix ++
        Iterator(LinearArrayQueue<T>* iterate_over, int initial);
    };


    Iterator begin () const;
    Iterator end   () const;


  private:
    T*  queue;         //Linear array with front index at 0, rear at used-1
    int length    = 0; //Physical length of array (must be > .size())
    int used      = 0; //Amount of array used
    int mod_count = 0; //For sensing concurrent modification

    //Helper methods
    int  erase_at     (int i);
    void ensure_length(int new_length);
  };



////////////////////////////////////////////////////////////////////////////////
//
//LinearArrayQueue class and related definitions

//Destructor/Constructors

template<class T>
LinearArrayQueue<T>::~LinearArrayQueue() {
  delete[] queue;
}


template<class T>
LinearArrayQueue<T>::LinearArrayQueue() {
  queue = new T[length];
}


template<class T>
LinearArrayQueue<T>::LinearArrayQueue(int initial_length)
: length(initial_length) {
  if (length < 0)
    length = 0;
  queue = new T[length];
}


template<class T>
LinearArrayQueue<T>::LinearArrayQueue(const LinearArrayQueue<T>& to_copy)
: length(to_copy.length), used(to_copy.used) {
  queue = new T[length];
  for (int i=0; i<used; ++i)
    queue[i] = to_copy.queue[i];
}


template<class T>
LinearArrayQueue<T>::LinearArrayQueue(std::initializer_list<T> il)
: length(il.size()) {
  queue = new T[length];
  for (const T& q_elem : il)
    enqueue(q_elem);
}


template<class T>
template<class Iterable>
LinearArrayQueue<T>::LinearArrayQueue(const Iterable& i)
: length(i.size()) {
  queue = new T[length];
  for (const T& v : i)
    enqueue(v);
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

template<class T>
bool LinearArrayQueue<T>::empty() const {
  return used == 0;
}


template<class T>
inline int LinearArrayQueue<T>::size() const {
  return used;
}


template<class T>
T& LinearArrayQueue<T>::peek () const {
  if (this->empty())
    throw EmptyError("LinearArrayQueue::peek");

  return queue[0];
}


template<class T>
std::string LinearArrayQueue<T>::str() const {
  std::ostringstream answer;
  answer << "LinearArrayQueue[";

  if (length != 0) {
    answer << "0:" << queue[0];
    for (int i = 1; i < length; ++i)
      answer << "," << i << ":" << queue[i];
  }

  answer << "](length=" << length << ",used=" << used << ",mod_count=" << mod_count << ")";
  return answer.str();
}


////////////////////////////////////////////////////////////////////////////////
//
//Commands

template<class T>
int LinearArrayQueue<T>::enqueue(const T& element) {
  this->ensure_length(used+1);
  queue[used++] = element;
  ++mod_count;
  return 1;
}


template<class T>
T LinearArrayQueue<T>::dequeue() {
  if (this->empty())
    throw EmptyError("LinearArrayQueue::dequeue");

  T answer = queue[0];
  for (int i=0; i<used-1; ++i)
    queue[i] = queue[i+1];
  --used; //here is the error; this statement should not be commented!
  ++mod_count;
  return answer;
}


template<class T>
void LinearArrayQueue<T>::clear() {
  used = 0;
  ++mod_count;
}


template<class T>
template<class Iterable>
int LinearArrayQueue<T>::enqueue_all(const Iterable& i) {
  int count = 0;
  for (auto v : i)
     count += enqueue(v);

    return count;
}


////////////////////////////////////////////////////////////////////////////////
//
//Operators

template<class T>
LinearArrayQueue<T>& LinearArrayQueue<T>::operator = (const LinearArrayQueue<T>& rhs) {
  if (this == &rhs)
    return *this;
  this->ensure_length(rhs.used);
  used = rhs.used;
  for (int i=0; i<used; ++i)
    queue[i] = rhs.queue[i];
  ++mod_count;
  return *this;
}


template<class T>
bool LinearArrayQueue<T>::operator == (const LinearArrayQueue<T>& rhs) const {
  if (this == &rhs)
    return true;
  if (used != rhs.size())
    return false;
  LinearArrayQueue<T>::Iterator rhs_i = rhs.begin();
  for (int i=0; i<used; ++i,++rhs_i)
    if (queue[i] != *rhs_i)
      return false;

  return true;
}


template<class T>
bool LinearArrayQueue<T>::operator != (const LinearArrayQueue<T>& rhs) const {
  return !(*this == rhs);
}

template<class T>
std::ostream& operator << (std::ostream& outs, const LinearArrayQueue<T>& q) {
  outs << "queue[";

  if (!q.empty()) {
    outs << q.queue[0];
    for (int i = 1; i < q.used; ++i)
      outs << ","<< q.queue[i];
  }

  outs << "]:rear";
  return outs;
}


////////////////////////////////////////////////////////////////////////////////
//
//Iterator constructors

template<class T>
auto LinearArrayQueue<T>::begin () const -> LinearArrayQueue<T>::Iterator {
  return Iterator(const_cast<LinearArrayQueue<T>*>(this),0);
}


template<class T>
auto LinearArrayQueue<T>::end () const -> LinearArrayQueue<T>::Iterator {
  return Iterator(const_cast<LinearArrayQueue<T>*>(this),used);
}


////////////////////////////////////////////////////////////////////////////////
//
//Private helper methods

template<class T>
int LinearArrayQueue<T>::erase_at(int i) {
  //Shift all subsequent values to keep order and restore continquity
  for (int j=i; j<used-1; ++j)
    queue[j] = queue[j+1];
  --used;
  ++mod_count;
  return 1;
}


template<class T>
void LinearArrayQueue<T>::ensure_length(int new_length) {
  if (length >= new_length)
    return;
  T*  old_queue  = queue;
  length = std::max(new_length,2*length);
  queue = new T[length];
  for (int i=0; i<used; ++i)
    queue[i] = old_queue[i];

  delete [] old_queue;
}





////////////////////////////////////////////////////////////////////////////////
//
//Iterator class definitions

template<class T>
LinearArrayQueue<T>::Iterator::Iterator(LinearArrayQueue<T>* iterate_over, int initial) : current(initial), ref_queue(iterate_over) {
  expected_mod_count = ref_queue->mod_count;
}


template<class T>
LinearArrayQueue<T>::Iterator::~Iterator() {}


template<class T>
T LinearArrayQueue<T>::Iterator::erase() {
  if (expected_mod_count != ref_queue->mod_count)
    throw ConcurrentModificationError("LinearArrayQueue::Iterator::erase");
  if (!can_erase)
    throw CannotEraseError("LinearArrayQueue::Iterator::erase Iterator cursor already erased");
  if (current < 0 || current >= ref_queue->used)
    throw CannotEraseError("LinearArrayQueue::Iterator::erase Iterator cursor beyond data structure");

  can_erase = false;
  T toReturn = ref_queue->queue[current];
  ref_queue->erase_at(current);
  expected_mod_count = ref_queue->mod_count;
  return toReturn;
}


template<class T>
std::string LinearArrayQueue<T>::Iterator::str() const {
  std::ostringstream answer;
  answer << ref_queue->str() << "(current=" << current << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
  return answer.str();
}


template<class T>
auto LinearArrayQueue<T>::Iterator::operator ++ () -> LinearArrayQueue<T>::Iterator& {
  if (expected_mod_count != ref_queue->mod_count)
    throw ConcurrentModificationError("LinearArrayQueue::Iterator::operator ++");

  if (current == ref_queue->used)
    return *this;

  if (!can_erase)
    can_erase = true;
  else
    ++current;

  return *this;
}


template<class T>
auto LinearArrayQueue<T>::Iterator::operator ++ (int) -> LinearArrayQueue<T>::Iterator {
  if (expected_mod_count != ref_queue->mod_count)
    throw ConcurrentModificationError("LinearArrayQueue::Iterator::operator ++(int)");

  if (current == ref_queue->used)
    return *this;

  Iterator to_return(*this);
  if (!can_erase)
    can_erase = true;
  else{
    ++to_return.current;
    ++current;
  }

  return to_return;
}


template<class T>
bool LinearArrayQueue<T>::Iterator::operator == (const LinearArrayQueue<T>::Iterator& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw ics::IteratorTypeError("LinearArrayQueue::Iterator::operator ==");
  if (expected_mod_count != ref_queue->mod_count)
    throw ConcurrentModificationError("LinearArrayQueue::Iterator::operator ==");
  if (ref_queue != rhsASI->ref_queue)
    throw ComparingDifferentIteratorsError("LinearArrayQueue::Iterator::operator ==");

  return current == rhsASI->current;
}


template<class T>
bool LinearArrayQueue<T>::Iterator::operator != (const LinearArrayQueue<T>::Iterator& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("LinearArrayQueue::Iterator::operator !=");
  if (expected_mod_count != ref_queue->mod_count)
    throw ConcurrentModificationError("LinearArrayQueue::Iterator::operator !=");
  if (ref_queue != rhsASI->ref_queue)
    throw ComparingDifferentIteratorsError("LinearArrayQueue::Iterator::operator !=");

  return current != rhsASI->current;
}


template<class T>
T& LinearArrayQueue<T>::Iterator::operator *() const {
  if (expected_mod_count != ref_queue->mod_count)
    throw ConcurrentModificationError("LinearArrayQueue::Iterator::operator *");
  if (!can_erase || current < 0 || current >= ref_queue->used) {
    std::ostringstream where;
    where << current << " when size = " << ref_queue->size();
    throw IteratorPositionIllegal("LinearArrayQueue::Iterator::operator * Iterator illegal: "+where.str());
  }

  return ref_queue->queue[current];
}


template<class T>
T* LinearArrayQueue<T>::Iterator::operator ->() const {
  if (expected_mod_count !=
      ref_queue->mod_count)
    throw ConcurrentModificationError("LinearArrayQueue::Iterator::operator *");
  if (!can_erase || current < 0 ||
      current >= ref_queue->used) {
    std::ostringstream where;
    where << current << " when size = " << ref_queue->size();
    throw IteratorPositionIllegal("LinearArrayQueue::Iterator::operator * Iterator illegal: "+where.str());
  }

  return &ref_queue->queue[current];
}

}

#endif /* LINEAR_ARRAY_QUEUE_HPP_ */
