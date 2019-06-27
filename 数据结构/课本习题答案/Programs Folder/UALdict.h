#include "dictionary.h"

// Dictionary implemented with an unsorted array-based list
template <class Key, class Elem, class KEComp, class EEComp>
class UALdict : public Dictionary<Key,Elem,KEComp,EEComp> {
private:
  AList<Elem>* list;
public:
  UALdict(int size=DefaultListSize)
    { list = new AList<Elem>(size); }
  ~UALdict() { delete list; }
  void clear() { list->clear(); }
  bool insert(const Elem& e) { return list->append(e); }
  bool remove(const Key& K, Elem& e) {
    for(list->setStart(); list->getValue(e); list->next())
      if (KEComp::eq(K, e)) {
        list->remove(e);
        return true;
      }
    return false;
  }
  bool removeAny(Elem& e) {
    if (size() == 0) return false;
    list->setEnd();
    list->prev();
    list->remove(e);
    return true;
  }
  bool find(const Key& K, Elem& e) const {
    for(list->setStart(); list->getValue(e); list->next())
      if (KEComp::eq(K, e)) return true;
    return false;
  }
  int size()
    { return list->leftLength() + list->rightLength(); }
};
