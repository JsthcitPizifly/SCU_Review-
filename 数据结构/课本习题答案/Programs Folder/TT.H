// Two-three tree implementation for the Dictionary ADT
template <class Key, class Elem, class KEComp, class EEComp>
class TTTree : public Dictionary<Key, Elem, KEComp, EEComp> {
private:
  TTNode<Elem>* root;          // Root of the tree
  int reccount;          // Number of records stored
  // Private "helper" functions
  void clearhelp(TTNode<Elem>*)                // Helper functions
    { cout << "Clearhelp not yet defined\n"; }
  bool inserthelp(TTNode<Elem>*&, const Elem&, Elem&, TTNode<Elem>*&);
  bool splitnode(TTNode<Elem>* subroot, const Elem& inval, TTNode<Elem>*inptr,
                               Elem& retval, TTNode<Elem>*& retptr);
  bool findhelp(TTNode<Elem>*, const Key&, Elem&) const;
  void printhelp(TTNode<Elem>*, int) const;
public:
  TTTree() { root = NULL; reccount = 0; }
  ~TTTree() { clearhelp(root); }
  void clear()
    { clearhelp(root);  root = NULL; reccount = 0; }
  bool insert(const Elem& e) { // Insert node with value val
    Elem retval;               // Smallest value in newly created node
    TTNode<Elem>* retptr = NULL; // Newly created node
    bool inssucc = inserthelp(root, e, retval, retptr);
    if (retptr != NULL) {      // Root overflowed: make new root
      TTNode<Elem>* temp = new TTNode<Elem>;  temp->lkey = retval;
      temp->left = root; temp->center = retptr;
      root = temp;
    }
    if (inssucc) reccount++;
    return inssucc;
  }
  bool remove(const Key& K, Elem& e) {
    cout << "Remove not implemented\n";
    return false;
  }
  bool removeAny(Elem& e) {
    cout << "RemoveAny not implemented\n";
    return false;
  }
  bool find(const Key& K, Elem& e) const
    { return findhelp(root, K, e); }
  int size() { return reccount; }
  void print() const {
    cout << "Print tree: \n";
    if (root == NULL) cout << "The 2-3 Tree is empty.\n";
    else printhelp(root, 0);
  }
};
