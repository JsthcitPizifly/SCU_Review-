#include <iostream.h>
#include <stdlib.h>
#include "book.h"
#include "astack.h"

typedef int Pole;
#define move(X, Y) cout << "Move " << (X) << " to " << (Y) << endl

void TOH(int n, Pole start, Pole goal, Pole tmp) {
  if (n == 0) return;          // Base case
  TOH(n-1, start, tmp, goal);  // Recursive call: n-1 rings
  move(start, goal);           // Move one disk
  TOH(n-1, tmp, goal, start);  // Recursive call: n-1 rings
}

enum TOHop { DOMOVE, DOTOH };

class TOHobj {
public:
  TOHop op;
  int num;
  Pole start, goal, tmp;

  // DOTOH operation
  TOHobj(int n, Pole s, Pole g, Pole t) {
    op = DOTOH; num = n;
    start = s; goal = g; tmp = t;
  }

  TOHobj(Pole s, Pole g) // DOMOVE operation
    { op = DOMOVE; start = s; goal = g; }
};

void TOH(int n, Pole start, Pole goal, Pole tmp,
         Stack<TOHobj*>& S) {
  S.push(new TOHobj(n, start, goal, tmp)); // Initial
  TOHobj* t;
  while (S.pop(t)) {       // Grab next task
    if (t->op == DOMOVE)   // Do a move
      move(t->start, t->goal);
    else if (t->num > 0) { // Do 3 statements of
	                   // recursion (reversed)
      int num = t->num;
      Pole tmp = t->tmp;  Pole goal = t->goal;
      Pole start = t->start;
      S.push(new TOHobj(num-1, tmp, goal, start));
      S.push(new TOHobj(start, goal));
      S.push(new TOHobj(num-1, start, tmp, goal));
    }
    delete t; // Must delete the TOHobj we made
  }
}

int main(int argc, char** argv) {

  Assert(argc == 2, "Usage: toh <num_of_disks>");

  int n = atoi(argv[1]);
  cout << "Doing recursive version on " << n << " disks\n";
  TOH(n, 1, 3, 2);

  cout << endl;

  AStack<TOHobj*> S(2*n+1); // Make stack with just enough room
  cout << "Now, do non-recursive version\n";
  TOH(n, 1, 3, 2, S);

  return 0;
}
