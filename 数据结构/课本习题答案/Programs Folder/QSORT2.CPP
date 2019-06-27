#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

template <class Elem, class Comp>
void inssort(Elem A[], int n) { // Insertion Sort
  for (int i=1; i<n; i++)       // Insert i'th record
    for (int j=i; (j>0) && (Comp::lt(A[j], A[j-1])); j--)
      swap(A, j, j-1);
}

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
void qsort(Elem array[], int i, int j) {
  if ((j-i) <= THRESHOLD) return; // Don't sort short list
  int pivotindex = findpivot(array, i, j);
  swap(array, pivotindex, j); // stick pivot at end
  int k = partition<Elem,Comp>(array, i-1, j, array[j]);
  swap(array, k, j);          // Put pivot value in place
  qsort<Elem,Comp>(array, i, k-1);
  qsort<Elem,Comp>(array, k+1, j);
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  qsort<Elem,Comp>(array, 0, n-1);
  inssort<Elem,Comp>(array, n); // Cleanup sort
}

#include "sortmain.cpp"
