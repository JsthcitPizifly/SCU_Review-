#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#include "dictionary.h"

#include "ttnode.h"

// A flyweight
Int* EMPTY = new Int(-1);

#include "tt.h"

template <class Key, class Elem, class KEComp, class EEComp>
void TTTree<Key, Elem, KEComp, EEComp>::
printhelp(TTNode<Elem>* subroot, int level) const {
  if (subroot == NULL) return;
  for (int i=0; i<level; i++) cout << "   "; // indent
  cout << subroot->lkey;
  if (subroot->rkey != EMPTY)
    cout << "  " << subroot->rkey << "\n";
  else cout << "\n";
  printhelp(subroot->left, level+1);
  printhelp(subroot->center, level+1);
  if (subroot->rkey != EMPTY)
    printhelp(subroot->right, level+1);
}

// Insert an Elem into the 2-3 tree.  Subroot is the current
// node, e is the Elem to be inserted, retval and retptr are
// return values for promoted element and child node when
// current node is split. 
template <class Key, class Elem, class KEComp, class EEComp>
bool TTTree<Key, Elem, KEComp, EEComp>::
inserthelp(TTNode<Elem>*& subroot, const Elem& e,
           Elem& retval, TTNode<Elem>*& retptr) {
  Elem myretv;  TTNode<Elem>* myretp = NULL;
  if (subroot == NULL)  // Empty tree: make new node
    { subroot = new TTNode<Elem>(); subroot->lkey = e; }
  else if (subroot->isLeaf())   // At leaf node: insert here
    if (subroot->rkey == EMPTY) { // Easy case: not full
      if (EEComp::gt(e, subroot->lkey)) subroot->rkey = e;
      else {subroot->rkey = subroot->lkey;
            subroot->lkey = e; }}
    else splitnode(subroot, e, NULL, retval, retptr);
  else if (EEComp::lt(e, subroot->lkey)) // Insert in child
    inserthelp(subroot->left, e, myretv, myretp);
  else if ((subroot->rkey == EMPTY) ||
           (EEComp::lt(e, subroot->rkey)))
    inserthelp(subroot->center, e, myretv, myretp);
  else inserthelp(subroot->right, e, myretv, myretp);
  if (myretp != NULL) // Child split: receive promoted value
    if (subroot->rkey != EMPTY) // Full: split node
      splitnode(subroot, myretv, myretp, retval, retptr);
    else { // Not full: add to this node
      if (EEComp::lt(myretv, subroot->lkey)) {
        subroot->rkey = subroot->lkey;
        subroot->lkey = myretv;
        subroot->right = subroot->center;
        subroot->center = myretp;
      }
      else
        { subroot->rkey = myretv; subroot->right = myretp; }
    }
  return true;
}

// Split a node in 2-3 tree.  Subroot is node being split,
// inval is Elem being inserted, inptr is child node being
// added (if subroot is an internal node), retval and retptr
// are promoted value and child, respectively.
template <class Key, class Elem, class KEComp, class EEComp>
bool TTTree<Key, Elem, KEComp, EEComp>::
splitnode(TTNode<Elem>* subroot, const Elem& inval,
          TTNode<Elem>*inptr, Elem& retval,
          TTNode<Elem>*& retptr) {
  retptr = new TTNode<Elem>();  // Node created by split
  if (EEComp::lt(inval, subroot->lkey)) { // Add at left
    retval = subroot->lkey;  subroot->lkey = inval;
    retptr->lkey = subroot->rkey;
    retptr->left = subroot->center;
    retptr->center = subroot->right;
    subroot->center = inptr;
  }
  else if (EEComp::lt(inval, subroot->rkey)) { // Center
    retval = inval;  retptr->lkey = subroot->rkey;
    retptr->left = inptr;
    retptr->center = subroot->right;
  }
  else { // Add at right
    retval = subroot->rkey;  retptr->lkey = inval;
    retptr->left = subroot->right;
    retptr->center = inptr;
  }
 subroot->rkey = EMPTY;
}

