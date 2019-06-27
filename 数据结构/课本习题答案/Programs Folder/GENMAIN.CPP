#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "book.h"

template <class Elem>
class GTNode {
private:
  Elem element;
  GTNode<Elem>* rent;
  GTNode<Elem>* leftchild;
  GTNode<Elem>* rightsib;
public:
  GTNode(const Elem&);             // Constructor
  GTNode(const Elem&, GTNode<Elem>*,
					  GTNode<Elem>*, GTNode<Elem>*);
  ~GTNode();                       // Destructor
  Elem value();                    // Return node's value
  bool isLeaf();                   // TRUE if node is a leaf
  GTNode* parent();                // Return node's parent
  GTNode* leftmost_child();        // Return node's first child
  GTNode* right_sibling();         // Return node's right sibling
  void setValue(Elem&);            // Set node's value
  void insert_first(GTNode<Elem>* n);    // Insert as the first child
  void insert_next(GTNode<Elem>* n);     // Insert as the right sibling
  void remove_first();             // Remove first child from tree
  void remove_next();              // Remove right sibling from tree
};

template <class Elem>
GTNode<Elem>::GTNode(const Elem& value) {
  rent = leftchild = rightsib = NULL;
  element = value;
}

template <class Elem>
GTNode<Elem>::GTNode(const Elem& value, GTNode<Elem>* par,
					 GTNode<Elem>* leftc, GTNode<Elem>* rights) {
  element = value;
  rent = par; leftchild = leftc; rightsib = rights;
}  

template <class Elem>
GTNode<Elem>::~GTNode() { }

template <class Elem>
Elem GTNode<Elem>::value() { return element; }

template <class Elem>
bool GTNode<Elem>::isLeaf() { return leftchild == NULL; }

template <class Elem>
GTNode<Elem>* GTNode<Elem>::parent() { return rent; }

template <class Elem>
GTNode<Elem>* GTNode<Elem>::leftmost_child() { return leftchild; }

template <class Elem>
GTNode<Elem>* GTNode<Elem>::right_sibling() { return rightsib; }

template <class Elem>
void GTNode<Elem>::setValue(Elem& value) { element = value; }

template <class Elem>
void GTNode<Elem>::insert_first(GTNode<Elem>* n) {
  n->rightsib = leftchild;
  n->rent = this;
  leftchild = n;
}

template <class Elem>
void GTNode<Elem>::insert_next(GTNode<Elem>* n) {
  n->rightsib = rightsib;
  n->rent = rent;
  rightsib = n;
}

template <class Elem>
void GTNode<Elem>::remove_first() {
  if (leftchild == NULL) return;
  GTNode<Elem>* temp = leftchild;
  leftchild = leftchild->rightsib;
  delete temp;  // BAD -- lose all its subtree!
}

template <class Elem>
void GTNode<Elem>::remove_next() {
  if (rightsib == NULL) return;
  GTNode<Elem>* temp = rightsib;
  rightsib = rightsib->rightsib;
  delete temp;  // BAD -- lose all its subtree!
}

/////////////////////////////////////////////

template <class Elem>
class GenTree {
private:
  GTNode<Elem>* rt;
  void printhelp(GTNode<Elem>*);    // Print helper function
public:
  GenTree();                        // Constructor
  ~GenTree();                       // Destructor
  void clear();                     // Send all nodes to free store
  GTNode<Elem>* root();             // Return the root of the tree
  void newroot(const Elem&, GTNode<Elem>*, GTNode<Elem>*); // Combine two trees
  void print() { printhelp(rt); } // Print a tree
};

template <class Elem>
GenTree<Elem>::GenTree() { rt = NULL; }

template <class Elem>
GenTree<Elem>::~GenTree() { rt = NULL; } // AWFUL! Throw away the storage

template <class Elem>
void GenTree<Elem>::clear() { rt = NULL; } // AWFUL! Throw away the storage

template <class Elem>
GTNode<Elem>* GenTree<Elem>::root() { return rt; }

template <class Elem>
void GenTree<Elem>::newroot(const Elem& value, GTNode<Elem>* first,
                                               GTNode<Elem>* sib) {
  clear();
  rt = new GTNode<Elem>(value, (GTNode<Elem>*)NULL, first, sib);
}


template <class Elem>  // Print using a preorder traversal
void GenTree<Elem>::printhelp(GTNode<Elem>* subroot) {
  if (subroot->isLeaf()) cout << "Leaf: ";
  else cout << "Internal: ";
  cout << subroot->value() << "\n";
  for (GTNode<Elem>* temp = subroot->leftmost_child();
       temp != NULL; temp = temp->right_sibling())
    printhelp(temp);
}

main()
{
  GenTree<int> tree;
  GTNode<int>* ptr;
  GenTree<int> tree2;
  GTNode<int>* ptr2;

  tree.newroot(1, NULL, NULL);
  ptr = tree.root();
  cout << "Print the tree with one node\n";
  tree.print();
  ptr->insert_first(new GTNode<int>(2));
  cout << "Print the tree with two nodes\n";
  tree.print();
  ptr = ptr->leftmost_child();
  cout << "ptr now at node " << ptr->value() << "\n";
  ptr->insert_next(new GTNode<int>(3));
  cout << "Print the tree with three nodes\n";
  tree.print();
  ptr->insert_next(new GTNode<int>(4));
  cout << "Print the tree with four nodes\n";
  tree.print();
  ptr = ptr->right_sibling();
  cout << "ptr now at node " << ptr->value() << "\n";
  ptr->insert_first(new GTNode<int>(5));
  cout << "Print the tree with 5 nodes\n";
  tree.print();

  tree2.newroot(11, NULL, NULL);
  ptr2 = tree2.root();
  ptr2->insert_first(new GTNode<int>(12));
  ptr2 = ptr2->leftmost_child();
  ptr2->insert_next(new GTNode<int>(13));

  return(0);
}
