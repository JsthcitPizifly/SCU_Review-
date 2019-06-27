// Stack abtract class
template <class Elem> class Stack {
public:
  // Reinitialize the stack.  The user is responsible for
  // reclaiming the storage used by the stack elements.
  virtual void clear() = 0;
  // Push an element onto the top of the stack.  Return
  // true if successful, false if not (if stack is full).
  virtual bool push(const Elem&) = 0;
  // Remove the element at the top of the stack. Return
  // true if succesful, false if stack is empty.
  // The element removed is returned in the first parameter.
  virtual bool pop(Elem&) = 0; // Pop Elem from top of stack
  // Return in first parameter a copy of the top element.
  // Return true if succesful, false if stack is empty.
  virtual bool topValue(Elem&) const = 0;
  // Return the number of elements in the stack.
  virtual int length() const = 0;
};
