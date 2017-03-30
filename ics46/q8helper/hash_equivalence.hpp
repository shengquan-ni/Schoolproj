#ifndef HASH_EQUIVALENCE_HPP_
#define HASH_EQUIVALENCE_HPP_

#include <sstream>
#include "ics_exceptions.hpp"
#include "hash_map.hpp"
#include "hash_set.hpp"


namespace ics {


//HashEquivalence must be instantiated with a legal thash function (there is no default)
//  The classes() method must use a hash that in instantiated in the template
template<class T, int (*thash) (const T& a)> class HashEquivalence {
  public:
    //Destructor/Constructors
    ~HashEquivalence ();

    HashEquivalence          (double the_load_threshold = 1.0);
    HashEquivalence          (const HashEquivalence<T,thash>& to_copy, double the_load_threshold = 1.0);
    explicit HashEquivalence (const std::initializer_list<T>& il, double the_load_threshold = 1.0);

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    explicit HashEquivalence (const Iterable& i, double the_load_threshold = 1.0);


    //Queries
    bool                in_same_class (const T& a, const T& b); // Not const because compression
    int                 size          () const;                 // number of values in all Equivalences
    int                 class_count   () const;                 // number of Equivalences
    HashSet<HashSet<T,thash>> classes ();                       // Not const because compression used
    std::string str                   () const; //supplies useful debugging information; contrast to operator <<


    //Commands
    void add_singleton    (const T& a);
    void merge_classes_of (const T& a, const T& b);


    //Operators
    template<class T2, int (*thash2) (const T2& a)>
    friend std::ostream& operator << (std::ostream& outs, const HashEquivalence<T2,thash2>& e);


    //Miscellaneous methods (useful for testing/debugging)
    int max_height               () const;
    HashMap<T,int> heights       () const;
    std::string equivalence_info () const;

  private:
    HashMap<T,T>   parent;
    HashMap<T,int> root_size;
	HashMap<int,int> histogram;
	int max_size=0;
	int total_num=0;
	double avg_size=0.0;
	int total_size=0;
    //Helper methods
    T compress_to_root (T a);
};





////////////////////////////////////////////////////////////////////////////////
//
//HashMap class and related definitions

//Destructor/Constructor

template<class T, int (*thash) (const T& a)>
HashEquivalence<T,thash>::~HashEquivalence ()
{}


template<class T, int (*thash) (const T& a)>
HashEquivalence<T,thash>::HashEquivalence(double the_load_threshold)
: parent(the_load_threshold,thash), root_size(the_load_threshold,thash),histogram(the_load_threshold,thash) {
}


template<class T, int (*thash) (const T& a)>
HashEquivalence<T,thash>::HashEquivalence (const HashEquivalence<T,thash>& to_copy, double the_load_threshold)
: parent(to_copy.parent,the_load_threshold,thash), root_size(to_copy.root_size,the_load_threshold,thash),histogram(the_load_threshold,thash) {
}


template<class T, int (*thash) (const T& a)>
HashEquivalence<T,thash>::HashEquivalence (const std::initializer_list<T>& il, double the_load_threshold)
: parent(the_load_threshold,thash), root_size(the_load_threshold,thash),histogram(the_load_threshold,thash) {
  for (const T& v : il)
    add_singleton(v);
}


template<class T, int (*thash) (const T& a)>
template <class Iterable>
HashEquivalence<T,thash>::HashEquivalence (const Iterable& i, double the_load_threshold)
:  parent(the_load_threshold,thash), root_size(the_load_threshold,thash),histogram(the_load_threshold,thash) {
  for (const T& v : i)
    add_singleton(v);
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

//Two values are in the same class if their equivalence trees have the same roots.
//In the process of finding the roots and comparing them, compress all the values
//  on the path to the root: make the parents of a and all its ancestors (not
//  descendants) directly refer to the root of a's equivalence class (same for b).
//Throw an EquivalenceError (with a descriptive message) if the parameter a or b
//  is not already a value in the Equivalence (were never added as singletons).
template<class T, int (*thash) (const T& a)>
bool HashEquivalence<T,thash>::in_same_class (const T& a, const T& b) {
  if (!parent.has_key(a)) {
    std::ostringstream exc;
    exc << "HashEquivalence.in_same_class: a(" << a << ") not in an equivalence class";
    throw EquivalenceError(exc.str());
  }
  if (!parent.has_key(b)) {
    std::ostringstream exc;
    exc << "HashEquivalence.in_same_class: b(" << b << ") not in an equivalence class";
    throw EquivalenceError(exc.str());
  }

  return compress_to_root(a) == compress_to_root(b);
}


//The number of values in all Equivalences; if a,b,c are equivalent, and
//  d,e are equivalent, size returns 5.
template<class T, int (*thash) (const T& a)>
int HashEquivalence<T,thash>::size () const{
  return parent.size();
}


//The number of different equivalent classes; if a,b,c are equivalent, and
//  d,e are equivalent, class_count returns 2.
template<class T, int (*thash) (const T& a)>
int HashEquivalence<T,thash>::class_count () const{
  return root_size.size();
}


//For every value in the Equivalence, compress it to its root and
//  insert it into the set associated with the root
//Then, insert into a Set all the sets collected previously in the map
//Use thash to write a lambda for hashing Set<T>, which is used in the
//  constructor for the returned HashSet<HashSet<T,thash>>.
template<class T, int (*thash) (const T& a)>
HashSet<HashSet<T,thash>> HashEquivalence<T,thash>::classes () {
  HashMap<T,HashSet<T,thash>> answer_map(1,thash);

  for (pair<T,T> np : parent) {
    T root = compress_to_root(np.first);
    answer_map[root].insert(np.first);
  }

  HashSet<HashSet<T,thash>> answer(1,
      [](const HashSet<T,thash>& set) {
        int answer = 1;
        for (const T& v : set)
          answer *= thash(v);
        return answer;}
   );


  for (const pair<T,HashSet<T,thash>>& rs : answer_map)
    answer.insert(rs.second);

  return answer;
}


template<class T, int (*thash) (const T& a)>
std::string HashEquivalence<T,thash>::str () const {
  std::ostringstream answer;
  answer << "HashEquivalence [" << std::endl;
  answer << "  parent   : " << parent.str() << std::endl;
  answer << "  root_size: " << root_size.str() << "]" << std::endl;
  return answer.str();
}


////////////////////////////////////////////////////////////////////////////////
//
//Commands

//Add the singleton a to the Equivalence.
//Throw an EquivalenceError (with a descriptive message) if the parameter a
//  already a value in the Equivalence (was previously added as a singleton).
template<class T, int (*thash) (const T& a)>
void HashEquivalence<T,thash>::add_singleton (const T& a) {
  if (parent.has_key(a)) {
    std::ostringstream exc;
    exc << "HashEquivalence.add_singleton: a(" << a << ") already in an equivalence class";
    throw EquivalenceError(exc.str());
  }
  parent[a]    = a; //at the root of its own equivalence tree
  root_size[a] = 1; //its equivalence class has 1 value in it (itself)
}


//Compress a and b to their roots.
//If they are in different equivalence classes, make the parent of the
//  root of the smaller-sized equivalence class refer to the root of the larger-
//  sized equivalence class; update the size of the root of the larger equivalence
//  class and remove the root of the smaller equivalence class from the root_size
//Throw an EquivalenceError (with a descriptive message) if the parameter a or b
//  is not already a value in the Equivalence (were never added as singletons)
template<class T, int (*thash) (const T& a)>
void HashEquivalence<T,thash>::merge_classes_of (const T& a, const T& b) {
  if (!parent.has_key(a)) {
    std::ostringstream exc;
    exc << "HashEquivalence.merge_classes_of: a(" << a << ") not in an equivalence class";
    throw EquivalenceError(exc.str());
  }
  if (!parent.has_key(b)) {
    std::ostringstream exc;
    exc << "HashEquivalence.merge_classes_of: b(" << b << ") not in an equivalence class";
    throw EquivalenceError(exc.str());
  }

  T a_root = compress_to_root(a);
  T b_root = compress_to_root(b);
  if (a_root == b_root)
    return;   //Already in same equivalence class! Don't execute code below

  if (root_size[a_root] < root_size[b_root]) {
    parent[a_root]    = b_root;
    root_size[b_root] = root_size[a_root]+root_size[b_root];
    root_size.erase(a_root);
  }else{
    parent[b_root]    = a_root;
    root_size[a_root] = root_size[a_root]+root_size[b_root];
    root_size.erase(b_root);
  }
}



////////////////////////////////////////////////////////////////////////////////
//
//Operators

template<class T, int (*thash) (const T& a)>
std::ostream& operator << (std::ostream& outs, const HashEquivalence<T,thash>& e) {
  outs << "HashEquivalence [" << std::endl;
  outs << "  parent map   : " << e.parent << std::endl;
  outs << "  root_size map: " << e.root_size << "]" << std::endl;
  return outs;
}


////////////////////////////////////////////////////////////////////////////////
//
//Helper methods

//Call compress_to_root as a helper method in_same_class and merge_classes_of.
//When finished, a and all its ancestors (but not descendants) should refer
//  (in the parent map) directly to the root of a's equivalence class.
//Throw an EquivalenceError (with a descriptive message) if the parameter a
//  is not already a value in the Equivalence (was never added as a singleton).
template<class T, int (*thash) (const T& a)>
T HashEquivalence<T,thash>::compress_to_root (T a) {
  if (!parent.has_key(a)) {
    std::ostringstream exc;
    exc << "HashEquivalence.compress_to_root: a("<<a<<") not in an equivalence class";
    throw EquivalenceError(exc.str());
  }

  HashSet<T> compress_set(1,thash);
  T to_root;
  while ( (to_root=parent[a]) != a) {
    compress_set.insert(a);
    a = to_root;
  }
  for (const T& x : compress_set) {
    parent[x] = to_root;
  }
	int t=compress_set.size();
	if(t>max_size)
		max_size=t;
	histogram[t]+=1;
	total_num+=1;
	total_size+=t;
	avg_size=(double)total_size/total_num;
		
  compress_set.clear();
  return to_root;
}


////////////////////////////////////////////////////////////////////////////////
//
//Miscellaneous methods (useful for testing/debugging)

//Compute all root heights (see method below), then locate/return the largest
template<class T, int (*thash) (const T& a)>
int HashEquivalence<T,thash>::max_height () const{
  int mh = 0;
  for (const pair<T,int>& h : heights())
    if (h.second > mh)
      mh = h.second;
  return mh;
}


//Compute/Return a map of all root heights.
//Don't compress any nodes here
template<class T, int (*thash) (const T& a)>
HashMap<T,int> HashEquivalence<T,thash>::heights () const {
  //Compute the depth of every node by tracing a path to its root;
  //  update the answer/height of the root if it is larger
  HashMap<T,int> answer(1,thash);
  for (const pair<T,T>& np : parent) {
    T e = np.first;
    int depth = 0;
    while (parent[e] != e) {
      e = parent[e];
      depth++;
    }
    if ( answer[e] < depth)
      answer[e] = depth;
  }

  return answer;
}


//Return string containing the parent, root_size, and height maps amd the maximum
//  height of any equivalence tree
template<class T, int (*thash) (const T& a)>
std::string HashEquivalence<T,thash>::equivalence_info () const {
  std::ostringstream answer;
  answer << "  max size     : " << max_size       << std::endl;
  answer << "  histogram    : " << std::endl;
	for(int i=0;i<=max_size;++i)
		answer<<i<<":"<<histogram[i]<<"          "<<(double)histogram[i]/total_num<<std::endl;
  answer << "  total num    : " << total_num    << std::endl;
  answer << "  avg size     : " << avg_size << std::endl;

  return answer.str();
}


}

#endif /* HASH_EQUIVALENCE_HPP_ */
