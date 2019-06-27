#include <iostream.h>
#include <stdlib.h>

#include "book.h"

long fibr(int n) { // Recursive Fibonacci generator
  Assert((n>0) && (n<47), "Input out of range");
  if ((n == 1) || (n == 2)) return 1; // Base case
  return fibr(n-1) + fibr(n-2);       // Recurse
}

long fibi(int n) { // Iterative Fibonacci generator
  Assert((n>0) && (n<47), "Input out of range");
  long curr, prev;
  if ((n == 1) || (n == 2)) return 1;
  curr = prev = 1;       // curr: current fibi value
  for (int i=3; i<=n; i++) { // Compute next value
    curr = prev + curr;
    prev = curr - prev;  // prev: previous fibi value
  }
  return curr;
}

int main(int argc, char** argv) {
  int n;

  Assert(argc == 2, "Usage: fib <n>");

  n = atoi(argv[1]);

  Settime();
  cout << "Fibi(" << n << ") = " << fibi(n) << endl;
  cout << "Fibi time: " << Gettime() << " seconds.\n";

  Settime();
  cout << "Fibr(" << n << ") = " << fibr(n) << endl;
  cout << "Fibr time: " << Gettime() << " seconds.\n";

  return 0;
}
