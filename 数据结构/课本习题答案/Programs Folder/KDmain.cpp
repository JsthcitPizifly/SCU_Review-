#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#include "binnode.h"

bool InCircle(int* c1, int* c2, int dim, int radius)
  { return true; }

class CityRec {
private:
  int pos[2];
public:
    int* coord() { return pos; }
};

void printout(CityRec& e) {};


template <class Elem> class KD {
private:
  BinNode<Elem>* root;
  int D; // Dimension of the key
  // TRUE iff two coords are equal
    bool EqualCoord(int*, int*) const {}
  bool findhelp(BinNode<Elem>*, int*, Elem&, int) const;
  BinNode<Elem>* findmin(BinNode<Elem>*, int, int) const;
  void regionhelp(BinNode<Elem>*, int*, int, int) const;
public:
  KD(int Din) { root = NULL; D = Din; }  // Constructor
  bool remove(int* coord, Elem& e)
    { findmin(root, 0, 0); }
  bool find(Elem& e, int* coord) const
    { return findhelp(root, coord, e, 0); }
  void regionsearch(int* coord, int radius) const
    { regionhelp(root, coord, radius, 0); }
};
  
template <class Elem> bool KD<Elem>::
findhelp(BinNode<Elem>* subroot, int* coord,
         Elem& e, int discrim) const {
  if (subroot == NULL) return false; // Empty tree
  int* currcoord;
  currcoord = (subroot->val()).coord();
  if (EqualCoord(currcoord, coord)) { // Found it
    e = subroot->val();
    return true;
  }
  if (currcoord[discrim] < coord[discrim])
    return findhelp(subroot->left(),coord,e,(discrim+1)%D);
  else
    return findhelp(subroot->right(),coord,e,(discrim+1)%D);
}

template <class Elem> void KD<Elem>::
regionhelp(BinNode<Elem>* subroot, int* coord,
           int rad, int discrim) const {
  // Check if record at subroot is in circle
  if (InCircle((subroot->val()).coord(), coord, D, rad))
    printout(subroot->val());  // Do what is appropriate
  int* currcoord = (subroot->val()).coord();
  if (currcoord[discrim] > (coord[discrim] - rad))
    regionhelp(subroot->left(), coord, rad, (discrim+1)%D);
  if (currcoord[discrim] < (coord[discrim] + rad))
    regionhelp(subroot->right(), coord, rad, (discrim+1)%D);
}

template <class Elem> BinNode<Elem>* KD<Elem>::
findmin(BinNode<Elem>* subroot,
          int discrim, int currdis) const {
  // discrim: discriminator key used for minimum search;
  // currdis: current level (mod D);
  BinNode<Elem> *temp1, *temp2;
  int *coord, *t1coord, *t2coord;
  if (subroot == NULL) return NULL;
  coord = (subroot->val()).coord();
  temp1 = findmin(subroot->left(), discrim, (currdis+1)%D);
  if (temp1 != NULL)
    t1coord = (temp1->val()).coord();
  if (discrim != currdis) { // Min could be on either side
    temp2 = findmin(subroot->right(),discrim,(currdis+1)%D);
    if (temp2 != NULL)
      t2coord = (temp2->val()).coord();
    if ((temp1 == NULL) || ((temp2 != NULL) &&
         (t2coord[discrim] < t1coord[discrim])))
      temp1 = temp2; // Right side has smaller key value
  } // Now, temp1 has the smallest value in children
  if ((temp1 == NULL) || (coord[discrim]<t1coord[discrim]))      
    return subroot;
  else return temp1;
}

int main(int argc, char** argv) {
  CityRec dum;
  int dumc[2] = {10, 20};
  KD<CityRec>* tree = new KD<CityRec>(2);
  tree->find(dum, dumc);
  tree->regionsearch(dumc, 10);
  tree->remove(dumc, dum);
  return(0);
}
