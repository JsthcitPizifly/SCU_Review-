#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#define visit(X)

// Binary tree node abstract class
template <class Elem> class BinNode {
public:
  // Return the node's element
  virtual Elem& val() = 0;
  // Set the node's element
  virtual void setVal(const Elem&) = 0;
  // Return the node's left child
  virtual BinNode* left() const = 0;
  // Set the node's left child
  virtual void setLeft(BinNode*) = 0;
  // Return the node's right child
  virtual BinNode* right() const = 0;
  // Set the node's right child
  virtual void setRight(BinNode*) = 0;
  // Return true iff the node is a leaf
  virtual bool isLeaf() = 0;
};

// Binary tree node class
template <class Elem>
class BinNodePtr : public BinNode<Elem> {
public:
  Elem it;                     // The node's value
  BinNodePtr* lc;              // Pointer to left child
  BinNodePtr* rc;              // Pointer to right child
public:
  // Two constructors -- with and without initial values
  BinNodePtr() { lc = rc = NULL; }
  BinNodePtr(Elem e, BinNodePtr* l =NULL,
                     BinNodePtr* r =NULL)
    { it = e; lc = l; rc = r; }
  ~BinNodePtr() {}             // Destructor
  Elem& val() { return it; }
  void setVal(const Elem& e) { it = e; }
  BinNode<Elem>* left() const { return lc; }
  void setLeft(BinNode<Elem>* b) { lc = (BinNodePtr*)b; }
  BinNode<Elem>* right() const { return rc; }
  void setRight(BinNode<Elem>* b) { rc = (BinNodePtr*)b; }
  bool isLeaf() { return (lc == NULL) && (rc == NULL); }
};

int count1=0;
int count2=0;

int countp1=0;
int countp2=0;
int countp3=0;

// Binary tree
template <class Elem>
class bintree {
private:
  BinNode<Elem>* root;   // Root of the BST
public:
  bintree() { root = NULL; }  // Constructor
  BinNode<Elem>* getroot() { return root; }
  void setroot(BinNode<Elem>* newroot) { root = newroot; }
};


template <class Elem>
void preorder1(BinNode<Elem>* subroot)
{
  if (subroot->left() != NULL) preorder1(subroot->left());
  if (subroot->right() != NULL) preorder1(subroot->right());
}

template <class Elem>
void preorder1a(BinNodePtr<Elem>* subroot)
{
  if (subroot->lc != NULL) preorder1a(subroot->lc);
  if (subroot->rc != NULL) preorder1a(subroot->rc);
}

template <class Elem>
void preorder1b(BinNodePtr<Elem>* subroot)
{
  BinNodePtr<Elem>* myl = subroot->lc;
  BinNodePtr<Elem>* myr = subroot->rc;
  if (myl != NULL) preorder1b(myl);
  if (myr != NULL) preorder1b(myr);
}

template <class Elem>
void preorder2(BinNode<Elem>* subroot)
{
  if (subroot == NULL) return;  // Empty subtree, do nothing
  if (subroot->left() != NULL) preorder2(subroot->left());
  if (subroot->right() != NULL) preorder2(subroot->right());
}


template <class Elem>
void preorder3(BinNode<Elem>* subroot)
{
  if (subroot == NULL) return;  // Empty subtree, do nothing
  preorder3(subroot->left());
  preorder3(subroot->right());
}

template <class Elem>
void preorder3a(BinNodePtr<Elem>* subroot)
{
  if (subroot == NULL) return;  // Empty subtree, do nothing
  preorder3a(subroot->lc);
  preorder3a(subroot->rc);
}

template <class Elem>
BinNode<Elem>* insert(BinNode<Elem>* subroot, Elem val) {
  if (subroot == NULL)
    return new BinNodePtr<Elem>(val);
  else if (Random(2) == 0) {
count1++;
    subroot->setLeft(insert(subroot->left(), val));
	return subroot;
  }
  else {
count2++;
     subroot->setRight(insert(subroot->right(), val));
     return subroot;
  }
}


template <class Elem>
buildRandomTree(int numnodes, bintree<Elem>* tree) {
  for(int i=0; i<numnodes; i++)
    tree->setroot(insert(tree->getroot(), i));
}


int main(int argc, char** argv) {
  bintree<int>* tree = new bintree<int>();

  Assert(argc == 3, "Usage: travtest <numnodes> <numruns>");

  int numnodes = atoi(argv[1]);
  int numruns = atoi(argv[2]);
  int i;
  Randomize();
  cout << "Build a tree with " << numnodes << " nodes\n";
  buildRandomTree(numnodes, tree);
  cout << "count1 is " << count1 << "; count2 is " << count2 << endl;

  Settime();
  for (i=0; i<numruns; i++)
    preorder1(tree->getroot());
  cout << "Time for check-ahead (preorder1): "
	   << Gettime() << " sec\n";

  Settime();
  for (i=0; i<numruns; i++)
    preorder1a((BinNodePtr<int>*)tree->getroot());
  cout << "Time for stripped check-ahead (preorder1a): "
       << Gettime() << " sec\n";

  Settime();
  for (i=0; i<numruns; i++)
    preorder1b((BinNodePtr<int>*)tree->getroot());
  cout << "Time for prestored check-ahead (preorder1b): "
       << Gettime() << " sec\n";

  Settime();
  for (i=0; i<numruns; i++)
    preorder2(tree->getroot());
  cout << "Time for check-ahead with extra check (preorder2): "
       << Gettime() << " sec\n";

  Settime();
  for (i=0; i< numruns; i++)
    preorder3(tree->getroot());
  cout << "Time for pre-check with extra recursive calls (preorder3): "
       << Gettime() << " sec\n";

  Settime();
  for (i=0; i< numruns; i++)
    preorder3a((BinNodePtr<int>*)tree->getroot());
  cout << "Time for stripped pre-check with extra recursive calls (preorder3a): "
       << Gettime() << " sec\n";

  cout << "countp1: "<< countp1 << ", countp2: "
	   << countp2 << ", countp3: " << countp3 << endl;
  return 0;
}
