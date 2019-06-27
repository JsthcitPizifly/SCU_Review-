#include <iostream.h>
#include <stdlib.h>

#include "book.h"

long fact(int n) {       // Compute n!
  // To fit n! in a long variable, require n <= 12
  Assert((n >= 0) && (n <= 12), "Input out of range");
  if (n <= 1)  return 1; // Base case: return base solution
  return n * fact(n-1);  // Recursive call for n > 1
}

#include "astack.h"

long fact(int n, Stack<int>& S) { // Compute n!
  // To fit n! in a long variable, require n <= 12
  Assert((n >= 0) && (n <= 12), "Input out of range");
  while (n > 1) S.push(n--);  // Load up the stack
  long result = 1;            // Holds final result
  int val;                    // Holds current value
  while(S.pop(val)) result = result * val; // Compute
  return result;
}

int main(int argc, char** argv)
{
  int n;

  Assert(argc == 2, "Usage: fact <n>");

  n = atoi(argv[1]);

  cout << "First, do the recursive version.\n";
  long val = fact(n);
  cout << "The factorial of " << n << " is " << val << endl;

  cout << "\nNow, do the stack-based version.\n";
  AStack<int> fs(n-1);  // Make stack just big enough
  long val2 = fact(n, fs);
  cout << "The factorial of " << n << " is " << val2 << endl;

  return 0;
}
