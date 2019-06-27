#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

int POW2[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};

#define pow2(X) POW2[X]

template <class Elem, class Comp>
void radix(Elem A[], Elem B[],
           int n, int k, int r, int cnt[]) {
  // cnt[i] stores number of records in bin[i]
  int j;
  for (int i=0, rtok=1; i<k; i++, rtok*=r) { // For k digits
    for (j=0; j<r; j++) cnt[j] = 0;     // Initialize cnt

    // Count the number of records for each bin on this pass
    for (j=0; j<n; j++) cnt[(A[j]/rtok)%r]++;

    // Index B: cnt[j] will be index for last slot of bin j.
    for (j=1; j<r; j++) cnt[j] = cnt[j-1] + cnt[j];

    // Put records into bins, work from bottom of each bin.
    // Since bins fill from bottom, j counts downwards
    for (j=n-1; j>=0; j--) B[--cnt[(A[j]/rtok)%r]] = A[j];

    for (j=0; j<n; j++) A[j] = B[j];    // Copy B back to A
  }
}

template <class Elem, class Comp>
void sort(Elem* array, int n) {
  static Elem* temp = NULL;
  static int* cnt = NULL;
  if (THRESHOLD == 0) {
	cout << "Need to set THRESHOLD\n";
	exit(0);
  }
  if (temp == NULL) temp = new Elem[n];  // Declare temp array
  if (cnt == NULL) cnt = new int[pow2(THRESHOLD)];  // Declare temp array
  radix<Elem,Comp>(array, temp, n, (sizeof(Elem) * 8)/THRESHOLD,
                   pow2(THRESHOLD), cnt);
}

#include "sortmain.cpp"
