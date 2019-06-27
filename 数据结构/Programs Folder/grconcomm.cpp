#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#include "grmat.h"

void DFS_component(Graph* G, int v, int compcount) {
  G->setMark(v, compcount);
  for (int w=G->first(v); w<G->n(); w = G->next(v,w))
    if (G->getMark(w) == 0)
      DFS_component(G, w, compcount);
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

  int i;
  int compcount;

  for (i=0; i<G->n(); i++) // For n vertices in the graph
    G->setMark(i, 0);   // Vertices start in no component
  compcount = 1;        // Counter for current component
  for (i=0; i<G->n(); i++)
    if (G->getMark(i) == 0) { // Start a new component
      DFS_component(G, i, compcount);
      compcount++;
    }

  for (i=0; i<G->n(); i++)
    cout << "Vertex " << i << ": " << G->getMark(i) << endl;
  return 0;
}
