// WARNING: This is NOT a complete implementation for B+-trees.
// The sole purpose of this code is to do a syntactic check on the book
// pseudocode.  You can probably create a complete B+-tree implementation
// by implementing the missing functions, but I make no guarentees.
// The purpose of the book pseudocode is not to present an implementation,
// but only to illustrate how the B+-tree works.

#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#define MAXREC 10
#define THRESHOLD 6

template <class Key>
class PAIR {
public:
  void* ptr; // Elem* for leaves, BPNode* for internals
  Key key;
};

template <class Key>
class BPNode {
public:
  PAIR<Key> recs[MAXREC];
  int numrec;
  BPNode* leftptr;  BPNode* rightptr; // Link the levels
  bool isLeaf() const;  // True if the node is a leaf
  bool isFull() const;  // True if the node is full
};

template <class Key>
bool BPNode<Key>::isLeaf() const {}

template <class Key>
bool BPNode<Key>::isFull() const {}

template <class Key, class Elem, class KKcomp>
class BPTree {
private:
  BPNode<Key>* root;
  int reccount;
  bool findhelp(BPNode<Key>* root, const Key& K, Elem*& e) const;
  bool inserthelp(BPNode<Key>* root, const Key& K, Elem* e,
                  Key& retval, void*& retptr);
  bool removehelp(BPNode<Key>* root, const Key& K, Elem*& e);
public:
  BPTree() { root = NULL; reccount = 0; }
  ~BPTree() {};
  bool insert(const Key& K, Elem* e) { // Insert node with value val
    Elem retval;               // Smallest value in newly created node
    void* retptr = NULL; // Newly created node
    bool inssucc = inserthelp(root, K, e, retval, retptr);
    if (retptr != NULL) {      // Root overflowed: make new root
      BPNode<Key>* temp = new BPNode<Key>;
      temp->recs[0].key = root->recs[0].key;
      temp->recs[0].ptr = root;
      temp->recs[1].key = retval;
      temp->recs[1].ptr = retptr;
      root = temp;
    }
    if (inssucc) reccount++;
    return inssucc;
  }
  bool remove(const Key& K, Elem*& e) {
    e = NULL;
    removehelp(root, K, e);
    return e != NULL;
  }
  bool find(const Key& K, Elem*& e) const { findhelp(root, K, e); }
};


template <class Key, class Elem, class KKcomp>
bool BPTree<Key, Elem, KKcomp>::
findhelp(BPNode<Key>* root, const Key& K, Elem*& e) const {
  // function binaryle(A, n, K) returns the greatest value
  //   less than or equal to K in array A of length n.
  int currec = binaryle(root->recs, root->numrec, K);
  if (root->isLeaf())
    if (KKcomp::eq(root->recs[currec].key, K)) {
      e = (Elem*) root->recs[currec].ptr;
      return true;
    }
    else return false;
  else return findhelp((BPNode<Key>*)
                       root->recs[currec].ptr, K, e);
}

template <class Key>
int binaryle(PAIR<Key>* array, int numrec, Key K) {}

template <class Key>
void putinarray(PAIR<Key>* array, int currec, Key retval, void* retptr) {}

template <class Key>
void* splitnode(BPNode<Key>* root, int currect, Key& myretv,
                       void*& myretp) {}

// B+-tree pseudocode: insert
// binaryle(A, n, K) returns the greatest value less
// than or equal to K in array A of length n.
// putinarray(A, pos, k, p) places in array A at
// position pos the key/pointer pair k and p.
// splitnode(rt, pos, k, p) places in node rt at
// position pos the key/pointer pair k/p.  In the process,
// the node is split into two, each taking half of the
// records, and the new node is returned.
template <class Key, class Elem, class KKcomp>
bool BPTree<Key, Elem, KKcomp>::
inserthelp(BPNode<Key>* subroot, const Key& K, Elem* e,
           Key& retval, void*& retptr) {
  Key myretv;  // Least key in new node if current is split
  void* myretp = NULL; // Pointer to new node on split

  int currec = binaryle(subroot->recs, subroot->numrec, K);
  if (subroot->isLeaf()) { // Leaf node: set insert values
    myretv = K;
    myretp = e;
  }
  else { // internal node
    inserthelp((BPNode<Key>*)subroot->recs[currec].ptr,
               K, e,  myretv, myretp);
    if (myretp == NULL) return true; // Child did not split,
  }                     // no need to insert to current node

  // Do insert to the current node.  Split if necessary
  if (subroot->isLeaf() &&
      KKcomp::eq(subroot->recs[currec].key, myretv))
    return false; // Duplicate
  if (!subroot->isFull())
    putinarray<Key>(subroot->recs, currec, myretv, myretp);
  else {
    retptr = splitnode<Key>(subroot, currec, myretv,myretp);
    retval = ((BPNode<Key>*)retptr)->recs[0].key;
  }
  return true;
}

template <class Key>
void removerec(BPNode<Key>* root, int currec) {}

template <class Key>
void merge_nodes(BPNode<Key>* root, BPNode<Key>* right) {}

template <class Key>
void shuffle_nodes(BPNode<Key>* root, BPNode<Key>* right) {}

// removehelp returns TRUE if a child has been removed.
//   If so, adjustment to the current node is required.
// binaryle(A, n, K) returns the greatest value less than
//   or equal to K in array A of length n.
// removerec(A, n, c) removes record at position c from
//   array A with n records.
// merge_nodes(N1, N2) merges together the record arrays of
//   BPNodes N1 and N2.
// shuffle_nodes(N1, N2) copies execess records from BPNode
//   N2 to BPNode N1, so that both have equal # of records. 
template <class Key, class Elem, class KKcomp>
bool BPTree<Key, Elem, KKcomp>::
removehelp(BPNode<Key>* subroot, const Key& K,
           Elem*& retval) {
  int currec;  bool delchild;

  currec = binaryle(root->recs, root->numrec, K);
  if (root->isLeaf())
    if (!KKcomp::eq(K, root->recs[currec].key))
      return false;
    else retval = (Elem*)root->recs[currec].ptr;
  else // Delete from child
    if (!removehelp((BPNode<Key>*) root->recs[currec].ptr,
                          K, retval))
       return false; // Child did not collapse
  // Now, remove record at position currec
  removerec(root, currec);
  if (root->numrec > THRESHOLD) return false;
  else                           // Underflow
    if (root->leftptr == NULL)   // No left neighbor
      if (root->numrec + root->rightptr->numrec <= MAXREC) {
        merge_nodes(root, root->rightptr);
        return true;
      }
      else {                     // Key value has changed
        shuffle_nodes(root, root->rightptr);
        retval = (Elem*)root->rightptr->recs[0].ptr;
        return false;
      }
    else if (root->numrec+root->leftptr->numrec <= MAXREC) {
      merge_nodes(root->leftptr, root);
      return true;
    }
    else {
      shuffle_nodes(root, root->leftptr);
      retval = (Elem*)root->recs[0].ptr;
      return false;
    }
}

int main()
{
  BPTree<int,int,intintCompare> tree;

  int* val;
  tree.find(5, val);
  tree.insert(5, val);
  tree.remove(5, val);
  return 0;
}
