// This is the file to include in your code if you want access to the
// complete LStack template class
#include <iostream>
// Include the link class
#include "link.h"

// First, get the declaration for the base stack class
#include "stack.h"

// Link list-based stack implementation
template <class Elem> class LStack: public Stack<Elem> {
private:
  Link<Elem>* top;           // Pointer to first element
  int size;                  // Count number of elements
public:
  LStack() { top = NULL; size = 0; }
  ~LStack() { clear(); }     // Destructor
  void clear() {
    while (top != NULL) {    // Delete link nodes
      Link<Elem>* temp = top;
      top = top->next;
      size = 0;
      delete temp;
    }
  }
  bool push(const Elem& item) {
    top = new Link<Elem>(item, top);
    size++;
    return true;
  }
  bool pop(Elem& it) {
    if (size == 0) 
		return false;
    it = top->element;
    Link<Elem>* ltemp = top->next;
    delete top;
    top = ltemp;
    size--;	
    return true;
  }
  bool topValue(Elem& it) const {
    if (size == 0) return false;
    it = top->element;
    return true;
  }
  Elem gettop()
  {
	  return top->element;
  }
  int length() const { return size; }
};
