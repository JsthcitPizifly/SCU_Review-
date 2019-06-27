#include <iostream.h>
#include <stdlib.h>

#include "book.h"

class Payroll {
public:
  int ID;
  char* name;
};

class IDCompare {
public:
  static bool lt(Payroll& x, Payroll& y)
    { return x.ID < y.ID; }
  static bool eq(Payroll& x, Payroll& y)
    { return x.ID == y.ID; }
  static bool gt(Payroll& x, Payroll& y)
    { return x.ID > y.ID; }
};

class NameCompare {
public:
  static bool lt(Payroll& x, Payroll& y)
    { return strcmp(x.name, y.name) < 0; }
  static bool eq(Payroll& x, Payroll& y)
    { return strcmp(x.name, y.name) == 0; }
  static bool gt(Payroll& x, Payroll& y)
    { return strcmp(x.name, y.name) > 0; }
};

int main(int argc, char** argv) {
  Payroll* foo;
}
