// This file includes all of the pieces of the skiplist class implementation

#define MAXLEVEL 9

#include "dictionary.h"

template <class Elem>
class SkipNode {
public:
  int myLevel;
  Elem value;
  SkipNode** forward;
  SkipNode() {
    myLevel = MAXLEVEL;
    value = (Elem)NULL;
    forward = new SkipNode* [MAXLEVEL+1];
    for (int i=0; i<=MAXLEVEL; i++)
      forward[i] = NULL;
  }
  SkipNode(Elem r, int level) {
    myLevel = level;
    value = r;
    forward = new SkipNode* [level+1];
    for (int i=0; i<=level; i++)
      forward[i] = NULL;
  }
  ~SkipNode() { delete [] forward; }
};


template <class Key, class Elem, class KEComp, class EEComp>
class SkipList : public Dictionary<Key, Elem, KEComp, EEComp> {
private:
  SkipNode<Elem>* head;
  int level;
  int reccount;
  void AdjustHead(int& level) {level = MAXLEVEL;}
public:
  SkipList() {
    head = new SkipNode<Elem>;
    level = MAXLEVEL; reccount = 0;
  }
  void clear() { cout << "Clear not implemented\n"; }
  bool find(const Key& K, Elem& e) const;
  bool insert(const Elem& e);
  bool remove(const Key& K, Elem& e) { cout << "Remove not implemented\n"; }
  bool removeAny(Elem& e) { cout << "Removeany not implemented\n"; return false; }
  int size() { return reccount; }
  void print() const {
    for (SkipNode<Elem>* temp = head; temp!= NULL; temp = temp->forward[0]) {
      if (temp->value != NULL)
        cout << "temp->value is " << temp->value << "\n";
      for(int i=0; i<=temp->myLevel; i++)
        if (temp->forward[i] == NULL)
          cout << " point to NULL\n";
        else
          cout << " point to " << temp->forward[i]->value << "\n";
    }
  }
};

// Pick a level using an exponential distribution
int randomLevel(void) {
  int level;
  for (level=0; Random(2) == 0; level++); // Do nothing
  return level;
}

template <class Key, class Elem, class KEComp, class EEComp>
bool SkipList<Key, Elem, KEComp, EEComp>::
find(const Key& K, Elem& e) const {
  SkipNode<Elem> *x = head;             // Dummy header node
  for (int i=level; i>=0; i--)
    while ((x->forward[i] != NULL) &&
           KEComp::gt(K, x->forward[i]->value))
      x = x->forward[i];
  x = x->forward[0];  // Move to actual record, if it exists
  if ((x != NULL) && KEComp::eq(K, x->value)) {
    e = x->value;
    return true;
  }
  else return false;
}

template <class Key, class Elem, class KEComp, class EEComp>
bool SkipList<Key, Elem, KEComp, EEComp>::
insert(const Elem& val) {
  int i;
  SkipNode<Elem> *x = head;   // Start at header node
  int newLevel = randomLevel(); // Select level for new node
  if (newLevel > level) {     // New node is deepest in list
    AdjustHead(newLevel);     // Add null pointers to header
    level = newLevel;
  }
  SkipNode<Elem>* update[level+1]; // Track ends of levels
  for(i=level; i>=0; i--) { // Search for insert position
    while((x->forward[i] != NULL) &&
          EEComp::lt(x->forward[i]->value, val))
      x = x->forward[i];
    update[i] = x;          // Keep track of end at level i
  }
  x = new SkipNode<Elem>(val, newLevel); // Create new node
  for (i=0; i<=newLevel; i++) { // Splice into list
    x->forward[i] = update[i]->forward[i]; // Where x points
    update[i]->forward[i] = x;             // Where y points
  }
  reccount++;
}
