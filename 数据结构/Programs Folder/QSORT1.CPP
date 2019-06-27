#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

template <class Elem> int findpivot(Elem A[], int i, int j)
  { return (i+j)/2; }

template <class Elem, class Comp>
int partition(Elem A[], int l, int r, Elem& pivot) {
  do {             // Move the bounds inward until they meet
    while (Comp::lt(A[++l], pivot));     // Move l right and
    while ((r != 0) && Comp::gt(A[--r], pivot)); // r left
    swap(A, l, r);              // Swap out-of-place values
  } while (l < r);              // Stop when they cross
  swap(A, l, r);                // Reverse last, wasted swap
  return l;      // Return first position in right partition
}

template <class Elem, class Comp>
void qsort(Elem A[], int i, int j) { // Quicksort
  if (j <= i) return; // Don't sort 0 or 1 Elem
  int pivotindex = findpivot(A, i, j);
  swap(A, pivotindex, j);    // Put pivot at end
  // k will be the first position in the right subarray
  int k = partition<Elem,Comp>(A, i-1, j, A[j]);
  swap(A, k, j);             // Put pivot in place
  qsort<Elem,Comp>(A, i, k-1);
  qsort<Elem,Comp>(A, k+1, j);
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  qsort<Elem,Comp>(array, 0, n-1);
}

#include "sortmain.cpp"
