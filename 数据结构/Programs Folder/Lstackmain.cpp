#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#include "lstack.h"

template <class El> void StackTest(Stack<El>& St) {
  El temp;

  // Test a bunch of stack operations
  if (St.topValue(temp))
    cout << "Top is " << temp << endl;
  else cout << "Nothing in stack\n";
  St.push(10);
  St.push(20);
  St.push(15);
  cout << "Size is " << St.length() << endl;
  if (St.topValue(temp))
    cout << "Top is " << temp << endl;
  else cout << "Nothing in stack\n";
  while(St.pop(temp))
    cout << temp << " ";
  cout << endl;
  if (St.topValue(temp))
    cout << "Top is " << temp << endl;
  else cout << "Nothing in stack\n";
  cout << "Size is " << St.length() << endl;
  St.clear();
  cout << "Size is " << St.length() << endl;
  cout << "That is all.\n\n";
}

// Driver class for list implementations

// Main routine for array-based list driver class
int main(int argc, char** argv) {
  // Declare some sample lists
  LStack<Int> S1;
  LStack<Int*> S2(15);
  LStack<int> S3;

  StackTest<Int>(S1);
  StackTest<int>(S3);
  return 0;
}
