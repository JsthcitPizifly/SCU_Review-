#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#include "hashdict.h"

// Search for the record with Key K
template <class Key, class Elem, class KEComp, class EEComp>
bool hashdict<Key, Elem, KEComp, EEComp>::
hashSearch(const Key& K, Elem& e) const {
  int home;              // Home position for K
  int pos = home = h(K); // Initial posit on probe sequence
  for (int i = 1; !KEComp::eq(K, HT[pos]) &&
                  !EEComp::eq(EMPTY, HT[pos]); i++)
    pos = (home + p(K, i)) % M;  // Next on probe sequence
  if (KEComp::eq(K, HT[pos])) {  // Found it
    e = HT[pos];
    return true;
  }
  else return false;      // K not in hash table
}

int getkey(Int* e) { return e->key(); }
char* getkey(char* e) { return e; }

// Insert e into hash table HT
template <class Key, class Elem, class KEComp, class EEComp>
bool hashdict<Key, Elem, KEComp, EEComp>::
hashInsert(const Elem& e) {
  int home;                      // Home position for e
  int pos = home = h(getkey(e)); // Init probe sequence
  for (int i=1; !(EEComp::eq(EMPTY, HT[pos])); i++) {
    pos = (home + p(getkey(e), i)) % M; // Follow probes
    if (EEComp::eq(e, HT[pos])) return false; // Duplicate
  }
  HT[pos] = e;                   // Insert e
  return true;
}

// Driver class for testing a hash table-based dictionary

int Intkey(Int& e) { return e.key(); }
char* charkey(char*& e) { return e; }

int main(int argc, char** argv) {
  hashdict<int, Int*, intIntsCompare, IntsIntsCompare> dict(100, new Int(-1));
  Int* val;

  dict.insert(new Int(10));
  if (dict.find(10, val))
    cout << "Found value " << val << " to match key value 10\n";
  else
    cout << "Nothing found to match key value 10\n";

  hashdict<char*, char*, CCCompare, CCCompare> Strdict(100, "");
  char* str;

  Strdict.insert("hello");
  if (Strdict.find("hello", str))
    cout << "Found value " << str << " to match key value hello\n";
  else
    cout << "Nothing found to match key value hello\n";
}
