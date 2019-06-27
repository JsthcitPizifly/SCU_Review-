#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "book.h"
typedef char Operator;
typedef char* Operand;

enum Nodetype {leaf, internal};  // Enumerate node types

class VarBinNode {       // Generic node class
public:
  Nodetype mytype;       // Stores the type for this node
  union {
    struct {             // Structure for internal node
      VarBinNode* left;  // Left child
      VarBinNode* right; // Right child
      Operator opx;      // Internal node value
    } intl;
    Operand var;         // Leaves just store a value
  };
  VarBinNode(const Operand& val) // Constructor: leaf
    { mytype = leaf; var = val; }
  // Constructor: Internal
  VarBinNode(const Operator& op, VarBinNode* l,
                                 VarBinNode* r) {
    mytype = internal; intl.opx = op;
    intl.left = l; intl.right = r;
  }
  bool isLeaf() { return mytype == leaf; }
  VarBinNode* leftchild() { return intl.left; }
  VarBinNode* rightchild() { return intl.right; }
};

void traverse(VarBinNode* subroot) { // Preorder traversal
  if (subroot == NULL) return;
  if (subroot->isLeaf())
    cout << "Leaf: " << subroot->var << "\n";
  else {
    cout << "Internal: " << subroot->intl.opx << "\n";
    traverse(subroot->leftchild());
    traverse(subroot->rightchild());
  }
}


// Main test routine
int main()
{
  VarBinNode* temp1;
  VarBinNode* temp2;
  VarBinNode* root;
  char* string1 = "Hello1";
  char* string2 = "Another String";

  temp1 = new VarBinNode(string1);
  temp2 = new VarBinNode(string2);
  root = new VarBinNode('+', temp1, temp2);
  traverse(root);
  return(0);
}
