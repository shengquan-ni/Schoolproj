#include <vector>
#include <algorithm>                 // std::random_shuffle
#include <random>


//Tuype declaration for LN<T>
template<class T>
class LN {
  public:
    LN ()
      : value(), next()
    {}

    LN (const LN<T>& l)
      : value(l.value), next(l.next)
    {}

    LN (T value, LN* n = nullptr)
      : value(value), next(n)
    {}

  T   value;
  LN* next;
};


//Print a linked list/array nicely, prefaced by label,
//  optionally printing whether or not it is sorted
template<class T>
void print (std::string label, LN<T>* l, bool report_sorted) {
  bool sorted = true;
  std::cout << label;
  for (LN<T>* c=l; c!=nullptr; c=c->next) {
    std::cout << c->value;
    if (c->next == nullptr)
      std::cout << std::endl;
    else {
      std::cout << ", ";
      if (c->value > c->next->value)
        sorted = false;
    }
  }
  if (report_sorted)
    std::cout << (sorted ? "    Sorted" : "    Not Sorted") << std::endl;
}


template<class T>
void print (std::string label, T a[], int length, bool report_sorted) {
  bool sorted = true;
  std::cout << label;
  for (int i=0; i<length; ++i) {
    std::cout << a[i];
    if (i == length-1)
      std::cout << std::endl;
    else {
      std::cout << ", ";
      if (a[i] > a[i+1])
        sorted = false;
    }
  }
  if (report_sorted)
    std::cout << (sorted ? "    Sorted" : "    Not Sorted") << std::endl;
}


//Build a list from an array (keeping the same order)
template<class T>
LN<T>* build (T a[], int length, int i) {
  if (i >= length)
    return nullptr;
  else
    return new LN<T>(a[i],build(a,length,i+1));
}


//Randomize positions of values in an array
template<class T>
void shuffle(T values[], int length) {
  std::vector<T> v_values;
  for (int i=0; i<length; ++i)
    v_values.push_back(values[i]);
  std::random_shuffle(v_values.begin(),v_values.end());
  for (int i=0; i<length; ++i)
    values[i] = v_values[i];
}