#include <iostream.h>
#include <stdlib.h>

#include "book.h"

class intintCompare {
public:
  static bool lt(int x, int y) { return x < y; }
  static bool eq(int x, int y) { return x == y; }
  static bool gt(int x, int y) { return x > y; }
};

class iiiComp {
public:
  inline static bool lt(int x, int y) { return x < y; }
  inline static bool eq(int x, int y) { return x == y; }
  inline static bool gt(int x, int y) { return x > y; }
};

int main(int argc, char** argv) {
  int a = 10;
  int b = 20;
  bool dum;

  Assert(argc == 2, "Usage: comptest <numruns>");

  int numruns = atoi(argv[1]);
  int i;

  Settime();
  for(i=0; i<numruns; i++) {
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
    dum = intintCompare::lt(a, b);
  }
  cout << "Time for class comparison: "
	   << Gettime() << " sec\n";

  Settime();
  for(i=0; i<numruns; i++) {
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
    dum = iiiComp::lt(a, b);
  }
  cout << "Time for inline'd class comparison: "
	   << Gettime() << " sec\n";

  Settime();
  for (i=0; i<numruns; i++) {
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
    dum = a < b;
  }
  cout << "Time for simple comparison: "
       << Gettime() << " sec\n";

  return 0;
}
