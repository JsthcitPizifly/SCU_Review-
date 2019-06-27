#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

template <class Elem, class Comp>
void bubsort(Elem A[], int n) { // Bubble Sort
  for (int i=0; i<n-1; i++)     // Bubble up i'th record
    for (int j=n-1; j>i; j--)
      if (Comp::lt(A[j], A[j-1]))
        swap(A, j, j-1);
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  bubsort<Elem,Comp>(array, n);
}

#include "sortmain.cpp"
