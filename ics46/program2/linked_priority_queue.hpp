// Submitter: Shengqun(Ni, Shengquan)
// Partner  : changchs(Shen, Changchuan)
// We certify that we worked cooperatively on this programming
//   assignment, according to the rules for pair programming
#ifndef LINKED_PRIORITY_QUEUE_HPP_
#define LINKED_PRIORITY_QUEUE_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "array_stack.hpp"      //See operator <<


namespace ics {


#ifndef undefinedgtdefined
#define undefinedgtdefined
template<class T>
bool undefinedgt (const T& a, const T& b) {return false;}
#endif /* undefinedgtdefined */

//Instantiate the templated class supplying tgt(a,b): true, iff a has higher priority than b.
//If tgt is defaulted to undefinedgt in the template, then a constructor must supply cgt.
//If both tgt and cgt are supplied, then they must be the same (by ==) function.
//If neither is supplied, or both are supplied but different, TemplateFunctionError is raised.
//The (unique) non-undefinedgt value supplied by tgt/cgt is stored in the instance variable gt.
template<class T, bool (*tgt)(const T& a, const T& b) = undefinedgt<T>> class LinkedPriorityQueue {
  public:
    typedef bool (*gtfunc) (const T& a, const T& b);
    //Destructor/Constructors
    ~LinkedPriorityQueue();

    LinkedPriorityQueue          (bool (*cgt)(const T& a, const T& b) = undefinedgt<T>);
    LinkedPriorityQueue          (const LinkedPriorityQueue<T,tgt>& to_copy, bool (*cgt)(const T& a, const T& b) = undefinedgt<T>);
    explicit LinkedPriorityQueue (const std::initializer_list<T>& il, bool (*cgt)(const T& a, const T& b) = undefinedgt<T>);

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    explicit LinkedPriorityQueue (const Iterable& i, bool (*cgt)(const T& a, const T& b) = undefinedgt<T>);


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
    LinkedPriorityQueue<T,tgt>& operator = (const LinkedPriorityQueue<T,tgt>& rhs);
    bool operator == (const LinkedPriorityQueue<T,tgt>& rhs) const;
    bool operator != (const LinkedPriorityQueue<T,tgt>& rhs) const;

    template<class T2, bool (*gt2)(const T2& a, const T2& b)>
    friend std::ostream& operator << (std::ostream& outs, const LinkedPriorityQueue<T2,gt2>& pq);



  private:
    class LN;

  public:
    class Iterator {
      public:
        //Private constructor called in begin/end, which are friends of LinkedPriorityQueue<T,tgt>
        ~Iterator();
        T           erase();
        std::string str  () const;
        LinkedPriorityQueue<T,tgt>::Iterator& operator ++ ();
        LinkedPriorityQueue<T,tgt>::Iterator  operator ++ (int);
        bool operator == (const LinkedPriorityQueue<T,tgt>::Iterator& rhs) const;
        bool operator != (const LinkedPriorityQueue<T,tgt>::Iterator& rhs) const;
        T& operator *  () const;
        T* operator -> () const;
        friend std::ostream& operator << (std::ostream& outs, const LinkedPriorityQueue<T,tgt>::Iterator& i) {
          outs << i.str(); //Use the same meaning as the debugging .str() method
          return outs;
        }
        friend Iterator LinkedPriorityQueue<T,tgt>::begin () const;
        friend Iterator LinkedPriorityQueue<T,tgt>::end   () const;

      private:
        //If can_erase is false, current indexes the "next" value (must ++ to reach it)
        LN*             prev=nullptr;            //initialize prev to the header
        LN*             current;         //current == prev->next
        LinkedPriorityQueue<T,tgt>* ref_pq;
        int             expected_mod_count;
        bool            can_erase = true;

        //Called in friends begin/end
        Iterator(LinkedPriorityQueue<T,tgt>* iterate_over, LN* initial);
    };


    Iterator begin () const;
    Iterator end   () const;


  private:
    class LN {
      public:
        LN ()                      {}
        LN (const LN& ln)          : value(ln.value), next(ln.next){}
        LN (T v,  LN* n = nullptr) : value(v), next(n){}

        T   value;
        LN* next = nullptr;
    };


    bool (*gt) (const T& a, const T& b); // The gt used by enqueue (from template or constructor)
    LN* front     =  new LN();
    int used      =  0;                  //Cache count of nodes in linked list
    int mod_count =  0;                  //Allows sensing concurrent modification

    //Helper methods
    void delete_list(LN*& front);        //Deallocate all LNs, and set front's argument to nullptr;
};





////////////////////////////////////////////////////////////////////////////////
//
//LinkedPriorityQueue class and related definitions

//Destructor/Constructors

template<class T, bool (*tgt)(const T& a, const T& b)>
LinkedPriorityQueue<T,tgt>::~LinkedPriorityQueue() {
    delete_list(front);
}


template<class T, bool (*tgt)(const T& a, const T& b)>
LinkedPriorityQueue<T,tgt>::LinkedPriorityQueue(bool (*cgt)(const T& a, const T& b)):gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt)
{
    if (gt == (gtfunc)undefinedgt<T>)
        throw TemplateFunctionError("LinkedPriorityQueue::default constructor: neither specified");
    if (tgt != (gtfunc)undefinedgt<T> && cgt != (gtfunc)undefinedgt<T> && tgt != cgt)
        throw TemplateFunctionError("LinkedPriorityQueue::default constructor: both specified and different");
}


