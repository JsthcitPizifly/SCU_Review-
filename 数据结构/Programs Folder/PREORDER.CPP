#include <iostream.h>
#include <stdlib.h>
#include "book.h"

#include "binnode.h"

// Stick these in to test the preorder routine
#define visit(X) (cout << X->val() << endl)

template <class Elem>
void preorder(BinNode<Elem>* subroot) {
  if (subroot == NULL) return;  // Empty subtree, do nothing
  visit(subroot);  // Perform whatever action is desired
  preorder(subroot->left());
  preorder(subroot->right());
}

template <class Elem>
int count(BinNode<Elem>* subroot) {
  if (subroot == NULL) return 0;  // Nothing to count
  return 1 + count(subroot->left())
           + count(subroot->right());
}

// Test the preorder traversal routines
int main()
{
  BinNodePtr<Int>* root = new BinNodePtr<Int>(10);
  root->setLeft(new BinNodePtr<Int>(15));
  root->setRight(new BinNodePtr<Int>(20));
  preorder(root);
  cout << " Count is: " << count(root) << endl;
}
