#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#include "permute.h"

#define COUNT 100

typedef int Elem;

int main(int argc, char** argv) {
  Elem* A; // The array pointer
  Elem* B; // Second array
  int n;
  int i, j;

  Assert(argc == 2, "Usage: binsimp <size_of_array>");

  n = atoi(argv[1]);
  A = new Elem[n];
  B = new Elem[n];

  Randomize();

  for (i=0; i<n; i++)
    A[i] = i;
  permute(A, n);

  Settime();
  for (j=0; j<COUNT; j++) {

  for (i=0; i<n; i++)
     B[A[i]] = A[i];

  }
  cout << "Time for `fast' binsort (" << COUNT << " runs): "
       << Gettime() << " seconds\n";

  // For "slow" binsort, we first get a benchmark on the time to
  // do permutations.

  Settime();
  for (j=0; j<COUNT; j++) {
    for (i=0; i<n; i++)
      A[i] = i;
    permute(A, n);
  }
  double permtime = Gettime();
  cout << "Time to do " << COUNT << " permutations: "
       << permtime << " seconds\n";

  // Now, we do the binsort.

  Settime();
  for (j=0; j<COUNT; j++) {
    for (i=0; i<n; i++)
      A[i] = i;
    permute(A, n);

  for (i=0; i<n; i++)
     while (A[i] != i)
        swap(A, i, A[i]);

  }
  double slowtime = Gettime();
  cout << "Time for `slow' binsort (" << COUNT << " runs): "
       << slowtime << " seconds\n";
  cout << "Net cost is: " << slowtime - permtime << " seconds\n";

  cout << "Let's check to be sure this works.\n";
  for(i=0; i<10; i++)
    cout << A[i] << "  ";
  cout << endl;
  for(i=0; i<10; i++)
    cout << B[i] << "  ";
  cout << endl;

 return 0;
}
