#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#define ROOT -1

// Collect together the UNION/FIND functions
#include "ufs.h"

int main(int argc, char** argv) {
  Gentree* gt = new Gentree(10);
  gt->UNION(1, 2);
  cout << gt->differ(0, 1) << endl;
  cout << gt->differ(2, 1) << endl;
  return 0;
}
