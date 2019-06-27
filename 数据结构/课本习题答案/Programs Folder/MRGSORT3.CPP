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
void mergesort(Elem A[], Elem temp[], int left, int right) {
  if ((right-left) <= THRESHOLD) { // Small list
    inssort<Elem,Comp>(&A[left], right-left+1);
    return;
  }
  int i, j, k, mid = (left+right)/2;
  if (left == right) return;
  mergesort<Elem,Comp>(A, temp, left, mid);
  mergesort<Elem,Comp>(A, temp, mid+1, right);
  // Do the merge operation.  First, copy 2 halves to temp.
  for (i=mid; i>=left; i--) temp[i] = A[i];
  for (j=1; j<=right-mid; j++) temp[right-j+1] = A[j+mid];
  // Merge sublists back to A
  for (i=left,j=right,k=left; k<=right; k++)
    if (temp[i] < temp[j]) A[k] = temp[i++];
    else A[k] = temp[j--];
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  static Elem* temp = NULL;
  if (temp == NULL) temp = new Elem[n];  // Declare temp array
  mergesort<Elem,Comp>(array, temp, 0, n-1);
}

#include "sortmain.cpp"
