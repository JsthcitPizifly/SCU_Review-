#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#include "lqueue.h"

template <class El> void QueueTest(Queue<El>& Que) {
  El temp;

  // Test a bunch of queue operations
  Que.enqueue(10);
  Que.enqueue(20);
  Que.enqueue(15);
  cout << "Length is " << Que.length() << endl;
  if (Que.frontValue(temp))
    cout << "Front is " << temp << endl;
  else cout << "Nothing in queue\n";
  while(Que.dequeue(temp))
    cout << temp << " ";
  cout << endl;
  cout << "Length is " << Que.length() << endl;
  if (Que.frontValue(temp))
    cout << "Front is " << temp << endl;
  else cout << "Nothing in queue\n";
  Que.clear();
  cout << "Length is " << Que.length() << endl;
  cout << "That is all.\n\n";
}

// Driver class for queue implementations

// Main routine for array-based queue driver class
int main(int argc, char** argv) {
  // Declare some sample lists
  LQueue<Int> S1;
  LQueue<Int*> S2(15);
  LQueue<int> S3;

  QueueTest<Int>(S1);
  QueueTest<int>(S3);
  return 0;
}
