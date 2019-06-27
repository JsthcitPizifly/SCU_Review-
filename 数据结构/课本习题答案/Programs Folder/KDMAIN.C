#include "book.h"

#define key(X) (X)

typedef int Elem;

#define kd_key(X, L) (X)

bool InCircle(int v, int D, int k) {}
void printout(int v) {}


class KDNode {                // Binary tree node class
public:
  Elem value;                 // The node's value
  KDNode* left;               // Pointer to left child
  KDNode* right;              // Pointer to right child
  BinNode() { }
};

class KD {
private:
  KDNode* root;
public:
  KDNode* KDfindhelp(KDNode*, Elem, int, int) const;
  KDNode* KDfindmin(KDNode*, int, int, int);
  void KDRegionSearch(KDNode*, Elem, int, int, int);
};
  
#include "kdfind.x"
#include "kdrsch.x"
#include "kddmin.x"

int main(int argc, char** argv) {
  return(0);
}
