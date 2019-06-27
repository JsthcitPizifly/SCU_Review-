#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#define INFINITY 65535  // Big enough for simple tests

#define ROOT -1

#include "uf.h"

#include "grmat.h"
#include "minheap.h"

int minVertex(Graph*, int*);

void AddEdgetoMST(int v1, int v2) {
  cout << "Add edge " << v1 << " to " << v2 << "\n";
}

class DijkElem {
public:
  int vertex;
  int distance;
  DijkElem() { vertex = -1; distance = -1; }
  DijkElem(int v, int d) { vertex = v; distance = d; }
};

class DDComp {
public:
  static bool lt(DijkElem x, DijkElem y)
    { return x.distance < y.distance; }
  static bool eq(DijkElem x, DijkElem y)
    { return x.distance == y.distance; }
  static bool gt(DijkElem x, DijkElem y)
    { return x.distance > y.distance; }
};

class KruskElem {
public:
  int from, to, distance;
  KruskElem() { from = -1;  to = -1; distance = -1; }
  KruskElem(int f, int t, int d)
    { from = f; to = t; distance = d; }
};

class KKComp {
public:
  static bool lt(KruskElem x, KruskElem y)
    { return x.distance < y.distance; }
  static bool eq(KruskElem x, KruskElem y)
    { return x.distance == y.distance; }
  static bool gt(KruskElem x, KruskElem y)
    { return x.distance > y.distance; }
};

Kruskel(Graph* G) { // Kruskal's MST algorithm
  Gentree A(G->n()); // Equivalence class array
  KruskElem E[G->e()];   // Array of edges for min-heap
  int i;
  int edgecnt = 0;
  for (i=0; i<G->n(); i++)  // Put the edges on the array
    for (int w=G->first(i); w<G->n(); w = G->next(i,w)) {
      E[edgecnt].distance = G->weight(i, w);
      E[edgecnt].from = i;
      E[edgecnt++].to = w;
    }
  // Heapify the edges
  minheap<KruskElem, KKComp> H(E, edgecnt, edgecnt);
  int numMST = G->n();         // Initially n equiv classes
  for (i=0; numMST>1; i++) {   // Combine equiv classes
    KruskElem temp;
    H.removemin(temp); // Get next cheapest edge
    int v = temp.from;  int u = temp.to;
    if (A.differ(v, u)) { // If in different equiv classes
      A.UNION(v, u);      // Combine equiv classes
      AddEdgetoMST(temp.from, temp.to);  // Add edge to MST
      numMST--;           // One less MST
    }
  }
}


// Test Depth First Search:
// Version for Adjancency Matrix representation
main(int argc, char** argv) {
  Graph* G;
  FILE *fid;

  if (argc != 2) {
    cout << "Usage: gkruskm <file>\n";
    exit(-1);
  }

  if ((fid = fopen(argv[1], "rt")) == NULL) {
    cout << "Unable to open file |" << argv[1] << "|\n";
    exit(-1);
  }

  G = createGraph<Graphm>(fid);
  if (G == NULL) {
    cout << "Unable to create graph\n";
    exit(-1);
  }

  Kruskel(G);
  return 0;
}