template <class Key, class Elem, class KEComp, class EEComp>
bool TTTree<Key, Elem, KEComp, EEComp>::
findhelp(TTNode<Elem>* subroot,
         const Key& K, Elem& e) const {
  if (subroot == NULL) return false;     // val not found
  if (KEComp::eq(K, subroot->lkey))
    { e = subroot->lkey; return true; }
  if ((subroot->rkey != EMPTY) &&
      (KEComp::eq(K, subroot->rkey)))
    { e = subroot->rkey; return true; }
  if (KEComp::lt(K, subroot->lkey))      // Search left
    return findhelp(subroot->left, K, e);
  else if (subroot->rkey == EMPTY)       // Search center
    return findhelp(subroot->center, K, e);
  else if (KEComp::lt(K, subroot->rkey)) // Search center
    return findhelp(subroot->center, K, e);
  else return findhelp(subroot->right, K, e); // Right
}

// Warning: This has horrible memory leaks.
// Everytime it does a remove to "it",
// the next time "it" gets used, that previous
// Int object gets clobbered.
int main()
{
  TTTree<int, Int*, intIntsCompare, IntsIntsCompare > tree;
  Int* it;

  cout << "Size: " << tree.size() << "\n";
  tree.insert(new Int(100));
  tree.print();
  cout << "Size: " << tree.size() << "\n";
  tree.remove(10, it);
  tree.print();
  cout << "Size: " << tree.size() << "\n";
  tree.clear();
  cout << "Size: " << tree.size() << "\n";
  tree.insert(new Int(15));
  cout << "Size: " << tree.size() << "\n";
  if (tree.find(20, it))
    cout << "Found " << it << endl;
  else cout << "No key 20\n";
  if (tree.find(15, it))
    cout << "Found " << it << endl;
  else cout << "No key 15\n";
  tree.print();
  if (tree.remove(20, it))
    cout << "Removed " << it << endl;
  else cout << "No key 20\n";
  cout << "Now, insert 20\n";
  tree.insert(new Int(20));
  tree.print();
  if (tree.remove(20, it))
    cout << "Removed " << it << endl;
  else cout << "No key 20\n";
  tree.print();
  tree.insert(new Int(700));
  cout << "Size: " << tree.size() << "\n";
  tree.print();
  tree.insert(new Int(350));
  tree.print();
  tree.insert(new Int(201));
  tree.print();
  tree.insert(new Int(170));
  tree.print();
  tree.insert(new Int(151));
  tree.print();
  tree.insert(new Int(190));
  tree.print();
  tree.insert(new Int(1000));
  tree.print();
  tree.insert(new Int(900));
  tree.print();
  tree.insert(new Int(950));
  tree.print();
  tree.insert(new Int(10));
  tree.print();
  if (tree.find(1000, it))
    cout << "Found " << it << endl;
  else cout << "No key 1000\n";
  if (tree.find(999, it))
    cout << "Found " << it << endl;
  else cout << "No key 999\n";
  if (tree.find(20, it))
    cout << "Found " << it << endl;
  else cout << "No key 20\n";
  cout << "Now do some delete tests.\n";
  if (tree.remove(15, it))
    cout << "Removed " << it << endl;
  else cout << "No key 15\n";
  tree.print();
  if (tree.remove(151, it))
    cout << "Removed " << it << endl;
  else cout << "No key 151\n";
  tree.print();
  if (tree.remove(151, it))
    cout << "Removed " << it << endl;
  else cout << "No key 151\n";
  if (tree.remove(700, it))
    cout << "Removed " << it << endl;
  else cout << "No key 700\n";
  tree.print();
  tree.clear();
  tree.print();
  cout << "Size: " << tree.size() << "\n";

  cout << "Finally, test iterator\n";
  tree.insert(new Int(3500));
  tree.insert(new Int(2010));
  tree.insert(new Int(1700));
  tree.insert(new Int(1510));
  tree.insert(new Int(1900));
  tree.insert(new Int(10000));
  tree.insert(new Int(9000));
  tree.insert(new Int(9500));
  tree.insert(new Int(100));
  tree.print();
  while (tree.removeAny(it))
    cout << it << " ";
  cout << "\n";
  return 0;
}
