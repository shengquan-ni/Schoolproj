#ifndef Q6SOLUTION_HPP_
#define Q6SOLUTION_HPP_


#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <algorithm>                 // std::swap
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "q6utility.hpp"


////////////////////////////////////////////////////////////////////////////////

//Problem 1

//Write this function
template<class T>
void selection_sort(LN<T>* l){
    for(auto t=l;t;t=t->next)
    {
        auto min=t;
        for(auto t2=t->next;t2;t2=t2->next)
            if(t2->value<min->value)
                min=t2;
        auto temp=min->value;
        min->value=t->value;
        t->value=temp;
    }
}


////////////////////////////////////////////////////////////////////////////////

//Problem 2

//Write this function
template<class T>
void merge(T a[], int left_low,  int left_high,
           int right_low, int right_high) {
    auto size=left_high-left_low+right_high-right_low+2;
    auto start=left_low;
    auto temp_array=new T[size];
    for(auto i=0;i<size;++i)
    {
        if(left_low>left_high)
            temp_array[i]=a[right_low++];
        else if(right_low>right_high)
            temp_array[i]=a[left_low++];
        else
            temp_array[i]=a[left_low]>a[right_low]?a[right_low++]:a[left_low++];
    }
    for(auto i=0;i<size;++i)
        a[start+i]=temp_array[i];
    delete[] temp_array;
}


////////////////////////////////////////////////////////////////////////////////

//Problem 3

int select_digit (int number, int place)
{return number/place % 10;}


//Write this function
void radix_sort(int a[], int length) {
    ics::ArrayQueue<int> buckets[10];
    for(auto p=1;p<=100000;p*=10)
    {
        for(auto i=0;i<length;++i)
            buckets[select_digit(a[i],p)].enqueue(a[i]);
        int now=0;
        for(auto i=0;i<10;++i)
            while(!buckets[i].empty())
                a[now++]=buckets[i].dequeue();
    }
}


////////////////////////////////////////////////////////////////////////////////

//Problem 4

//Modify this function

template<class T>
int selection_sort(T a[], int length) {
    int count=0;
  for (int index_to_update=0; index_to_update<length; ++index_to_update) {
    int index_of_min = index_to_update;
    for (int i = index_to_update+1; i<length; ++i)
      if ( a[i] < a[index_of_min] )
        index_of_min = i;
    std::swap(a[index_to_update], a[index_of_min]);
      if(index_of_min!=index_to_update)++count;
  }
  return count; //allows to compile
}


//Write this function

//Test how often in selection_sort the index_to_update and index_of_min are.
//  different when swapping.
//Test is on an array of the the values 0..length-1, randomly shuffled num_tests times
//Returns the average number of different indexes.
double test_swapping(int length, int num_tests) {
    int array[length];
    double total=0;
    for(int i=0;i<length;++i)
        array[i]=i;
    for(int i=0;i<num_tests;++i)
    {
        shuffle(array,length);
        total+=selection_sort(array,length);
    }
    return total/(length*num_tests); //allows to compile
}

#endif /* Q6SOLUTION_HPP_ */
