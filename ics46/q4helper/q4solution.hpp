#ifndef Q4SOLUTION_HPP_
#define Q4SOLUTION_HPP_


#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <vector>
#include "ics46goody.hpp"
#include "array_set.hpp"
#include "array_map.hpp"


////////////////////////////////////////////////////////////////////////////////

//Problems 3-5

//Two Pointer Node: Used to store both Binary Tree and Doubly-Linked Lists
//Binary Tree: left/right points to left/right subtrees
//Doubly-Linked Lists: left/right point to preceding and following nodes
template<class T>
class TPN {
  public:
    TPN (T value, TPN<T>* leftp = nullptr, TPN<T>* rightp = nullptr)
      : value(value), left(leftp), right(rightp)
    {}

  T       value;
  TPN<T>* left;
  TPN<T>* right;
};


//Build a doubly-linked circular list with values, in order specified
//Returns a pointer to node storing values[0] (or nullptr, if no nodes)
template<class T>
TPN<T>* build_dlcl(TPN<T>*& left, T values[], int N) {
  if (N == 0)
    return nullptr;

  left = new TPN<T>(values[0]);
  TPN<T>* prev = left;
  for (int i=1; i<N; ++i) {
    TPN<T>* last = new TPN<T>(values[i]);
    prev->right = last;
    last->left  = prev;
    prev = last;
  }

  left->left  = prev; //prev is currently last node
  prev->right = left;

  return left;
}

//Print a doubly-linked circular list on outs
//Check both left and right pointers for correctness, including
//   circularity of list
template<class T>
void print_dlcl(TPN<T>* t, std::ostream& outs) {
  if (t == nullptr)  {
    outs << "empty" << std::endl;
    return;
  }

  if (t->right == t)  {
    outs << t->value << "<->circular to first node";
    if (t->left != t)
      outs << "...but left of first node is not itself";
    outs << std::endl;
    return;
  }

  outs << t->value;
  TPN<T>* c = t->right;
  for (; /*see body*/; c = c->right) {
    outs << "<->" << c->value;
    if (c->left->right != c) {
      outs << "Last link had incorrect left pointer";
      return;
    }
    if (c->right == t)
      break;
  }
  outs << "<->circular to first node";
  if (t->left != c)
    outs << "...but left of first node is not last";
  outs << std::endl;
}

//Insert to_insert into binary tree t, comparing as if its value was as_if
//This approach allows building binary trees that do not satisfy the BST order property
//e.g., if I insert value 5 as it it were 2, then 5 is placed in the tree where 2 would go
//If the first and second values are always the same, the tree wlll be a BST.
template<class T>
void insert (TPN<T>*& t, T to_insert, T as_if) {
  if (t == nullptr)
    t = new TPN<T>(to_insert);    //nullptr implicit for left/right subtrees
  else
    if (as_if < t->value)
      insert(t->left, to_insert, as_if);
    else if (as_if > t->value)
      insert(t->right, to_insert, as_if);
}

//Build a binary tree using values_and_as_if; for each pair of values, the first is
//  put in the tree where the second belongs.
template<class T>
void build_bt(TPN<T>*& root, T values_and_as_if[], int N) {
  for (int i=0; i<N; i+=2)
    insert(root, values_and_as_if[i],values_and_as_if[i+1]);
}


//Print a binary tree on outs
template<class T>
void print_rotated(TPN<T>* t, std::string  indent, std::ostream& outs) {
  if (t == nullptr)
    return;
  else {
    print_rotated(t->right, indent+"..", outs);
    outs << indent << t->value << std::endl;
    print_rotated(t->left, indent+"..", outs);
  }
}


////////////////////////////////////////////////////////////////////////////////

//Problems 3

//Returns whether every value in root's tree is < value
template<class T>
bool all_less(TPN<T>* root, T value) {
  if (root == nullptr)
    return true;
  else
    return root->value < value && all_less(root->left,value) && all_less(root->right,value);
}

//Returns whether every value in root's tree is > value
template<class T>
bool all_greater(TPN<T>* root, T value) {
  if (root == nullptr)
    return true;
  else
    return root->value > value && all_greater(root->left,value) && all_greater(root->right,value);
}

//Returns whether root's tree satisfies the order property of binary search trees.
//Must be written as one if statement, declaring no local variables.
template<class T>
bool is_bst(TPN<T>* root) {
    return !root || all_less(root->left,root->value) && all_greater(root->right,root->value) && is_bst(root->left) && is_bst(root->right);
}

////////////////////////////////////////////////////////////////////////////////

//Problems 4

//Returns a pointer to the left-most value in the merged version of two doubly-linked circulalr lists.
template<class T>
TPN<T>* merge(TPN<T>* left, TPN<T>* right) {
    if(left && right)
    {
        auto mr1 = left->left;
        auto mr2 = right->left;
        mr1->right = right;
        left->left = mr2;
        right->left = mr1;
        mr2->right = left;
        return left;
    }
    else if(left)return left;
    else return right;

}

////////////////////////////////////////////////////////////////////////////////

//Problems 5

//Returns the doubly-linked circular list equivalent of a binary tree (switching the
//  meaning of left/right from subtree pointer to previous/next pointers
//The order in the resulting list is the same as an in-order traversal of the tree
//  (so for a BST it is in increasing order)
template<class T>
TPN<T>* bt_to_dlcl(TPN<T>* root) {
    if(!root)return nullptr;
    else if(!root->left && !root->right)
    {
        root->left=root;
        root->right=root;
        return root;
    }
    auto left=bt_to_dlcl(root->left);
    auto right=bt_to_dlcl(root->right);
    root->left=root;
    root->right=root;
    auto result=merge(left,root);
    return merge(result,right);

}



#endif /* Q4SOLUTION_HPP_ */