template<class T, bool (*tgt)(const T& a, const T& b)>
LinkedPriorityQueue<T,tgt>::LinkedPriorityQueue(const LinkedPriorityQueue<T,tgt>& to_copy, bool (*cgt)(const T& a, const T& b)):gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt)
{
    if (gt == (gtfunc)undefinedgt<T>)
        gt = to_copy.gt;
    if (tgt != (gtfunc)undefinedgt<T> && cgt != (gtfunc)undefinedgt<T> && tgt != cgt)
        throw TemplateFunctionError("LinkedPriorityQueue::length constructor: both specified and different");
    if(gt==to_copy.gt)
        *this=to_copy;
    else
        enqueue_all(to_copy);
}


template<class T, bool (*tgt)(const T& a, const T& b)>
LinkedPriorityQueue<T,tgt>::LinkedPriorityQueue(const std::initializer_list<T>& il, bool (*cgt)(const T& a, const T& b)):gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt)
{
    if (gt == (gtfunc)undefinedgt<T>)
        throw TemplateFunctionError("LinkedPriorityQueue::length constructor: neither specified");
    if (tgt != (gtfunc)undefinedgt<T> && cgt != (gtfunc)undefinedgt<T> && tgt != cgt)
        throw TemplateFunctionError("LinkedPriorityQueue::length constructor: both specified and different");
    for (const T& pq_elem : il)
        enqueue(pq_elem);

}


