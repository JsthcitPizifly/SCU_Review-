#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#include "grmat.h"

#include "aqueue.h"

void printout(int v) {
  cout << v << " ";
}

// Topological sort: Queue
void topsort(Graph* G, Queue<int>* Q) {
  int Count[G->n()];
  int v, w;
  for (v=0; v<G->n(); v++) Count[v] = 0; // Initialize
  for (v=0; v<G->n(); v++)   // Process every edge
    for (w=G->first(v); w<G->n(); w = G->next(v,w))
       Count[w]++;   // Add to v2's prereq count
  for (v=0; v<G->n(); v++)   // Initialize Queue
    if (Count[v] == 0)       // Vertex has no prerequisites
      Q->enqueue(v);
  while (Q->length() != 0) { // Process the vertices
    Q->dequeue(v);
    printout(v);             // PreVisit for Vertex V
    for (w=G->first(v); w<G->n(); w = G->next(v,w)) {
      Count[w]--;    // One less prerequisite
      if (Count[w] == 0)     // This vertex is now free
        Q->enqueue(w);
    }
  }
}

// Test Depth First Search:
// Version for Adjancency Matrix representation
main(int argc, char** argv) {
  Graph* G;
  FILE *fid;

  if (argc != 2) {
    cout << "Usage: grdfsm <file>\n";
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

  Queue<int>* Q = new AQueue<int>(G->n());

  topsort(G, Q);
  cout << endl;
  return 0;
}
