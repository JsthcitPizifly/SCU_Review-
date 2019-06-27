#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#include "alist.h"

#include "salist.h"

// Driver class for sorted array-based list implementation

int main(int argc, char** argv) {
  // Declare some sample lists
  SAList<Int*,IntsIntsCompare> L1;
  SAList<Int*,IntsIntsCompare> L2(15);
  SAList<Int,IntIntCompare> L3;

  Int dum;
  L3.insert(5);
  L3.insert(10);
  L3.insert(3);
  L3.insert(7);
  L3.print();
  L3.setStart();
  L3.remove(dum);
  cout << "Removed " << dum << endl;
  L3.print();
  return 0;
}
