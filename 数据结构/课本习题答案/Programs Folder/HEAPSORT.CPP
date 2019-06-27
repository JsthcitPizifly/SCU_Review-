#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#include "maxheap.h"

template <class Elem, class Comp>
void heapsort(Elem A[], int n) { // Heapsort
  Elem mval;
  maxheap<Elem,Comp> H(A, n, n); // Build the heap
  for (int i=0; i<n; i++)        // Now sort
    H.removemax(mval); // Removemax places max at end
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
 heapsort<Elem,Comp>(array, n);
}

#include "sortmain.cpp"
