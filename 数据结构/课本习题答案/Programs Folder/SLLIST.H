template <class Elem, class Compare>
class SLList: protected LList<Elem> {
public:
  SLList(int size=DefaultListSize) : LList<Elem>(size) {}
  ~SLList() {}                  // Destructor
  LList<Elem>::clear;
  bool insert(const Elem& item) { // Insert at right
    Elem curr;
    for (setStart(); getValue(curr); next())
      if(!Compare::lt(curr, item)) break;
    return LList<Elem>::insert(item);
  }
  LList<Elem>::remove;
  LList<Elem>::setStart;
  LList<Elem>::setEnd;
  LList<Elem>::prev;
  LList<Elem>::next;
  LList<Elem>::leftLength;
  LList<Elem>::rightLength;
  LList<Elem>::setPos;
  LList<Elem>::getValue;
  LList<Elem>::print;
};
