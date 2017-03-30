#include <string>
#include <iostream>
#include <fstream>
#include "ics46goody.hpp"
#include "ics_exceptions.hpp"
#include "hash_equivalence.hpp"

int hash_int(const std::string& a){std::hash<std::string> t;return t(a);}
ics::HashEquivalence<std::string,hash_int> e;

int main() {
  std::cout << "Enter a sequence of singletons first; then other operations are allowed." << std::endl;
  for (;;) try {

    std::string x = ics::prompt_string("  Enter value for singleton (or quit)");
    if (x == "quit")
      break;
    if (x != "")
      e.add_singleton(x);
  } catch (ics::IcsError& e) {
    std::cout << "  " << e.what() << std::endl;
  }


  for (;;) try {
    std::cout << std::endl << std::endl << e << std::endl;
    std::cout << "Accessors             Mutators             General"                      << std::endl;
    std::cout << "  i  - in same class    a - add singleton    p - print equivalence_info" << std::endl;
    std::cout << "  1  - size             m - merge classes    q - quit"                   << std::endl;
    std::cout << "  2  - class count"                                                      << std::endl;
    std::cout << "  c  - classes"                                                          << std::endl;
    std::cout << "  s  - str"                                                              << std::endl;

    std::string allowable[] = {"i","1","2","c","s","a","m","p","q",""};
    std::cout << std::endl;
    std::string op = ics::prompt_string("Enter equivalence operation","",allowable);

    if (op == "i") {
      std::string x = ics::prompt_string("  Enter a value in an equivalence class");
      std::string y = ics::prompt_string("  Enter a value in an equivalence class");
      std::cout << "  " << x << " and " << y << " in_same_class() = " << e.in_same_class(x, y) << std::endl;
    }else if (op == "1") {
      std::cout << "  size() = " << e.size() << std::endl;
    }else if (op == "2") {
      std::cout << "  class_count() = " << e.class_count() << std::endl;
    }else if (op == "c") {
      std::cout << "  classes() = " << e.classes() << std::endl;
    }else if (op == "s") {
      std::cout << "  str() = " << e.str() << std::endl;
    }else if (op == "a") {
      std::string x = ics::prompt_string("  Enter value for a new singleton");
      e.add_singleton(x);
      std::cout << "  added singleton " << x << std::endl;
    }else if (op == "m") {
      std::string x = ics::prompt_string("  Enter a value in an equivalence class");
      std::string y = ics::prompt_string("  Enter a value in an equivalence class");
      e.merge_classes_of(x,y);
      std::cout << "  merged classes of " << x << " and " << y << std::endl;
    }else  if (op == "p") {
       std::cout << e.equivalence_info();
    }else if (op == "q")
       break;

  } catch (ics::IcsError& e) {
    std::cout << "  " << e.what() << std::endl;
  }
}

