#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>

#include "book.h"
#include "compare.h"

#include "permute.h"

#include "maxheap.h"

int main(int argc, char** argv) {
  int i, j;
  int n;
  Int* A[20];
  Int* B[20];
  Int C[10] = {73, 6, 57, 88, 60, 34, 83, 72, 48, 85};
  maxheap<Int*, IntsIntsCompare> BH(B, 0, 20);
  maxheap<Int, IntIntCompare> Test(C, 10, 10);

  if (argc != 2) {
    cout << "Usage: heap <heapsize>\n";
    exit(-1);
  }

  n = atoi(argv[1]);
  if (n > 20) {
    cout << "heap size " << n << " too big.\n";
    exit(-1);
  }

  Randomize();

  for (i=0; i<n; i++)
    A[i] = new Int(i);

  permute(A, n);

  cout << "Initial values:\n";
  for (i=0; i<n; i++) {
    cout << A[i] << "  ";
    if (i == 9) cout << "\n";
  }
  cout << "\n\n";

  for (i=0; i<n; i++)
    BH.insert(A[i]);

  for (i=0; i<BH.heapsize(); i++) {
    cout << B[i] << "  ";
    if (i == 9) cout << "\n";
  }
  cout << "\n\n";

  maxheap<Int*, IntsIntsCompare> AH(A, n, 20);
  Int* AHval;

  for (i=0; i<AH.heapsize(); i++) {
    cout << A[i] << "  ";
    if (i == 9) cout << "\n";
  }
  cout << "\n\n";

  AH.removemax(AHval);
  cout << "Max value: " << AHval << "\n";

  for (i=0; i<AH.heapsize(); i++) {
    cout << A[i] << "  ";
    if (i == 9) cout << "\n";
  }
  cout << "\n\n";

  AH.removemax(AHval);
  cout << "Max value: " << AHval << "\n";

  for (i=0; i<AH.heapsize(); i++) {
    cout << A[i] << "  ";
    if (i == 9) cout << "\n";
  }
  cout << "\n\n";

  AH.remove(2, AHval);
  cout << "Remove value: " << AHval << "\n";

  for (i=0; i<AH.heapsize(); i++) {
    cout << A[i] << "  ";
    if (i == 9) cout << "\n";
  }
  cout << "\n";

  for (i=0; i<10; i++)
    cout << C[i] << "  ";
  cout << "\n";

  Int Testval;
  for (j=0; j<10; j++) {
    Test.removemax(Testval);
    for (i=0; i<10; i++)
      cout << C[i] << "  ";
    cout << "\n";
  }

  return 0;
}
