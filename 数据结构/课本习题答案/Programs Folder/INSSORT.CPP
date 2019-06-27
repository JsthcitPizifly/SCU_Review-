#include <iostream.h>
#include <stdlib.h>

#include "book.h"
int comps=0;
int icomps=0;
int qcomps=0;
#include "compare.h"

template <class Elem, class Comp>
void inssort(Elem A[], int n) { // Insertion Sort
  for (int i=1; i<n; i++)       // Insert i'th record
    for (int j=i; (j>0) && (Comp::lt(A[j], A[j-1])); j--)
      swap(A, j, j-1);
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  inssort<Elem,Comp>(array, n);
}

#include "sortmain.cpp"
