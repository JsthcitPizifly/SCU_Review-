#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#include "grmat.h"

// Floyd's all-pairs shortest paths algorithm
void Floyd(Graph* G) {
  int D[G->n()][G->n()];       // Store distances
  for (int i=0; i<G->n(); i++) // Initialize D with weights
    for (int j=0; j<G->n(); j++)
      D[i][j] = G->weight(i, j);
  for (int k=0; k<G->n(); k++) // Compute all k paths
    for (int i=0; i<G->n(); i++)
      for (int j=0; j<G->n(); j++)
        if (D[i][j] > (D[i][k] + D[k][j]))
          D[i][j] = D[i][k] + D[k][j];
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

  Floyd(G);
  return 0;
}
