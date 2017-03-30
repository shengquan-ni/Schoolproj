// Submitter: Shengqun(Ni, Shengquan)
// Partner  : changchs(Shen, Changchuan)
// We certify that we worked cooperatively on this programming
//   assignment, according to the rules for pair programming
#ifndef HASH_MAP_HPP_
#define HASH_MAP_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "pair.hpp"


namespace ics {


#ifndef undefinedhashdefined
#define undefinedhashdefined
template<class T>
int undefinedhash (const T& a) {return 0;}
#endif /* undefinedhashdefined */

//Instantiate the templated class supplying thash(a): produces a hash value for a.
//If thash is defaulted to undefinedhash in the template, then a constructor must supply chash.
//If both thash and chash are supplied, then they must be the same (by ==) function.
//If neither is supplied, or both are supplied but different, TemplateFunctionError is raised.
//The (unique) non-undefinedhash value supplied by thash/chash is stored in the instance variable hash.
template<class KEY,class T, int (*thash)(const KEY& a) = undefinedhash<KEY>> class HashMap {
  public:
    typedef ics::pair<KEY,T>   Entry;
    typedef int (*hashfunc) (const KEY& a);

    //Destructor/Constructors
    ~HashMap ();

    HashMap          (double the_load_threshold = 1.0, int (*chash)(const KEY& a) = undefinedhash<KEY>);
    explicit HashMap (int initial_bins, double the_load_threshold = 1.0, int (*chash)(const KEY& k) = undefinedhash<KEY>);
    HashMap          (const HashMap<KEY,T,thash>& to_copy, double the_load_threshold = 1.0, int (*chash)(const KEY& a) = undefinedhash<KEY>);
    explicit HashMap (const std::initializer_list<Entry>& il, double the_load_threshold = 1.0, int (*chash)(const KEY& a) = undefinedhash<KEY>);

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    explicit HashMap (const Iterable& i, double the_load_threshold = 1.0, int (*chash)(const KEY& a) = undefinedhash<KEY>);


    //Queries
    bool empty      () const;
    int  size       () const;
    bool has_key    (const KEY& key) const;
    bool has_value  (const T& value) const;
    std::string str () const; //supplies useful debugging information; contrast to operator <<


    //Commands
    T    put   (const KEY& key, const T& value);
    T    erase (const KEY& key);
    void clear ();

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    int put_all(const Iterable& i);


    //Operators

    T&       operator [] (const KEY&);
    const T& operator [] (const KEY&) const;
    HashMap<KEY,T,thash>& operator = (const HashMap<KEY,T,thash>& rhs);
    bool operator == (const HashMap<KEY,T,thash>& rhs) const;
    bool operator != (const HashMap<KEY,T,thash>& rhs) const;

    template<class KEY2,class T2, int (*hash2)(const KEY2& a)>
    friend std::ostream& operator << (std::ostream& outs, const HashMap<KEY2,T2,hash2>& m);



  private:
    class LN;

  public:
    class Iterator {
      public:
         typedef pair<int,LN*> Cursor;

        //Private constructor called in begin/end, which are friends of HashMap<T>
        ~Iterator();
        Entry       erase();
        std::string str  () const;
        HashMap<KEY,T,thash>::Iterator& operator ++ ();
        HashMap<KEY,T,thash>::Iterator  operator ++ (int);
        bool operator == (const HashMap<KEY,T,thash>::Iterator& rhs) const;
        bool operator != (const HashMap<KEY,T,thash>::Iterator& rhs) const;
        Entry& operator *  () const;
        Entry* operator -> () const;
        friend std::ostream& operator << (std::ostream& outs, const HashMap<KEY,T,thash>::Iterator& i) {
          outs << i.str(); //Use the same meaning as the debugging .str() method
          return outs;
        }
        friend Iterator HashMap<KEY,T,thash>::begin () const;
        friend Iterator HashMap<KEY,T,thash>::end   () const;

      private:
        //If can_erase is false, current indexes the "next" value (must ++ to reach it)
        Cursor                current; //Bin Index + LN* pointer; stops if LN* == nullptr
        HashMap<KEY,T,thash>* ref_map;
        int                   expected_mod_count;
        bool                  can_erase = true;

        //Helper methods
        void advance_cursors();

        //Called in friends begin/end
        Iterator(HashMap<KEY,T,thash>* iterate_over, bool from_begin);
    };


    Iterator begin () const;
    Iterator end   () const;


  private:
    class LN {
    public:
      LN ()                         : next(nullptr){}
      LN (const LN& ln)             : value(ln.value), next(ln.next){}
      LN (Entry v, LN* n = nullptr) : value(v), next(n){}

      Entry value;
      LN*   next;
  };

  int (*hash)(const KEY& k);  //Hashing function used (from template or constructor)
  LN** map      = nullptr;    //Pointer to array of pointers: each bin stores a list with a trailer node
  double load_threshold;      //used/bins <= load_threshold
  int bins      = 1;          //# bins in array (should start >= 1 so hash_compress doesn't divide by 0)
  int used      = 0;          //Cache for number of key->value pairs in the hash table
  int mod_count = 0;          //For sensing concurrent modification


  //Helper methods
  int   hash_compress        (const KEY& key)          const;  //hash function ranged to [0,bins-1]
  LN*   find_key             (const KEY& key) const;           //Returns reference to key's node or nullptr
  LN*   copy_list            (LN*   l)                 const;  //Copy the keys/values in a bin (order irrelevant)
  LN**  copy_hash_table      (LN** ht, int bins)       const;  //Copy the bins/keys/values in ht tree (order in bins irrelevant)

  void  ensure_load_threshold(int new_used);                   //Reallocate if load_factor > load_threshold
  void  delete_hash_table    (LN**& ht, int bins);             //Deallocate all LN in ht (and the ht itself; ht == nullptr)
};





////////////////////////////////////////////////////////////////////////////////
//
//HashMap class and related definitions

//Destructor/Constructors

template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::~HashMap() {
    delete_hash_table(map,bins);
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::HashMap(double the_load_threshold, int (*chash)(const KEY& k)):load_threshold(the_load_threshold),hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash)
{
    if (hash == (hashfunc)undefinedhash<KEY>)
        throw TemplateFunctionError("HashMap::default constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::default constructor: both specified and different");

    map = new LN*[bins];
    for(int i=0;i<bins;++i)
        map[i]=new LN();

}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::HashMap(int initial_bins, double the_load_threshold, int (*chash)(const KEY& k)):bins(initial_bins),load_threshold(the_load_threshold),hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash)
{
    if (hash == (hashfunc)undefinedhash<KEY>)
        throw TemplateFunctionError("HashMap::default constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::default constructor: both specified and different");

    map = new LN*[bins];
    for(int i=0;i<bins;++i)
        map[i]=new LN();
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::HashMap(const HashMap<KEY,T,thash>& to_copy, double the_load_threshold, int (*chash)(const KEY& a)):load_threshold(the_load_threshold),hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash)
{
    if (hash == (hashfunc)undefinedhash<KEY>)
        hash=to_copy.hash;
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::default constructor: both specified and different");
    if(hash==to_copy.hash)
    {
        map=copy_hash_table(to_copy.map,to_copy.bins);
        bins=to_copy.bins;
        ensure_load_threshold(used=to_copy.used);
    }
    else
    {
        map = new LN*[bins];
        for(int i=0;i<bins;++i)
            map[i]=new LN();
        put_all(to_copy);
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::HashMap(const std::initializer_list<Entry>& il, double the_load_threshold, int (*chash)(const KEY& k)):load_threshold(the_load_threshold),hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash)
{
    if (hash == (hashfunc)undefinedhash<KEY>)
        throw TemplateFunctionError("HashMap::default constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::default constructor: both specified and different");
    map = new LN*[bins];
    for(int i=0;i<bins;++i)
        map[i]=new LN();
    put_all(il);
}


template<class KEY,class T, int (*thash)(const KEY& a)>
template <class Iterable>
HashMap<KEY,T,thash>::HashMap(const Iterable& i, double the_load_threshold, int (*chash)(const KEY& k)):load_threshold(the_load_threshold),hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash)
{
    if (hash == (hashfunc)undefinedhash<KEY>)
        throw TemplateFunctionError("HashMap::default constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::default constructor: both specified and different");
    map = new LN*[bins];
    for(int i=0;i<bins;++i)
        map[i]=new LN();
    put_all(i);
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::empty() const {
    return used==0;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
int HashMap<KEY,T,thash>::size() const {
    return used;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::has_key (const KEY& key) const {
    return find_key(key)!=nullptr;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::has_value (const T& value) const {
    for(int i=0;i<bins;++i)
    {
        for(auto t=map[i];t->next!=nullptr;t=t->next)
            if(t->value.second==value)
                return true;
    }
    return false;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
std::string HashMap<KEY,T,thash>::str() const {
    std::ostringstream answer;
    for(int i=0;i<bins;++i)
    {
        answer<<"["<<i<<"]: ";
        for(auto t=map[i];t->next!=nullptr;t=t->next)
            answer<<t->value.first<<"->"<<t->value.second<<" -> ";
        answer<<"TRAILER"<<std::endl;
    }
    return answer.str();
}


////////////////////////////////////////////////////////////////////////////////
//
//Commands

template<class KEY,class T, int (*thash)(const KEY& a)>
T HashMap<KEY,T,thash>::put(const KEY& key, const T& value) {
    ++mod_count;
    if(has_key(key))
    {
        auto t=find_key(key);
        auto result=t->value.second;
        t->value.second=value;
        return result;
    }
    else
    {
        ensure_load_threshold(++used);
        auto i=hash_compress(key);
        map[i]=new LN(ics::make_pair(key,value),map[i]);
        return value;
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
T HashMap<KEY,T,thash>::erase(const KEY& key) {
    ++mod_count;
    auto t=find_key(key);
    if(t)
    {
        --used;
        auto result=t->value.second;
        auto temp=t->next;
        t->value = t->next->value;
        t->next = t->next->next;
        delete temp;
        return result;
    }
    std::ostringstream answer;
    answer << "HashMap::erase: key(" << key << ") not in Map";
    throw KeyError(answer.str());
}


template<class KEY,class T, int (*thash)(const KEY& a)>
void HashMap<KEY,T,thash>::clear() {
    used=0;
    for(int i=0;i<bins;++i)
    {
        auto temp=map[i];
        while(temp->next)
        {
            auto temp2=temp->next;
            delete temp;
            temp=temp2;
        }
        map[i]=temp;
    }
    ++mod_count;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
template<class Iterable>
int HashMap<KEY,T,thash>::put_all(const Iterable& i) {
    int count=0;
    for(auto v:i)
    {
        ++count;
        put(v.first,v.second);
    }
    return count;
}


////////////////////////////////////////////////////////////////////////////////
//
//Operators

template<class KEY,class T, int (*thash)(const KEY& a)>
T& HashMap<KEY,T,thash>::operator [] (const KEY& key) {
    auto temp=find_key(key);
    if(temp)
        return temp->value.second;
    else
    {
        ensure_load_threshold(++used);
        int i=hash_compress(key);
        map[i]=new LN(ics::make_pair(key,T()),map[i]);
        ++mod_count;
        return map[i]->value.second;
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
const T& HashMap<KEY,T,thash>::operator [] (const KEY& key) const {
    auto temp=find_key(key);
    if(temp)
        return temp->value.second;
    std::ostringstream answer;
    answer << "HashMap::erase: key(" << key << ") not in Map";
    throw KeyError(answer.str());
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>& HashMap<KEY,T,thash>::operator = (const HashMap<KEY,T,thash>& rhs) {
    if (this == &rhs)
        return *this;
    clear();
    hash=rhs.hash;
    map=copy_hash_table(rhs.map,rhs.bins);
    load_threshold=rhs.load_threshold;
    bins=rhs.bins;
    ensure_load_threshold(used=rhs.used);
    ++mod_count;
    return *this;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::operator == (const HashMap<KEY,T,thash>& rhs) const {
    if (this == &rhs)
        return true;

    if (used != rhs.size())
        return false;
    if(empty())
        return true;
    auto i=begin();
    while(i!=end())
    {
        if(!rhs.has_key((*i).first))return false;
        if((*i).second!=rhs[(*i).first])return false;
        ++i;
    }
    return true;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::operator != (const HashMap<KEY,T,thash>& rhs) const {
    return !(*this == rhs);
}


template<class KEY,class T, int (*thash)(const KEY& a)>
std::ostream& operator << (std::ostream& outs, const HashMap<KEY,T,thash>& m) {
    outs << "map[";
    if(!m.empty())
    {
        auto i = m.begin();
        outs << (*i).first << "->" << (*i).second;
        ++i;
        while (i != m.end())
        {
            outs << "," << (*i).first << "->" << (*i).second;
            ++i;
        }
    }
    outs << "]";
    return outs;
}


////////////////////////////////////////////////////////////////////////////////
//
//Iterator constructors

template<class KEY,class T, int (*thash)(const KEY& a)>
auto HashMap<KEY,T,thash>::begin () const -> HashMap<KEY,T,thash>::Iterator {
    return Iterator(const_cast<HashMap<KEY,T,thash>*>(this),true);
}


template<class KEY,class T, int (*thash)(const KEY& a)>
auto HashMap<KEY,T,thash>::end () const -> HashMap<KEY,T,thash>::Iterator {
    return Iterator(const_cast<HashMap<KEY,T,thash>*>(this),false);
}


///////////////////////////////////////////////////////////////////////////////
//
//Private helper methods

template<class KEY,class T, int (*thash)(const KEY& a)>
int HashMap<KEY,T,thash>::hash_compress (const KEY& key) const {
    int raw_result=hash(key);
    if(raw_result<0)
        return (-raw_result)%bins;
    else
        return raw_result%bins;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
typename HashMap<KEY,T,thash>::LN* HashMap<KEY,T,thash>::find_key (const KEY& key) const {
    int i=hash_compress(key);
    for(auto t=map[i];t->next!=nullptr;t=t->next)
    {
        if(t->value.first==key)
            return t;
    }
    return nullptr;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
typename HashMap<KEY,T,thash>::LN* HashMap<KEY,T,thash>::copy_list (LN* l) const {
    if(!l)return nullptr;
    return new LN(l->value,copy_list(l->next));
}


template<class KEY,class T, int (*thash)(const KEY& a)>
typename HashMap<KEY,T,thash>::LN** HashMap<KEY,T,thash>::copy_hash_table (LN** ht, int bins) const {
    auto result=new LN*[bins];
    for(int i=0;i<bins;++i)
        result[i]=copy_list(ht[i]);
    return result;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
void HashMap<KEY,T,thash>::ensure_load_threshold(int new_used) {
    if((double)new_used/bins>load_threshold)
    {
        auto new_map=new LN*[bins<<1];
        int old_bins=bins;
        bins*=2;
        for(int i=0;i<bins;++i)
            new_map[i]=new LN();
        for(int i=0;i<old_bins;++i)
        {
            while(map[i]->next!=nullptr)
            {
                auto new_index=hash_compress(map[i]->value.first);
                auto temp=new_map[new_index];
                auto temp2=map[i]->next;
                new_map[new_index]=map[i];
                new_map[new_index]->next=temp;
                map[i]=temp2;
            }
            delete map[i];
        }
        delete[] map;
        map=new_map;
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
void HashMap<KEY,T,thash>::delete_hash_table (LN**& ht, int bins) {
    for(int i=0;i<bins;++i)
    {
        while(ht[i])
        {
            auto temp=ht[i]->next;
            delete ht[i];
            ht[i]=temp;
        }
    }
    delete[] ht;
    ht=nullptr;
}






////////////////////////////////////////////////////////////////////////////////
//
//Iterator class definitions

template<class KEY,class T, int (*thash)(const KEY& a)>
void HashMap<KEY,T,thash>::Iterator::advance_cursors(){
    if(current.first!=-1 && current.second->next && current.second->next->next)
        current=ics::make_pair(current.first,current.second->next);
    else
    {
        for(int i=current.first+1;i<ref_map->bins;++i)
            if(ref_map->map[i]->next)
            {
                current=ics::make_pair(i,ref_map->map[i]);
                return;
            }
        current=ics::make_pair(-1,(LN*)nullptr);
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::Iterator::Iterator(HashMap<KEY,T,thash>* iterate_over, bool from_begin)
: ref_map(iterate_over), expected_mod_count(ref_map->mod_count) {
    current = ics::make_pair(-1,(LN*)nullptr);
    if(from_begin)
        advance_cursors();
    expected_mod_count=ref_map->mod_count;

}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::Iterator::~Iterator()
{}


template<class KEY,class T, int (*thash)(const KEY& a)>
auto HashMap<KEY,T,thash>::Iterator::erase() -> Entry {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::erase");
    if (!can_erase)
        throw CannotEraseError("HashMap::Iterator::erase Iterator cursor already erased");
    if (current.first==-1)
        throw CannotEraseError("HashMap::Iterator::erase Iterator cursor beyond data structure");

    can_erase = false;
    Entry to_return = current.second->value;
    ref_map->erase(to_return.first);
    if(current.second->next==nullptr)
        advance_cursors();
    expected_mod_count = ref_map->mod_count;
    return to_return;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
std::string HashMap<KEY,T,thash>::Iterator::str() const {
    std::ostringstream answer;
    answer << ref_map->str() << "(expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
    return answer.str();
}

template<class KEY,class T, int (*thash)(const KEY& a)>
auto  HashMap<KEY,T,thash>::Iterator::operator ++ () -> HashMap<KEY,T,thash>::Iterator& {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator ++");

    if (current.first==-1)
        return *this;

    if (can_erase)
        advance_cursors();
    else
        can_erase = true;

    return *this;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
auto  HashMap<KEY,T,thash>::Iterator::operator ++ (int) -> HashMap<KEY,T,thash>::Iterator {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator ++(int)");

    if (current.first==-1)
        return *this;

    Iterator to_return(*this);
    if (can_erase)
        advance_cursors();
    else
        can_erase = true;

    return to_return;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::Iterator::operator == (const HashMap<KEY,T,thash>::Iterator& rhs) const {
    const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsASI == 0)
        throw IteratorTypeError("HashMap::Iterator::operator ==");
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator ==");
    if (ref_map != rhsASI->ref_map)
        throw ComparingDifferentIteratorsError("HashMap::Iterator::operator ==");

    return current.first==rhsASI->current.first && current.second == rhsASI->current.second;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::Iterator::operator != (const HashMap<KEY,T,thash>::Iterator& rhs) const {
    const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsASI == 0)
        throw IteratorTypeError("HashMap::Iterator::operator ==");
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator ==");
    if (ref_map != rhsASI->ref_map)
        throw ComparingDifferentIteratorsError("HashMap::Iterator::operator ==");

    return current.first!=rhsASI->current.first || current.second != rhsASI->current.second;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
pair<KEY,T>& HashMap<KEY,T,thash>::Iterator::operator *() const {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator *");
    if (!can_erase || current.first==-1) {
        std::ostringstream where;
        where <<" when size = " << ref_map->size();
        throw IteratorPositionIllegal("HashMap::Iterator::operator * Iterator illegal: "+where.str());
    }

    return current.second->value;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
pair<KEY,T>* HashMap<KEY,T,thash>::Iterator::operator ->() const {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator *");
    if (!can_erase || current.first==-1) {
        std::ostringstream where;
        where <<" when size = " << ref_map->size();
        throw IteratorPositionIllegal("HashMap::Iterator::operator * Iterator illegal: "+where.str());
    }

    return &(current.second->value);
}


}

#endif /* HASH_MAP_HPP_ */
