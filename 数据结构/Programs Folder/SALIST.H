// Sorted array-based list
template <class Elem, class Compare>
class SAList: protected AList<Elem> {
public:
  SAList(int size=DefaultListSize) : AList<Elem>(size) {}
  ~SAList() {}                    // Destructor
  AList<Elem>::clear;  // Expose AList clear method
  // Redefine insert function to keep values sorted
  bool insert(const Elem& item) { // Insert at right
    Elem curr;
    for (setStart(); getValue(curr); next())
      if(!Compare::lt(curr, item)) break;
    return AList<Elem>::insert(item);
  }
  // All remaining methods are exposed from AList
  AList<Elem>::remove;
  AList<Elem>::setStart;
  AList<Elem>::setEnd;
  AList<Elem>::prev;
  AList<Elem>::next;
  AList<Elem>::leftLength;
  AList<Elem>::rightLength;
  AList<Elem>::setPos;
  AList<Elem>::getValue;
  AList<Elem>::print;
};
