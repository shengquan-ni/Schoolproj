//Shengquan Ni 46564157
#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include "ics46goody.hpp"
#include "ics_exceptions.hpp"
#include "array_queue.hpp"
#include "array_priority_queue.hpp"
#include "array_map.hpp"


//Helper Functions (you decide what is useful)
//Hint: I used helpers for only sort_descendants and sort_generations


//Problem #1a and #1b
template<class KEY,class T>
void swap (ics::ArrayMap<KEY,T>& m, KEY key1, KEY key2) {
   m[key2] = m.put(key1,m[key2]);
}


template<class KEY,class T>
void values_set_to_queue (const ics::ArrayMap<KEY,ics::ArraySet<T>>& m1,
                          ics::ArrayMap<KEY,ics::ArrayQueue<T>>&     m2) {
    for(auto i:m1)
        m2[i.first].enqueue_all(i.second);
}


//Problem #2a and #2b
ics::ArrayQueue<std::string> sort_descendants (const ics::ArrayMap<std::string,ics::ArrayQueue<int>>& m) {
    typedef ics::ArrayMap<std::string,ics::ArrayQueue<int>>::Entry E;
    ics::ArrayPriorityQueue<E> apq(m,[](const E& t1,const E& t2)
    {
        auto sum=[](const ics::ArrayQueue<int>& q){int count=0;for(auto i:q)count+=i;return count;};
        return sum(t1.second)==sum(t2.second)?t1.first<t2.first:sum(t1.second)<sum(t2.second);
    });
    ics::ArrayQueue<std::string> result;
    for(auto i:apq)result.enqueue(i.first);
    return result;
}


ics::ArrayQueue<ics::pair<std::string,ics::ArrayQueue<int>>> sort_generations (const ics::ArrayMap<std::string,ics::ArrayQueue<int>>& m) {
    typedef ics::ArrayMap<std::string,ics::ArrayQueue<int>>::Entry E;
    ics::ArrayPriorityQueue<E> apq(m,[](const E& t1,const E& t2)
    {
        auto sum=[](const ics::ArrayQueue<int>& q){int count=0;for(auto i:q)count+=i;return count;};
        return t1.second.size()==t2.second.size()?(sum(t1.second)==sum(t2.second)?t1.first<t2.first:sum(t1.second)>sum(t2.second)):t1.second.size()>t2.second.size();
    });
    return ics::ArrayQueue<ics::pair<std::string,ics::ArrayQueue<int>>>(apq);
}


//Problem #3a and #3b
ics::ArraySet<std::string> big_family(const ics::ArrayMap<std::string,ics::ArrayQueue<int>>& m) {
    auto sum=[](const ics::ArrayQueue<int>& q){int count=0;for(auto i:q)count+=i;return count;};
    ics::ArraySet<std::string> result;
    for(auto i:m)if(sum(i.second)>=10)result.insert(i.first);
    return result;
}


ics::ArrayMap<std::string,ics::ArraySet<char>> big_word_map(const std::string sentence) {
    ics::ArrayMap<std::string,ics::ArraySet<char>> result;
    for(auto i:ics::split(sentence," "))if(i.size()>3)result[i].insert_all(i);
    return result;
}


//Problem #4
ics::ArrayMap<char,ics::ArraySet<char>> near(const std::string word, int dist) {
    ics::ArrayMap<char,ics::ArraySet<char>> result;
    int size=word.size();
    for(int i=0;i<size;++i)
        for(int j=std::max<int>(0,i-dist);j<=std::min<int>(i+dist,size-1);++j)
            result[word[i]].insert(word[j]);
    return result;
}


//Problem #5
ics::ArrayMap<std::string,ics::ArrayMap<std::string,int>> alt_map(const  ics::ArrayMap<ics::pair<std::string,std::string>,int>calls) {
    ics::ArrayMap<std::string,ics::ArrayMap<std::string,int>> result;
    for(auto i:calls)
        result[i.first.first][i.first.second]=i.second;
    return result;
}


#endif /* SOLUTION_HPP_ */
