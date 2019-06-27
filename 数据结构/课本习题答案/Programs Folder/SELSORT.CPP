#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

template <class Elem, class Comp>
void selsort(Elem A[], int n) { // Selection Sort
  for (int i=0; i<n-1; i++) {   // Select i'th record
    int lowindex = i;           // Remember its index
    for (int j=n-1; j>i; j--)   // Find the least value
      if (Comp::lt(A[j], A[lowindex]))
	lowindex = j;           // Put it in place
    swap(A, i, lowindex);
  }
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  selsort<Elem,Comp>(array, n);
}

#include "sortmain.cpp"
