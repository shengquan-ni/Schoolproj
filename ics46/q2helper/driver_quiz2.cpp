//#include <string>
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <algorithm>    // std::random_shuffle
//#include "q2solution.hpp"
//
//void test_relation(const std::string& s1, const std::string& s2) {
//  std::cout << "  \"" + s1 + "\" " <<  relation(s1,s2) << " \"" + s2 + "\"" << std::endl;
//}
//
//template<class T>
//LN<T>* build_linked_list_fast(T values[], int length) {  //O(N)
//  if (length == 0)
//    return nullptr;
//
//  LN<T>* front      = new LN<T>(values[0]);
//  LN<T>* rear_cache = front;
//  for (int i=1; i<length; ++i)
//    rear_cache = rear_cache->next = new LN<T>(values[i]);
//
//  return front;
//}
//
//
//int main() {
//  try{
//    //Testing relation
//    std::cout << "Testing relation" << std::endl;
//    test_relation("","");
//    test_relation("a","");
//    test_relation("","a");
//    test_relation("ant","ant");
//    test_relation("ant","anteater");
//    test_relation("anteater","ant");
//    test_relation("x","ant");
//
//
//    //Testing remove_all_i
//    std::cout << "\nTesting remove_all_i" << std::endl;
//
//    LN<int>* test = build_linked_list_fast(new int[3]{7,8,9},3);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_i(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//    test = build_linked_list_fast(new int[3]{5,6,7},3);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_i(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//    test = build_linked_list_fast(new int[3]{8,7,6},3);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_i(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//    test = build_linked_list_fast(new int[6]{7,5,7,7,2,7},6);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_i(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//    test = build_linked_list_fast(new int[8]{7,7,5,7,7,2,7,7},8);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_i(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//
//    std::cout << "\nTesting remove_all_r" << std::endl;
//
//    test = build_linked_list_fast(new int[3]{7,8,9},3);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_r(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//    test = build_linked_list_fast(new int[3]{5,6,7},3);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_r(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//    test = build_linked_list_fast(new int[3]{8,7,6},3);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_r(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//    test = build_linked_list_fast(new int[6]{7,5,7,7,2,7},6);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_r(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//    test = build_linked_list_fast(new int[8]{7,7,5,7,7,2,7,7},8);
//    std::cout << "Before removal: " << test << std::endl;
//    remove_all_r(test,7);
//    std::cout << "After removal (of 7): " << test << std::endl;
//
//
//  } catch (const std::exception& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
//
//
//
///*
//Here is the output that the driver should produce (although Tests 2-3 are random:
//Testing relation
//  "" = ""
//  "a" > ""
//  "" < "a"
//  "ant" = "ant"
//  "ant" < "anteater"
//  "anteater" > "ant"
//  "x" > "ant"
//
//Testing remove_all_i
//Before removal: 7->8->9->nullptr
//After removal (of 7): 8->9->nullptr
//Before removal: 5->6->7->nullptr
//After removal (of 7): 5->6->nullptr
//Before removal: 8->7->6->nullptr
//After removal (of 7): 8->6->nullptr
//Before removal: 7->5->7->7->2->7->nullptr
//After removal (of 7): 5->2->nullptr
//Before removal: 7->7->5->7->7->2->7->7->nullptr
//After removal (of 7): 5->2->nullptr
//
//Testing remove_all_r
//Before removal: 7->8->9->nullptr
//After removal (of 7): 8->9->nullptr
//Before removal: 5->6->7->nullptr
//After removal (of 7): 5->6->nullptr
//Before removal: 8->7->6->nullptr
//After removal (of 7): 8->6->nullptr
//Before removal: 7->5->7->7->2->7->nullptr
//After removal (of 7): 5->2->nullptr
//Before removal: 7->7->5->7->7->2->7->7->nullptr
//After removal (of 7): 5->2->nullptr
//
//*/
