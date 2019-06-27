#include "dictionary.h"

// Dictionary implemented with a hash table
template <class Key, class Elem, class KEComp, class EEComp>
class hashdict : public Dictionary<Key,Elem,KEComp,EEComp> {
private:
  Elem* HT;     // The hash table
  int M;        // Size of HT
  int currcnt;  // The current number of elements in HT
  Elem EMPTY;   // User-supplied value for an empty slot
  int p(Key K, int i) const // Probe using linear probing
    { return i; }
  int h(int x) const { return x % M; } // Poor hash function
  int h(char* x) const { // Hash function for character keys
    int i, sum;
    for (sum=0, i=0; x[i] != '\0'; i++) sum += (int) x[i];
    return(sum % M);
  }
  bool hashInsert(const Elem&);
  bool hashSearch(const Key&, Elem&) const;
public:
  hashdict(int sz, Elem e){ // e defines an EMPTY slot
    M = sz;  EMPTY = e;
    currcnt = 0;  HT = new Elem[sz]; // Make HT of size sz
    for (int i=0; i<M; i++) HT[i] = EMPTY; // Initialize HT
  }
  ~hashdict() { delete HT; }
  void clear() { // Clear the dictionary
    for (int i=0; i<M; i++) HT[i] = EMPTY;
    currcnt = 0;
  }
  bool insert(const Elem& e) { // Insert e into dictionary
    if (currcnt == M) return false;
    if (hashInsert(e)) {
      currcnt++;
      return true;
    }
    else return false;
  }
  bool remove(const Key& K, Elem& e) {} // Not implemented
  bool removeAny(Elem& e) {  // Remove the first element
    for (int i=0; i<M; i++)
      if (!EEComp::eq(EMPTY, HT[i])) {
        e = HT[i];  HT[i] = EMPTY;
        currcnt--;  return true;
      }
    return false;
  }
  bool find(const Key& K, Elem& e) const
    { return hashSearch(K, e); }
  int size() { return currcnt; } // Number stored in table
};
