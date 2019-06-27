// Timing test for freelists: Non freelist version

#include <iostream.h>
#include <stdlib.h>

#include "book.h"

// Include the link template class -- non freelist
#include "link.h"

int main(int argc, char** argv) {
  Link<int>* test1;
  Link<Int*>* test2;
  Link<Int>* test3;
  Int* dum = new Int(10);

  Assert(argc == 2, "Usage: freetest <number_of_iterations>");

  int count = atol(argv[1]);
  int i;
  double time;

  test1 = new Link<int>(10);
  test2 = new Link<Int*>(dum);
  delete test1;
  delete test2;

  Settime();
  for (i=0; i<count; i++) {
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
    test1 = new Link<int>(i);
    delete test1;
  }
  time = Gettime();

  cout << "Time for int: " << time << endl;

  Settime();
  for (i=0; i<count; i++) {
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
    test2 = new Link<Int*>(dum);
    delete test2;
  }
  time = Gettime();

  cout << "Time for int: " << time << endl;

  Settime();
  for (i=0; i<count; i++) {
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
    test3 = new Link<Int>(i);
    delete test3;
  }
  time = Gettime();

  cout << "Time for int: " << time << endl;

}
