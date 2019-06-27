#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

template <class Elem, class Comp>
void mergesort(Elem A[], Elem temp[], int left, int right) {
  int mid = (left+right)/2;
  if (left == right) return;        // List of one element
  mergesort<Elem,Comp>(A, temp, left, mid);
  mergesort<Elem,Comp>(A, temp, mid+1, right);
  for (int i=left; i<=right; i++)   // Copy subarray to temp
    temp[i] = A[i];
  // Do the merge operation back to A
  int i1 = left; int i2 = mid + 1;
  for (int curr=left; curr<=right; curr++) {
    if (i1 == mid+1)      // Left sublist exhausted
      A[curr] = temp[i2++];
    else if (i2 > right)  // Right sublist exhausted
      A[curr] = temp[i1++];
    else if (Comp::lt(temp[i1], temp[i2]))
      A[curr] = temp[i1++];
    else A[curr] = temp[i2++];
  }
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  static Elem* temp = NULL;
  if (temp == NULL) temp = new Elem[n];  // Declare temp array
  mergesort<Elem,Comp>(array, temp, 0, n-1);
}

#include "sortmain.cpp"
