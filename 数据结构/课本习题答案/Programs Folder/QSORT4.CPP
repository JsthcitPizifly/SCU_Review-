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

template <class Elem, class Comp>
void qsort(Elem array[], int i, int j) {
  static int stack[200];
  int top = -1;
  Elem pivot;
  int pivotindex, l, r;

  stack[++top] = i;
  stack[++top] = j;

  while (top > 0) {
    // Pop stack
    j = stack[top--];
    i = stack[top--];

    // Findpivot
    pivotindex = (i+j)/2;
    pivot = array[pivotindex];
    swap(array, pivotindex, j); // stick pivot at end

    // Partition
    l = i-1;
    r = j;
    do {
      while (Comp::lt(array[++l], pivot));
      while (r && Comp::gt(array[--r], pivot));
      swap(array, l, r);
    } while (l < r);
    swap(array, l, r);          // Undo final swap
    swap(array, l, j);          // Put pivot value in place

    // Load up stack.  l is pivot point.
    if ((l-1-i) > THRESHOLD) {
      stack[++top] = i;
      stack[++top] = l-1;
    }
    if ((j-l-1) > THRESHOLD) {
      stack[++top] = l+1;
      stack[++top] = j;
    }
  }
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  qsort<Elem,Comp>(array, 0, n-1);
  inssort<Elem,Comp>(array, n);      // Final Insertion Sort
}

#include "sortmain.cpp"
