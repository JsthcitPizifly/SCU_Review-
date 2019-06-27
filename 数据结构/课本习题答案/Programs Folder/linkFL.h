// Singly-linked list node with freelist support
template <class Elem> class Link {
private:
  static Link<Elem>* freelist; // Head of the freelist
public:
  Elem element;                // Value for this node
  Link* next;                  // Point to next node in list
  Link(const Elem& elemval, Link* nextval =NULL)
    { element = elemval;  next = nextval; }
  Link(Link* nextval =NULL) { next = nextval; }
  void* operator new(size_t);  // Overloaded new operator
  void operator delete(void*); // Overloaded delete operator
};

template <class Elem>
Link<Elem>* Link<Elem>::freelist = NULL;

template <class Elem>   // Overload for new operator
void* Link<Elem>::operator new(size_t) {
  if (freelist == NULL) return ::new Link; // Create space
  Link<Elem>* temp = freelist;  // Can take  from freelist
  freelist = freelist->next;
  return temp;                 // Return the link
}

template <class Elem>   // Overload for delete operator
void Link<Elem>::operator delete(void* ptr) {
  ((Link<Elem>*)ptr)->next = freelist; // Put on freelist
  freelist = (Link<Elem>*)ptr;
}
