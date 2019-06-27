#include <iostream.h>
#include <stdlib.h>
#include "book.h"
#include "compare.h"

// This version is generalized to use a template for elements,
// and a comparator.
// Return the position of an element in a sorted array of
// size n with key value K.  If none exist, return n.
template<class Compare, class Elem, class Key>
int binaryt(Elem array[], int n, Key K) {
  int l = -1;
  int r = n;     // l and r are beyond the bounds of array
  while (l+1 != r) {   // Stop when l and r meet
    int i = (l+r)/2;   // Check middle of remaining subarray
    if (Compare::lt(K, array[i])) r = i;    // In left half
    if (Compare::eq(K, array[i])) return i; // Found it
    if (Compare::gt(K, array[i])) l = i;    // In right half
  }
  return n; // Search value not in array
}

// This is the version that appears in the book.
// It works on an integer array.
// Return the position of an element in a sorted array of
// size n with value K.  If none exist, return n.
int binary(int array[], int n, int K) {
  int l = -1;
  int r = n;          // l and r are beyond array bounds
  while (l+1 != r) {  // Stop when l and r meet
    int i = (l+r)/2;  // Check middle of remaining subarray
    if (K < array[i]) r = i;     // In left half
    if (K == array[i]) return i; // Found it
    if (K > array[i]) l = i;     // In right half
  }
  return n; // Search value not in array
}

// Test program to test out both the specific and the generic bsearch
// algorithm.
int main(int argc, char** argv) {
  int i, numvals, K, result;
  int* A;
  Int* B;
  Int** C;

  Assert(argc == 3, "Usage: bsearch <num_values> <search_key>");

  numvals = atoi(argv[1]);
  K = atoi(argv[2]);

  // Create and initialize array
  A = new int[numvals];
  B = new Int[numvals];
  C = new Int*[numvals];
	
  for (i=0; i<numvals; i++)
    A[i] = i;

  // Call to specialized implementation (integer only)
  // The template type is bogus to keep the VC++ compiler happy
  // (it insists on having something to resolve the comparator parameter).
  // But, it upsets the g++ compiler.  The g++ compiler doesn't appear
  // to recognize the specialization
  result = binary(A, numvals, K);
  if (result == numvals)
    cout << "Binary search was unsuccessful\n";
  else
    cout << "Binary search returns " << result << "\n";

  for (i=0; i<numvals; i++)
    { A[i] = i; B[i] = i; C[i] = new Int(i); }

  // This also calls the integer-only specialized form,
  // but it would work equally well if the specialization
  // didn't exist.
  result = binaryt<intintCompare>(A, numvals, K);
  if (result == numvals)
    cout << "Binary search was unsuccessful\n";
  else
    cout << "Binary search returns " << result << "\n";

  // Call to generalized template form
  result = binaryt<intIntCompare>(B, numvals, K);
  if (result == numvals)
    cout << "Binary search was unsuccessful\n";
  else
    cout << "Binary search returns " << result << "\n";

  // Call to generalized template form
  result = binaryt<intIntsCompare>(C, numvals, K);
  if (result == numvals)
    cout << "Binary search was unsuccessful\n";
  else
    cout << "Binary search returns " << result << "\n";


  return  0;
}
