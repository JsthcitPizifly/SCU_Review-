#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "book.h"
typedef char Operator;
typedef char* Operand;

class VarBinNode {   // Node abstract base class
public:
  virtual bool isLeaf() = 0;
  virtual void trav() = 0;
};

class LeafNode : public VarBinNode { // Leaf node
private:
  Operand var;                       // Operand value
public:
  LeafNode(const Operand& val) { var = val; } // Constructor
  bool isLeaf() { return true; }     // Version for Leafnode
  Operand value() { return var; }    // Return node value
  void trav() { cout << "Leaf: " << value() << endl; }
};

class IntlNode : public VarBinNode { // Internal node
private:
  VarBinNode* lc;                    // Left child
  VarBinNode* rc;                    // Right child
  Operator opx;                      // Operator value
public:
  IntlNode(const Operator& op, VarBinNode* l, VarBinNode* r)
    { opx = op; lc = l; rc = r; }    // Constructor
  bool isLeaf() { return false; }    // Version for IntlNode
  VarBinNode* left() { return lc; }  // Left child
  VarBinNode* right() { return rc; } // Right child
  Operator value() { return opx; }   // Value
  void trav() {
    cout << "Internal: " << value() << endl;
    if (left() != NULL) left()->trav();
    if (right() != NULL) right()->trav();
  }
};

void traverse(VarBinNode *root) {    // Preorder traversal
  if (root != NULL) root->trav();
}


// Main test routine
int main()
{
  VarBinNode* temp1;
  VarBinNode* temp2;
  VarBinNode* root;
  char *string1 = "Hello1";
  char *string2 = "Another string";

  temp1 = new LeafNode(string1);
  temp2 = new LeafNode(string2);
  root = new IntlNode('+', temp1, temp2);
  traverse(root);
  return(0);
}
