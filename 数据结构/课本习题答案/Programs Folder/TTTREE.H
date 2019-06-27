// Two-three tree implementation for the Dictionary ADT
template <class Key, class Elem, class KEComp, class EEComp>
class TTTree : public Dictionary<Key, Elem, KEComp, EEComp> {
public:
  TTTree();
  ~TTTree();
  void clear();
  bool insert(const Elem&);
  bool remove(const Key&, Elem&);
  bool removeAny(Elem&);
  bool find(const Key&, Elem&) const;
  int size();
  void print() const;
};
