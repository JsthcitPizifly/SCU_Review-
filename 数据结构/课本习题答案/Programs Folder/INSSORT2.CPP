#include <iostream.h>
#include <stdlib.h>

#include "book.h"
int comps=0;
int icomps=0;
int qcomps=0;
#include "compare.h"

#include "inssort2.x"

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  inssort<Elem,Comp>(array, n);
}

#include "sortmain.cpp"