template<class T, bool (*tgt)(const T& a, const T& b)>
template<class Iterable>
LinkedPriorityQueue<T,tgt>::LinkedPriorityQueue(const Iterable& i, bool (*cgt)(const T& a, const T& b)):gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt)
{
    if (gt == (gtfunc)undefinedgt<T>)
        throw TemplateFunctionError("LinkedPriorityQueue::length constructor: neither specified");
    if (tgt != (gtfunc)undefinedgt<T> && cgt != (gtfunc)undefinedgt<T> && tgt != cgt)
        throw TemplateFunctionError("LinkedPriorityQueue::length constructor: both specified and different");
    for (const T& pq_elem : i)
        enqueue(pq_elem);
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

template<class T, bool (*tgt)(const T& a, const T& b)>
bool LinkedPriorityQueue<T,tgt>::empty() const {
    return used==0;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
int LinkedPriorityQueue<T,tgt>::size() const {
    return used;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
T& LinkedPriorityQueue<T,tgt>::peek () const {
    if (empty())
        throw EmptyError("LinkedPriorityQueue::peek");
   return front->next->value;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
std::string LinkedPriorityQueue<T,tgt>::str() const {
    std::ostringstream answer;
    answer << "LinkedPriorityQueue[HEADER";
    LN* temp=front->next;
    while(temp)
    {
        answer<<"->"<<temp->value;
        temp=temp->next;
    }
    answer << "](used=" << used <<",front="<<front <<",mod_count=" << mod_count << ")";
    return answer.str();
}


////////////////////////////////////////////////////////////////////////////////
//
//Commands

template<class T, bool (*tgt)(const T& a, const T& b)>
int LinkedPriorityQueue<T,tgt>::enqueue(const T& element) {
    if(used==0)
        front->next=new LN(element);
    else
    {
        LN* pre=front;
        LN* now=front->next;
        while(now && gt(now->value,element))
        {
            pre=now;
            now=now->next;
        };
        LN* to_add=new LN(element);
        pre->next=to_add;
        to_add->next=now;
    }
    ++used;
    ++mod_count;
    return 1;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
T LinkedPriorityQueue<T,tgt>::dequeue() {
    if (this->empty())
        throw EmptyError("LinkedPriorityQueue::dequeue");
    ++mod_count;
    --used;
    T result=front->next->value;
    LN* temp=front->next->next;
    delete front->next;
    front->next=temp;
    return result;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
void LinkedPriorityQueue<T,tgt>::clear() {
    delete_list(front->next);
    ++mod_count;
    used=0;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
template <class Iterable>
int LinkedPriorityQueue<T,tgt>::enqueue_all (const Iterable& i) {
    int count=0;
    for(auto v:i)
        count+=enqueue(v);
    return count;
}


////////////////////////////////////////////////////////////////////////////////
//
//Operators

template<class T, bool (*tgt)(const T& a, const T& b)>
LinkedPriorityQueue<T,tgt>& LinkedPriorityQueue<T,tgt>::operator = (const LinkedPriorityQueue<T,tgt>& rhs) {
    if (this == &rhs)
        return *this;
    gt=rhs.gt;
    used=0;
    LN* pre=front;
    LN* now=front->next;
    LN* copy=rhs.front->next;
    while(copy)
    {
        if(now)
            now->value=copy->value;
        else
        {
            pre->next=new LN(copy->value);
            now=pre->next;
        }
        ++used;
        pre=now;
        now=now->next;
        copy=copy->next;
    }
    if(now)
    {
        pre->next=nullptr;
        delete_list(now);
    }
    return *this;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
bool LinkedPriorityQueue<T,tgt>::operator == (const LinkedPriorityQueue<T,tgt>& rhs) const {
    if (this == &rhs)
        return true;

    if (gt != rhs.gt) //For PriorityQueues to be equal, they need the same gt function, and values
        return false;

    if (used != rhs.size())
        return false;

    auto i1=begin();
    auto i2=rhs.begin();
    while(i1!=end() && i2!=rhs.end())
    {
        if(*i1!=*i2)return false;
        i1++;
        i2++;
    }
    return true;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
bool LinkedPriorityQueue<T,tgt>::operator != (const LinkedPriorityQueue<T,tgt>& rhs) const {
    return !(*this == rhs);
}


template<class T, bool (*tgt)(const T& a, const T& b)>
std::ostream& operator << (std::ostream& outs, const LinkedPriorityQueue<T,tgt>& pq) {
    outs << "priority_queue[";
    if (!pq.empty()) {
        std::vector<T> v;
        auto temp=pq.front->next;
        while(temp)
        {
            v.push_back(temp->value);
            temp=temp->next;
        }
        for(int i=v.size()-1;i>=0;i--)
        {
            if(i==0)
                outs<<v[i];
            else
                outs<<v[i]<<",";
        }
    }
    outs << "]:highest";
    return outs;
}


////////////////////////////////////////////////////////////////////////////////
//
//Iterator constructors


template<class T, bool (*tgt)(const T& a, const T& b)>
auto LinkedPriorityQueue<T,tgt>::begin () const -> LinkedPriorityQueue<T,tgt>::Iterator {
    return Iterator(const_cast<LinkedPriorityQueue<T,tgt>*>(this),front->next);
}


template<class T, bool (*tgt)(const T& a, const T& b)>
auto LinkedPriorityQueue<T,tgt>::end () const -> LinkedPriorityQueue<T,tgt>::Iterator {
    return Iterator(const_cast<LinkedPriorityQueue<T,tgt>*>(this),nullptr);
}


////////////////////////////////////////////////////////////////////////////////
//
//Private helper methods

template<class T, bool (*tgt)(const T& a, const T& b)>
void LinkedPriorityQueue<T,tgt>::delete_list(LN*& front) {
    while(front)
    {
        LN* temp=front->next;
        delete front;
        front=temp;
    }
}





////////////////////////////////////////////////////////////////////////////////
//
//Iterator class definitions

template<class T, bool (*tgt)(const T& a, const T& b)>
LinkedPriorityQueue<T,tgt>::Iterator::Iterator(LinkedPriorityQueue<T,tgt>* iterate_over, LN* initial):current(initial), ref_pq(iterate_over), expected_mod_count(ref_pq->mod_count){
};


template<class T, bool (*tgt)(const T& a, const T& b)>
LinkedPriorityQueue<T,tgt>::Iterator::~Iterator()
{}


template<class T, bool (*tgt)(const T& a, const T& b)>
T LinkedPriorityQueue<T,tgt>::Iterator::erase() {
    if (expected_mod_count != ref_pq->mod_count)
        throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::erase");
    if (!can_erase)
        throw CannotEraseError("LinkedPriorityQueue::Iterator::erase Iterator cursor already erased");
    if (current==nullptr)
        throw CannotEraseError("LinkedPriorityQueue::Iterator::erase Iterator cursor beyond data structure");

    can_erase = false;
    T to_return = current->value;
    if(prev)
    {
        prev->next=current->next;
        delete current;
        current=prev->next;
    }
    else
    {
        LN* temp=current->next;
        delete current;
        current=temp;
        ref_pq->front->next=temp;
    }
    ref_pq->used--;
    ref_pq->mod_count++;
    expected_mod_count = ref_pq->mod_count;
    return to_return;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
std::string LinkedPriorityQueue<T,tgt>::Iterator::str() const {
    std::ostringstream answer;
    answer << ref_pq->str() << "/current=" << current << "/expected_mod_count=" << expected_mod_count << "/can_erase=" << can_erase;
    return answer.str();
}


template<class T, bool (*tgt)(const T& a, const T& b)>
auto LinkedPriorityQueue<T,tgt>::Iterator::operator ++ () -> LinkedPriorityQueue<T,tgt>::Iterator& {
    if (expected_mod_count != ref_pq->mod_count)
        throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator ++");

    if (current==nullptr)
        return *this;

    if (can_erase)
    {
        prev=current;
        current=current->next;
    }
    else
        can_erase = true;  //current already indexes "one beyond" deleted value

    return *this;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
auto LinkedPriorityQueue<T,tgt>::Iterator::operator ++ (int) -> LinkedPriorityQueue<T,tgt>::Iterator {
    if (expected_mod_count != ref_pq->mod_count)
        throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator ++(int)");

    if (current==nullptr)
        return *this;

    Iterator to_return(*this);
    if (can_erase)
    {
        prev=current;
        current=current->next;
    }
    else
        can_erase = true;  //current already indexes "one beyond" deleted value

    return to_return;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
bool LinkedPriorityQueue<T,tgt>::Iterator::operator == (const LinkedPriorityQueue<T,tgt>::Iterator& rhs) const {
    const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsASI == 0)
        throw IteratorTypeError("LinkedPriorityQueue::Iterator::operator ==");
    if (expected_mod_count != ref_pq->mod_count)
        throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator ==");
    if (ref_pq != rhsASI->ref_pq)
        throw ComparingDifferentIteratorsError("LinkedPriorityQueue::Iterator::operator ==");

    return current == rhsASI->current;
}


template<class T, bool (*tgt)(const T& a, const T& b)>
bool LinkedPriorityQueue<T,tgt>::Iterator::operator != (const LinkedPriorityQueue<T,tgt>::Iterator& rhs) const {
    const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsASI == 0)
        throw IteratorTypeError("LinkedPriorityQueue::Iterator::operator ==");
    if (expected_mod_count != ref_pq->mod_count)
        throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator ==");
    if (ref_pq != rhsASI->ref_pq)
        throw ComparingDifferentIteratorsError("LinkedPriorityQueue::Iterator::operator ==");

    return current != rhsASI->current;
}

template<class T, bool (*tgt)(const T& a, const T& b)>
T& LinkedPriorityQueue<T,tgt>::Iterator::operator *() const {
    if (expected_mod_count != ref_pq->mod_count)
        throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator *");
    if (!can_erase || current==nullptr) {
        std::ostringstream where;
        where << current << " when size = " << ref_pq->size();
        throw IteratorPositionIllegal("LinkedPriorityQueue::Iterator::operator * Iterator illegal: "+where.str());
    }

    return current->value;
}

template<class T, bool (*tgt)(const T& a, const T& b)>
T* LinkedPriorityQueue<T,tgt>::Iterator::operator ->() const {
    if (expected_mod_count != ref_pq->mod_count)
        throw ConcurrentModificationError("LinkedPriorityQueue::Iterator::operator *");
    if (!can_erase || current==nullptr) {
        std::ostringstream where;
        where << current << " when size = " << ref_pq->size();
        throw IteratorPositionIllegal("LinkedPriorityQueue::Iterator::operator * Iterator illegal: "+where.str());
    }

    return &current->value;
}


}

#endif /* LINKED_PRIORITY_QUEUE_HPP_ */
