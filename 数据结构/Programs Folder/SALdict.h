#include "dictionary.h"

// Dictionary implemented with a sorted array-based list
template <class Key, class Elem, class KEComp, class EEComp>
class SALdict : public Dictionary<Key,Elem,KEComp,EEComp> {
private:
  SAList<Elem, EEComp>* list;
public:
  SALdict(int size=DefaultListSize)
    { list = new SAList<Elem, EEComp>(size); }
  ~SALdict() { delete list; }
  void clear() { list->clear(); }
  bool insert(const Elem& e)
    { return list->insert(e); }
  bool remove(const Key& K, Elem& e) {
    for (list->setStart(); list->getValue(e); list->next())
      if (KEComp::eq(K, e)) {  // Sequential search
        list->remove(e);
        return true;
      }
    return false;
  }
  bool removeAny(Elem& e) {
    if (size() == 0) return false;
    list->setEnd();
    list->prev(); // Go one from end
    list->remove(e);
    return true;
  }
  bool find(const Key& K, Elem& e) const {
    int l = -1;
    int r = list->leftLength() + list->rightLength();
    while (l+1 != r) { // Stop when l and r meet
      int i = (l+r)/2; // Check middle of remaining subarray
      list->setPos(i);
      list->getValue(e);
      if (KEComp::lt(K, e)) r = i; // In left half
      if (KEComp::eq(K, e)) return true; // Found it
      if (KEComp::gt(K, e)) l = i; // In right half
    }
    return false;
  }
  int size()
    { return list->leftLength() + list->rightLength(); }
};
