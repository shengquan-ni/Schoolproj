#include "q4solution.hpp"
#include "ics46goody.hpp"

int main() {
  try {
    std::cout << std::endl << "Building Tree" << std::endl;

    int bt0_values[] = {};
    TPN<int>* bt0 = nullptr;
    build_bt(bt0, bt0_values, 0);
    std::cout << "bt0 rotated is" << std::endl;
    print_rotated(bt0,"",std::cout);
    std::cout << "is_bst returns " << is_bst(bt0) << std::endl << std::endl;

    int bt1_values[] = {4,4, 2,2, 5,5, 1,1, 3,3};
    TPN<int>* bt1 = nullptr;
    build_bt(bt1, bt1_values, 10);
    std::cout << "bt1 rotated is" << std::endl;
    print_rotated(bt1,"",std::cout);
    std::cout << "is_bst returns " << is_bst(bt1) << std::endl << std::endl;

    int bt2_values[] = {4,4, 2,2, 5,5, 6,3, 1,1};
    TPN<int>* bt2 = nullptr;
    build_bt(bt2, bt2_values, 10);
    std::cout << "bt2 rotated is" << std::endl;
    print_rotated(bt2,"",std::cout);
    std::cout << "is_bst returns " << is_bst(bt2) << std::endl << std::endl;

    int bt3_values[] = {8,8, 4,4, 2,2, 1,1, 3,3, 6,6, 5,5, 7,7, 12,12, 10,10, 9,9, 11,11, 14,14, 13,13, 15,15};
    TPN<int>* bt3 = nullptr;
    build_bt(bt3, bt3_values, 30);
    std::cout << "bt3 rotated is" << std::endl;
    print_rotated(bt3,"",std::cout);
    std::cout << "is_bst returns " << is_bst(bt3) << std::endl << std::endl;

    int bt4_values[] = {8,8, 4,4, 2,2, 1,1, 3,3, 6,6, 5,5, 16,7, 12,12, 10,10, 9,9, 11,11, 14,14, 13,13, 15,15};
    TPN<int>* bt4 = nullptr;
    build_bt(bt4, bt4_values, 30);
    std::cout << "bt4 rotated is" << std::endl;
    print_rotated(bt4,"",std::cout);
    std::cout << "is_bst returns " << is_bst(bt4) << std::endl << std::endl;


    int load1[]  = {1};
    int load1a[] = {2};
    int load2[]  = {2,3};
    int load4[]  = {4,5,6,7};

    TPN<int>* dlcl_0 = nullptr, *dlcl_1, *dlcl_1a, *dlcl_2, *dlcl_4, *dlcl;

    build_dlcl(dlcl_1, load1,1);
    build_dlcl(dlcl_2, load2,2);
    build_dlcl(dlcl_4, load4,4);

    std::cout << "Original lists" << std::endl;
    std::cout << "dlcl_0 = ";
    print_dlcl(dlcl_0,std::cout);

    std::cout << "dlcl_1 = ";
    print_dlcl(dlcl_1,std::cout);

    std::cout << "dlcl_2 = ";
    print_dlcl(dlcl_2,std::cout);

    std::cout << "dlcl_4 = ";
    print_dlcl(dlcl_4,std::cout);


    std::cout << std::endl << "Testing merge" << std::endl;

    std::cout << "merge(dlcl_0,dlcl_0) = ";
    dlcl = merge(dlcl_0,dlcl_0);
    print_dlcl(dlcl,std::cout);

    std::cout << "merge(dlcl_0,dlcl_1) = ";
    dlcl_0 = nullptr;
    build_dlcl(dlcl_1, load1,1);
    dlcl = merge(dlcl_0,dlcl_1);
    print_dlcl(dlcl,std::cout);

    std::cout << "merge(dlcl_1,dlcl_0) = ";
    dlcl_0 = nullptr;
    build_dlcl(dlcl_1, load1,1);
    dlcl = merge(dlcl_1,dlcl_0);
    print_dlcl(dlcl,std::cout);

    std::cout << "merge(dlcl_1,dlcl_1a) = ";
    build_dlcl(dlcl_1,  load1,1);
    build_dlcl(dlcl_1a, load1a,1);
    dlcl = merge(dlcl_1,dlcl_1a);
    print_dlcl(dlcl,std::cout);

    std::cout << "merge(dlcl_1,dlcl_2) = ";
    build_dlcl(dlcl_1, load1,1);
    build_dlcl(dlcl_2, load2,2);
    dlcl = merge(dlcl_1,dlcl_2);
    print_dlcl(dlcl,std::cout);

    std::cout << "merge(dlcl_2,dlcl_1) = ";
    build_dlcl(dlcl_1, load1,1);
    build_dlcl(dlcl_2, load2,2);
    dlcl = merge(dlcl_2,dlcl_1);
    print_dlcl(dlcl,std::cout);

    std::cout << "merge(dlcl_2,dlcl_4) = ";
    build_dlcl(dlcl_2, load2,2);
    build_dlcl(dlcl_4, load4,4);
    dlcl = merge(dlcl_2,dlcl_4);
    print_dlcl(dlcl,std::cout);

    std::cout << "merge(dlcl_4,dlcl_2) = ";
    build_dlcl(dlcl_2, load2,2);
    build_dlcl(dlcl_4, load4,4);
    dlcl = merge(dlcl_4,dlcl_2);
    print_dlcl(dlcl,std::cout);


    std::cout << std::endl << "Testing bt_to_dlcl" << std::endl;

    bt0 = nullptr;
    build_bt(bt0, bt0_values, 0);
    std::cout << "bt0 rotated is" << std::endl;
    print_rotated(bt0,"",std::cout);
    std::cout << "bt_to_dlcl(bt0) = ";
    print_dlcl(bt_to_dlcl(bt0),std::cout);
    std::cout << std::endl;

    bt1 = nullptr;
    build_bt(bt1, bt1_values, 10);
    std::cout << "bt1 rotated is" << std::endl;
    print_rotated(bt1,"",std::cout);
    std::cout << "bt_to_dlcl(bt1) = ";
    print_dlcl(bt_to_dlcl(bt1),std::cout);
    std::cout << std::endl;

    bt2 = nullptr;
    build_bt(bt2, bt2_values, 10);
    std::cout << "bt2 rotated is" << std::endl;
    print_rotated(bt2,"",std::cout);
    std::cout << "bt_to_dlcl(bt2) = ";
    print_dlcl(bt_to_dlcl(bt2),std::cout);
    std::cout << std::endl;

    bt3 = nullptr;
    build_bt(bt3, bt3_values, 30);
    std::cout << "bt3 rotated is" << std::endl;
    print_rotated(bt3,"",std::cout);
    std::cout << "bt_to_dlcl(bt3) = ";
    print_dlcl(bt_to_dlcl(bt3),std::cout);
    std::cout << std::endl;

    bt4 = nullptr;
    build_bt(bt4, bt4_values, 30);
    std::cout << "bt4 rotated is" << std::endl;
    print_rotated(bt4,"",std::cout);
    std::cout << "bt_to_dlcl(bt4) = ";
    print_dlcl(bt_to_dlcl(bt4),std::cout);
    std::cout << std::endl;

  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}

/* Driver should print the following
Building Tree
bt0 rotated is
is_bst returns 1

bt1 rotated is
..5
4
....3
..2
....1
is_bst returns 1

bt2 rotated is
..5
4
....6
..2
....1
is_bst returns 0

bt3 rotated is
......15
....14
......13
..12
......11
....10
......9
8
......7
....6
......5
..4
......3
....2
......1
is_bst returns 1

bt4 rotated is
......15
....14
......13
..12
......11
....10
......9
8
......16
....6
......5
..4
......3
....2
......1
is_bst returns 0

Original lists
dlcl_0 = empty
dlcl_1 = 1<->circular to first node
dlcl_2 = 2<->3<->circular to first node
dlcl_4 = 4<->5<->6<->7<->circular to first node

Testing merge
merge(dlcl_0,dlcl_0) = empty
merge(dlcl_0,dlcl_1) = 1<->circular to first node
merge(dlcl_1,dlcl_0) = 1<->circular to first node
merge(dlcl_1,dlcl_1a) = 1<->2<->circular to first node
merge(dlcl_1,dlcl_2) = 1<->2<->3<->circular to first node
merge(dlcl_2,dlcl_1) = 2<->3<->1<->circular to first node
merge(dlcl_2,dlcl_4) = 2<->3<->4<->5<->6<->7<->circular to first node
merge(dlcl_4,dlcl_2) = 4<->5<->6<->7<->2<->3<->circular to first node

Testing bt_to_dlcl
bt0 rotated is
bt_to_dlcl(bt0) = empty

bt1 rotated is
..5
4
....3
..2
....1
bt_to_dlcl(bt1) = 1<->2<->3<->4<->5<->circular to first node

bt2 rotated is
..5
4
....6
..2
....1
bt_to_dlcl(bt2) = 1<->2<->6<->4<->5<->circular to first node

bt3 rotated is
......15
....14
......13
..12
......11
....10
......9
8
......7
....6
......5
..4
......3
....2
......1
bt_to_dlcl(bt3) = 1<->2<->3<->4<->5<->6<->7<->8<->9<->10<->11<->12<->13<->14<->15<->circular to first node

bt4 rotated is
......15
....14
......13
..12
......11
....10
......9
8
......16
....6
......5
..4
......3
....2
......1
bt_to_dlcl(bt4) = 1<->2<->3<->4<->5<->6<->16<->8<->9<->10<->11<->12<->13<->14<->15<->circular to first node

 */