#include "dictionary.h"

// Dictionary implemented with an unsorted linked list
template <class Key, class Elem, class KEComp, class EEComp>
class ULLdict : public Dictionary<Key, Elem, KEComp, EEComp> {
private:
  LList<Elem>* list;
public:
  ULLdict(int size=DefaultListSize)
    { list = new LList<Elem>(size); }
  ~ULLdict() { delete list; }
  void clear() { list->clear(); }
  bool insert(const Elem& e)
    { return list->append(e); }
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
    list->setStart();
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
