// General tree node ADT
template <class Elem> class GTNode {
public:
  GTNode(const Elem&);             // Constructor
  ~GTNode();                       // Destructor
  Elem value();                    // Return node's value
  bool isLeaf();                   // TRUE if node is a leaf
  GTNode* parent();                // Return parent
  GTNode* leftmost_child();        // Return first child
  GTNode* right_sibling();         // Return right sibling
  void setValue(Elem&);            // Set node's value
  void insert_first(GTNode<Elem>* n); // Insert first child
  void insert_next(GTNode<Elem>* n);  // Insert next sibling
  void remove_first();             // Remove first child
  void remove_next();              // Remove right sibling
};

// General tree ADT
template <class Elem> class GenTree {
private:
  void printhelp(GTNode*); // Print helper function
public:
  GenTree();               // Constructor
  ~GenTree();              // Destructor
  void clear();            // Send nodes to free store
  GTNode* root();          // Return the root
  // Combine two subtrees
  void newroot(Elem&, GTNode<Elem>*, GTNode<Elem>*);
  void print();            // Print a tree
};
