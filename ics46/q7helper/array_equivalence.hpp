#ifndef ARRAY_EQUIVALENCE_HPP_
#define ARRAY_EQUIVALENCE_HPP_

#include <sstream>
#include "ics_exceptions.hpp"
#include "array_map.hpp"
#include "array_set.hpp"


namespace ics {


template<class T> class ArrayEquivalence {
  public:
	//Destructor/Constructors
	~ArrayEquivalence ();

	ArrayEquivalence          ();
	ArrayEquivalence          (const ArrayEquivalence<T>& to_copy);
	explicit ArrayEquivalence (const std::initializer_list<T>& il);

	//Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
	template <class Iterable>
	explicit ArrayEquivalence (const Iterable& i);


	//Queries
	bool                in_same_class (const T& a, const T& b); // Not const because compression
	int                 size          () const;                 // number of values in all Equivalences
	int                 class_count   () const;                 // number of Equivalences
	ArraySet<ArraySet<T>> classes     ();                       // Not const because compression used
	std::string str                   () const; //supplies useful debugging information; contrast to operator <<


	//Commands
	void add_singleton    (const T& a);
	void merge_classes_of (const T& a, const T& b);


	//Operators
	template<class T2>
	friend std::ostream& operator << (std::ostream& outs, const ArrayEquivalence<T2>& e);


	//Miscellaneous methods (useful for testing/debugging)
	int max_height               () const;
	ArrayMap<T,int> heights       () const;
	std::string equivalence_info () const;

  private:
	ArrayMap<T,T>   parent;
	ArrayMap<T,int> root_size;

	//Helper methods
	T compress_to_root (T a);
};





////////////////////////////////////////////////////////////////////////////////
//
//ArrayMap class and related definitions

//Destructor/Constructor

template<class T>
ArrayEquivalence<T>::~ArrayEquivalence ()
{}


template<class T>
ArrayEquivalence<T>::ArrayEquivalence()
{}


template<class T>
ArrayEquivalence<T>::ArrayEquivalence (const ArrayEquivalence<T>& to_copy)
: parent(to_copy.parent), root_size(to_copy.root_size) {
}


template<class T>
ArrayEquivalence<T>::ArrayEquivalence (const std::initializer_list<T>& il) {
  for (const T& v : il)
	add_singleton(v);
}


template<class T>
template <class Iterable>
ArrayEquivalence<T>::ArrayEquivalence (const Iterable& i) {
  for (const T& v : i)
	add_singleton(v);
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

//Two values are in the same class if their equivalence trees have the same root.
//In the process of finding the roots and comparing them, compress all the values
//  on the path to the root: make the parents of a and all its ancestors (not
//  descendants) directly refer to the root of a's equivalence class (same for b).
//Throw an EquivalenceError (with a descriptive message) if the parameter a or b
//  is not already a value in the Equivalence (were never added as singletons).
template<class T>
bool ArrayEquivalence<T>::in_same_class (const T& a, const T& b) {
	return compress_to_root(a)==compress_to_root(b);
}


//The number of values in all Equivalences; if a,b,c are equivalent, and
//  d,e are equivalent, size returns 5.
template<class T>
int ArrayEquivalence<T>::size () const{
  return parent.size();
}


//The number of different equivalent classes; if a,b,c are equivalent, and
//  d,e are equivalent, class_count returns 2.
template<class T>
int ArrayEquivalence<T>::class_count () const {
  return root_size.size();
}


//For every value in the Equivalence, compress it to its root and
//  insert it into the set associated with the root in a local map
//Then, insert into a Set all the sets collected previously in the map
template<class T>
ArraySet<ArraySet<T>> ArrayEquivalence<T>::classes () {
    ArraySet<ArraySet<T>> res;
    ArrayMap<T,ArraySet<T>> temp;
    for(auto i:parent)
    {
        auto root=compress_to_root(i.first);
        temp[root].insert(i.first);
    }
    for(auto i:temp)
    {
        res.insert(i.second);
    }
    return res;
}


template<class T>
std::string ArrayEquivalence<T>::str () const {
  std::ostringstream answer;
  answer << "ArrayEquivalence [" << std::endl;
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
template<class T>
void ArrayEquivalence<T>::add_singleton (const T& a) {
	if(parent.has_key(a))
		throw EquivalenceError("The parameter is already a value in the Equivalence.");
	else
    {
        parent.put(a,a);
        root_size[a]=1;
    }
}


//First, compress a and b to their roots.
//If they are in different equivalence classes, make the parent of the
//  root of the smaller-sized equivalence class refer to the root of the larger-
//  sized equivalence class; update the size of the root of the larger equivalence
//  class and remove the root of the smaller equivalence class from the root_size
//Throw an EquivalenceError (with a descriptive message) if the parameter a or b
//  is not already a value in the Equivalence (were never added as singletons)
template<class T>
void ArrayEquivalence<T>::merge_classes_of (const T& a, const T& b) {
  if(!parent.has_key(a) || !parent.has_key(b))
	  throw  EquivalenceError("At least one of the parameter is not a value in the Equivalence.");
  else
  {
	  auto t1=compress_to_root(a);
	  auto t2=compress_to_root(b);
      if(t1==t2)return;
	  if(root_size[t1]<root_size[t2])
	  {
		  root_size[t2]+=root_size[t1];
		  root_size.erase(t1);
		  parent[t1]=t2;
	  }
	  else
	  {
		  root_size[t1]+=root_size[t2];
		  root_size.erase(t2);
		  parent[t2]=t1;
	  }
  }
}



////////////////////////////////////////////////////////////////////////////////
//
//Operators

template<class T>
std::ostream& operator << (std::ostream& outs, const ArrayEquivalence<T>& e) {
  outs << "ArrayEquivalence [" << std::endl;
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
template<class T>
T ArrayEquivalence<T>::compress_to_root (T a) {
    if(!parent.has_key(a))
        throw EquivalenceError("The parameter is not already a value in the Equivalence.");
    else
    {
        auto root=a;
        while(parent[root]!=root)
            root=parent[root];
        while(parent[a]!=root)
        {
            auto temp=parent[a];
            parent[a]=root;
            a=temp;
        }
        return root;
    }

}


////////////////////////////////////////////////////////////////////////////////
//
//Miscellaneous methods (useful for testing/debugging)

//Compute all root heights (see method below), then locate/return the largest
template<class T>
int ArrayEquivalence<T>::max_height () const{
  int mh = 0;
  for (const pair<T,int>& h : heights())
	if (h.second > mh)
	  mh = h.second;
  return mh;
}


//Compute/Return a map of all root heights.
//Don't compress any nodes here
template<class T>
ArrayMap<T,int> ArrayEquivalence<T>::heights () const {
  //Compute the depth of every node by tracing a path to its root;
  //  update the answer/height of the root if it is larger
  ArrayMap<T,int> answer;
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
template<class T>
std::string ArrayEquivalence<T>::equivalence_info () const {
  std::ostringstream answer;

  answer << "  parent map   : " << parent       << std::endl;
  answer << "  root_size map: " << root_size    << std::endl;
  answer << "  heights map  : " << heights()    << std::endl;
  answer << "  max height   : " << max_height() << std::endl;

  return answer.str();
}


}

#endif /* ARRAY_EQUIVALENCE_HPP_ */
