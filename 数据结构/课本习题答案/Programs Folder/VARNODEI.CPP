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
};

class LeafNode : public VarBinNode { // Leaf node
private:
  Operand var;                       // Operand value
public:
  LeafNode(const Operand& val) { var = val; } // Constructor
  bool isLeaf() { return true; }     // Version for LeafNode
  Operand value() { return var; }    // Return node value
};

class IntlNode : public VarBinNode { // Internal node
private:
  VarBinNode* left;                  // Left child
  VarBinNode* right;                 // Right child
  Operator opx;                      // Operator value
public:
  IntlNode(const Operator& op, VarBinNode* l, VarBinNode* r)
    { opx = op; left = l; right = r; } // Constructor
  bool isLeaf() { return false; }    // Version for IntlNode
  VarBinNode* leftchild() { return left; }   // Left child
  VarBinNode* rightchild() { return right; } // Right child
  Operator value() { return opx; }           // Value
};

void traverse(VarBinNode *subroot) { // Preorder traversal
  if (subroot == NULL) return;       // Nothing to visit
  if (subroot->isLeaf())             // Do leaf node
    cout << "Leaf: "
         << ((LeafNode *)subroot)->value() << endl;
  else {                             // Do internal node
    cout << "Internal: "
         << ((IntlNode *)subroot)->value() << endl;
    traverse(((IntlNode *)subroot)->leftchild());
    traverse(((IntlNode *)subroot)->rightchild());
  }
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
