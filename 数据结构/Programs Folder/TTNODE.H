template <class Elem>
class TTNode {       // 2-3 tree node structure
public:
  Elem lkey;         // The node's left key
  Elem rkey;         // The node's right key
  TTNode* left;      // Pointer to left child
  TTNode* center;    // Pointer to middle child
  TTNode* right;     // Pointer to right child
  TTNode()
    { center = left = right = NULL; lkey = rkey = EMPTY; }
  ~TTNode() { }
  bool isLeaf() { return left == NULL; }
};
