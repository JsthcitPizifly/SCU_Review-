// This is the file to include in your code if you want access to the
// complete LQueue template class

// Include the link class
#include "link.h"

// First, get the declaration for the base stack class
#include "queue.h"

// Linked queue implementation
template <class Elem> class LQueue: public Queue<Elem> {
private:
  Link<Elem>* front;     // Pointer to front queue node
  Link<Elem>* rear;      // Pointer to rear queue node
  int size;              // Number of elements in queue
public:
  LQueue(int sz =DefaultListSize)  // Constructor 
    { front = NULL;  rear = NULL; size = 0; }
  ~LQueue() { clear(); } // Destructor
  void clear() {         // Clear queue
    while(front != NULL) { // Delete each link node
      rear = front;
      front = front->next;
      delete rear;
    }
    rear = NULL;
    size = 0;
  }
  bool enqueue(const Elem& it) {
    if (rear == NULL)   // Empty queue
      front = rear = new Link<Elem>(it, NULL);
    else {              // Append new node
      rear->next = new Link<Elem>(it, NULL);
      rear = rear->next;
    }
    size++;
    return true;
  }
  bool dequeue(Elem& it) { // Remove Elem from front
    if (size == 0) return false;    // Empty
    it = front->element;            // Store dequeued value
    Link<Elem>* ltemp = front;      // Hold dequeued link
    front = front->next;            // Advance front
    delete ltemp;                   // Delete link
    if (front == NULL) rear = NULL; // Dequeued last element
    size --;
    return true;                    // Return element value
  }
  bool frontValue(Elem& it) const {
    if (size == 0) return false;
    it = front->element;
    return true;
  }
  virtual int length() const { return size; }
};
