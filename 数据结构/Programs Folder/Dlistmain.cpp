#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#include "dlink.h"

#include "dlist.h"

// Full template version of find function
template <class Compare, class Elem, class Key>
bool findt(List<Elem>& L, Key K, Elem& it) {
  while (L.rightLength() > 0) {
    L.getValue(it);
    if (Compare::eq(K, it)) return true;
    else L.next();
  }
  return false;  // Value not found
}

// Test function for list iterator example
void DoSomething(int it) {}

// Specialization for ints, used in the book.
// The int version is used there so that the issues of comparators
// and keys can be deferred.
// Return true iff K is in list
bool find(List<int>& L, int K) {
  int it;
  for (L.setStart(); L.getValue(it); L.next())
    if (K == it) return true;  // Found it
  return false;                // K not found
}


template <class E1, class E2, class ListImp>
void ListTest(List<E1>& L1, List<E1>& L2, List<E2>& L3) {
  E1 temp1;
  // Test a bunch of list operations
  L2.append(new Int(1));
  L2.remove(temp1);
  L2.print();
  L2.append(new Int(10));
  L2.print();
  L2.append(new Int(20));
  L2.append(new Int(15));
  L2.print();
  L1.setStart();
  L1.insert(new Int(39));
  L1.next();
  L1.insert(new Int(9));
  L1.insert(new Int(5));
  L1.append(new Int(4));
  L1.append(new Int(3));
  L1.append(new Int(2));
  L1.append(new Int(1));
  L1.print();
  L1.setStart();
  if (! findt<intIntsCompare>(L1, 3, temp1))
    cout << "Value 3 not found.\n";
  else cout << "Found " << temp1 << endl;
  L1.print();
  if (! findt<intIntsCompare>(L1, 3, temp1))
    cout << "Value 3 not found.\n";
  else cout << "Found " << temp1 << endl;
  L1.print();
  L1.setStart();
  if (! findt<intIntsCompare>(L1, 29, temp1))
    cout << "Value 29 not found.\n";
  else cout << "Found " << temp1 << endl;
  if (! findt<intIntsCompare>(L1, 5, temp1))
    cout << "Value 5 not found.\n";
  else cout << "Found " << temp1 << endl;
  L1.setStart();
  if (! findt<intIntsCompare>(L1, 5, temp1))
    cout << "Value 5 not found.\n";
  else cout << "Found " << temp1 << endl;

  L2.setStart();
  if (!L2.getValue(temp1))
    cout << "L2: Nothing found\n";
  else cout << "L2 curr: " << temp1 << endl;
  cout << "L1: ";  L1.print();
  cout << "Size: " << L1.rightLength() + L1.leftLength() << endl;
  cout << "L2: ";  L2.print();
  cout << "L3: ";  L3.print();
  L3.insert(3);
  cout << "L3: ";  L3.print();
  L2.setStart();
  L2.next();
  L1.setStart();
  if (!L1.getValue(temp1))
    cout << "L1: Nothing found\n";
  else cout << "L1 curr: " << temp1 << endl;
  if (!L1.remove(temp1))
    cout << "Nothing to remove!\n";
  else cout << " Deleted " << temp1 << endl;
  L1.insert(new Int(42));
  L1.print();
  L1.setStart();
  if (! findt<intIntsCompare>(L1, 4, temp1))
    cout << "Value 4 not found.\n";
  else cout << "Found " << temp1 << endl;
  L2.setStart();
  if (!L2.remove(temp1))
    cout << "Nothing to remove!\n";
  else cout << " Deleted " << temp1 << endl;
  if (!L2.remove(temp1))
    cout << "Nothing to remove!\n";
  else cout << " Deleted " << temp1 << endl;
  L2.print();
  cout << "Size: " << L2.rightLength() + L2.leftLength() << endl;;
  L2.clear();  L2.print();
  cout << "Size: " << L2.rightLength() + L2.leftLength() << endl;
  L2.append(new Int(5));  L2.print();
  L2.setEnd();
  if (!L2.getValue(temp1))
    cout << "L2: Nothing found\n";
  else cout << "L2 curr: " << temp1 << endl;
  if (!L2.remove(temp1))
    cout << "Nothing to remove!\n";
  else cout << "Deleted " << temp1 << endl;
  cout << "Start a new round\n";
  L2.clear();
  L2.print();
  L2.setStart();
  L2.insert(new Int(1));
  L2.print();
  L2.insert(new Int(2));
  L2.print();
  L2.setPos(2);
  L2.insert(new Int(3));
  cout << "L2: "; L2.print();
  cout << "L1: "; L1.print();
  L1.remove(temp1);
  cout << "L1: "; L1.print();
  L2.clear();

  cout << "Now, test int find\n";
  int it;
  ListImp MyList;
  MyList.insert(3);
  if (! find(MyList, 3))
    cout << "Value 3 not found.\n";
  else cout << "Found 3\n";
  if (! find(MyList, 13))
    cout << "Value 13 not found.\n";
  else cout << "Found 13\n";

  cout << "Now, test the simple list iterator example.\n";
  for (MyList.setStart(); MyList.getValue(it); MyList.next())
    DoSomething(it);

  cout << "That is all.\n";
}

// Driver class for list implementations

// Main routine for array-based list driver class
int main(int argc, char** argv) {
  // Declare some sample lists
  LList<Int*> L1;
  LList<Int*> L2(15);
  LList<Int> L3;

  ListTest<Int*, Int, LList<int> >(L1, L2, L3);
  return 0;
}
