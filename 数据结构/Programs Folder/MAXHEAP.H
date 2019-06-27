// Max-heap class
template <class Elem, class Comp> class maxheap {
private:
  Elem* Heap;          // Pointer to the heap array
  int size;            // Maximum size of the heap
  int n;               // Number of elements now in the heap
  void siftdown(int);  // Put element in its correct place
public:
  maxheap(Elem* h, int num, int max)     // Constructor
    { Heap = h;  n = num;  size = max;  buildHeap(); }
  int heapsize() const       // Return current heap size
    { return n; }
  bool isLeaf(int pos) const // TRUE if pos is a leaf
    { return (pos >= n/2) && (pos < n); }
  int leftchild(int pos) const
    { return 2*pos + 1; }    // Return leftchild position
  int rightchild(int pos) const
    { return 2*pos + 2; }    // Return rightchild position
  int parent(int pos) const  // Return parent position
    { return (pos-1)/2; }
  bool insert(const Elem&);  // Insert value into heap
  bool removemax(Elem&);     // Remove maximum value
  bool remove(int, Elem&);   // Remove from given position
  void buildHeap()           // Heapify contents of Heap
    { for (int i=n/2-1; i>=0; i--) siftdown(i); }
};

template <class Elem, class Comp> // Utility function
void maxheap<Elem, Comp>::siftdown(int pos) {
  while (!isLeaf(pos)) {     // Stop if pos is a leaf
    int j = leftchild(pos);  int rc = rightchild(pos);
    if ((rc < n) && Comp::lt(Heap[j], Heap[rc]))
      j = rc;        // Set j to greater child's value
    if (!Comp::lt(Heap[pos], Heap[j])) return; // Done
    swap(Heap, pos, j);
    pos = j;         // Move down
  }
}

template <class Elem, class Comp> // Insert element
bool maxheap<Elem, Comp>::insert(const Elem& val) {
  if (n >= size) return false; // Heap is full
  int curr = n++;
  Heap[curr] = val;            // Start at end of heap
  // Now sift up until curr's parent > curr
  while ((curr!=0) &&
         (Comp::gt(Heap[curr], Heap[parent(curr)]))) {
    swap(Heap, curr, parent(curr));
    curr = parent(curr);
  }
  return true;
}

template <class Elem, class Comp> // Remove max value
bool maxheap<Elem, Comp>::removemax(Elem& it) {
  if (n == 0) return false; // Heap is empty
  swap(Heap, 0, --n);       // Swap max with last value
  if (n != 0) siftdown(0);  // Siftdown new root val
  it = Heap[n];             // Return deleted value
  return true;
}

// Remove value at specified position
template <class Elem, class Comp>
bool maxheap<Elem, Comp>::remove(int pos, Elem& it) {
  if ((pos < 0) || (pos >= n)) return false; // Bad pos
  swap(Heap, pos, --n);           // Swap with last value
  while ((pos != 0) &&
         (Comp::gt(Heap[pos], Heap[parent(pos)])))
    swap(Heap, pos, parent(pos)); // Push up if large key
  siftdown(pos);      // Push down if small key
  it = Heap[n];
  return true;
}
