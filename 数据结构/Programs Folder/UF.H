class Gentree {                // Gentree for UNION/FIND
private:
  int* array;                  // Node array
  int size;                    // Size of node array
  int FIND(int) const;         // Find root
public:
  Gentree(int);                // Constructor
  ~Gentree() { delete [] array; } // Destructor
  void UNION(int, int);        // Merge equivalences
  bool differ(int, int);       // TRUE if not in same tree
};

Gentree::Gentree(int sz) {     // Constructor
  size = sz;
  array = new int[sz];      // Create node array
  for(int i=0; i<sz; i++) array[i] = ROOT;
}

// Return TRUE if nodes are in different trees
bool Gentree::differ(int a, int b) {
  int root1 = FIND(a);   // Find root of node a
  int root2 = FIND(b);   // Find root of node b
  return root1 != root2;             // Compare roots
}

void Gentree::UNION(int a, int b) {  // Merge two subtrees
  int root1 = FIND(a);   // Find root of node a
  int root2 = FIND(b);   // Find root of node b
  if (root1 != root2) array[root2] = root1; // Merge
}

int Gentree::FIND(int curr) const { // With path compression
  if (array[curr] == ROOT) return curr;  // At root
    return array[curr] = FIND(array[curr]);
}
