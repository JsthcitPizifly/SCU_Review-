// Singly-linked list node
template <class Elem> class Link {
public:
  Elem element;      // Value for this node
  Link *next;        // Pointer to next node in list
  Link(const Elem& elemval, Link* nextval =NULL)
    { element = elemval;  next = nextval; }
  Link(Link* nextval =NULL) { next = nextval; }
};
