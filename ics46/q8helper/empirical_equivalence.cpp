#include <string>
#include <iostream>
#include <fstream>
#include "ics46goody.hpp"
#include "ics_exceptions.hpp"
#include <string>                    // std::hash<std::string>
#include <random>
#include <time.h>                    //For randomizing seed
#include "hash_equivalence.hpp"

int hash_int (const int& s) {std::hash<int> str_hash; return str_hash(s);}
typedef ics::HashEquivalence<int,hash_int> TestEquivalence;

int main() {
    int N            = 200000;//ics::prompt_int("Enter N for test (creates N singletons)");
    int test_times   = 1;//ics::prompt_int("Enter number of times to test (averaged): 5 is good");
    int merge_factor = 1;//ics::prompt_int("Enter factor (for N) for merges: 5 is good");

    std::default_random_engine generator;
    //generator.seed(time(nullptr));  //Uncomment to randomize
    std::uniform_int_distribution<int> distribution(0,N-1);   //0 - 999,999: up to 6 digits
    try {
      for (int count=1; count<=test_times; ++count) {
         std::cout << "Test: " << count << " of " << test_times << std::endl;
         TestEquivalence e;
         for (int i=0; i<N; ++i)
           e.add_singleton(i);

         //while (e.class_count() != 1) {  //KLUDGE Alternative loop: until 1 class
         for (int i=0; i<merge_factor*N; ++i) {
           int m1 = distribution(generator);
           int m2 = distribution(generator);
           //std::cout << e.classes() << " merging: " << m1 << "/" << m2 << std::endl;
           if (!e.in_same_class(m1, m2))
             e.merge_classes_of(m1, m2);
         }
         std::cout << e.equivalence_info() << std::endl;
       }

    } catch (ics::IcsError& e) {
      std::cout << "  " << e.what() << std::endl;
    }
}
