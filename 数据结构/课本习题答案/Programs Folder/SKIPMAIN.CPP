#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#include "skiplist.h"

// Warning: This has horrible memory leaks.
// Everytime it does a remove to "it",
// the next time "it" gets used, that previous
// Int object gets clobbered.
int main()
{
  SkipList<int, Int*, intIntsCompare, IntsIntsCompare > sl;
  Int* it;

  cout << "Size: " << sl.size() << "\n";
  sl.insert(new Int(100));
  sl.print();
  cout << "Size: " << sl.size() << "\n";
  sl.remove(10, it);
  sl.print();
  cout << "Size: " << sl.size() << "\n";
  sl.clear();
  cout << "Size: " << sl.size() << "\n";
  sl.insert(new Int(15));
  cout << "Size: " << sl.size() << "\n";
  if (sl.find(20, it))
    cout << "Found " << it << endl;
  else cout << "No key 20\n";
  if (sl.find(15, it))
    cout << "Found " << it << endl;
  else cout << "No key 15\n";
  sl.print();
  if (sl.remove(20, it))
    cout << "Removed " << it << endl;
  else cout << "No key 20\n";
  cout << "Now, insert 20\n";
  sl.insert(new Int(20));
  sl.print();
  if (sl.remove(20, it))
    cout << "Removed " << it << endl;
  else cout << "No key 20\n";
  sl.print();
  sl.insert(new Int(700));
  cout << "Size: " << sl.size() << "\n";
  sl.insert(new Int(350));
  sl.insert(new Int(201));
  sl.insert(new Int(170));
  sl.insert(new Int(151));
  sl.insert(new Int(190));
  sl.insert(new Int(1000));
  sl.insert(new Int(900));
  sl.insert(new Int(950));
  sl.insert(new Int(10));
  sl.print();
  if (sl.find(1000, it))
    cout << "Found " << it << endl;
  else cout << "No key 1000\n";
  if (sl.find(999, it))
    cout << "Found " << it << endl;
  else cout << "No key 999\n";
  if (sl.find(20, it))
    cout << "Found " << it << endl;
  else cout << "No key 20\n";
  cout << "Now do some delete tests.\n";
  if (sl.remove(15, it))
    cout << "Removed " << it << endl;
  else cout << "No key 15\n";
  sl.print();
  if (sl.remove(151, it))
    cout << "Removed " << it << endl;
  else cout << "No key 151\n";
  sl.print();
  if (sl.remove(151, it))
    cout << "Removed " << it << endl;
  else cout << "No key 151\n";
  if (sl.remove(700, it))
    cout << "Removed " << it << endl;
  else cout << "No key 700\n";
  sl.print();
  sl.clear();
  sl.print();
  cout << "Size: " << sl.size() << "\n";

  cout << "Finally, test iterator\n";
  sl.insert(new Int(3500));
  sl.insert(new Int(2010));
  sl.insert(new Int(1700));
  sl.insert(new Int(1510));
  sl.insert(new Int(1900));
  sl.insert(new Int(10000));
  sl.insert(new Int(9000));
  sl.insert(new Int(9500));
  sl.insert(new Int(100));
  sl.print();
  while (sl.size() > 0) {
    if (!sl.removeAny(it)) break;
    cout << it << " ";
  }
  cout << "\n";
  return(0);
}
