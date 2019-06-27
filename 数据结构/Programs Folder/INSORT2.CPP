#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#include "inssort2.x"

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  inssort<Elem,Comp>(array, n);
}

#include "sortmain.cpp"
