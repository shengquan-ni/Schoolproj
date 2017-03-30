//Shengquan Ni 46564157
#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include <string>
#include <iostream>
#include <fstream>


template<class T>
class LN {
  public:
    LN ()                        : next(nullptr){}
    LN (const LN<T>& ln)         : value(ln.value), next(ln.next){}
    LN (T v, LN<T>* n = nullptr) : value(v), next(n){}
    T      value;
    LN<T>* next;
};


//Simple way to print linked lists
template<class T>
std::ostream& operator << (std::ostream& outs, LN<T>* l) {
  for (LN<T>* p = l; p!=nullptr; p=p->next)
    std::cout << p->value << "->";
  std::cout << "nullptr";
  return outs;
}



char relation (const std::string& s1, const std::string& s2) {
    return (s1.empty() && s2.empty())?'=':(s1.empty()?'<':(s2.empty()?'>':(s1[0]==s2[0]?relation(s1.substr(1),s2.substr(1)):(s1[0]>s2[0]?'>':'<'))));
}


template<class T>
void remove_all_i (LN<T>*& l, T value) {
    LN<T>* pre=nullptr;
    LN<T>* cl=l;
    while(cl)
    {
        auto temp=cl;
        cl=cl->next;
        if(temp->value==value)
        {
            delete temp;
            if(pre)pre->next=cl;
            else l=cl;
        }
        else
            pre=temp;
    }
}


template<class T>
void remove_all_r (LN<T>*& l, T value) {
    if(l)
    {
        if(l->value==value)
        {
            auto temp=l;
            l=l->next;
            delete temp;
            remove_all_r(l,value);
        }
        else
            remove_all_r(l->next,value);
    }

}



#endif /* SOLUTION_HPP_ */
