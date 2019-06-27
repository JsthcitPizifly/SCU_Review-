#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

// Modified version of Insertion Sort for varying increments
template <class Elem, class Comp>
void inssort2(Elem A[], int n, int incr) {
  for (int i=incr; i<n; i+=incr)
    for (int j=i;
         (j>=incr) && (Comp::lt(A[j], A[j-incr])); j-=incr)
      swap(A, j, j-incr);
}

template <class Elem, class Comp>
void shellsort(Elem A[], int n) { // Shellsort
  for (int i=n/2; i>2; i/=2)      // For each increment
    for (int j=0; j<i; j++)       // Sort each sublist
      inssort2<Elem,Comp>(&A[j], n-j, i);
  inssort2<Elem,Comp>(A, n, 1);
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  shellsort<Elem,Comp>(array, n);
}

#include "sortmain.cpp"
