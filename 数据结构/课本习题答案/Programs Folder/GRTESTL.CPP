#include <iostream.h>
#include <stdlib.h>

#include "book.h"

#include "grlist.h"

// Simple program to test graph construction:
// Version for Adjancency List representation
main(int argc, char** argv) {
  Graph* G;
  FILE *fid;

  if (argc != 2) {
    cout << "Usage: grtestl <file>\n";
    exit(-1);
  }

  if ((fid = fopen(argv[1], "rt")) == NULL) {
    cout << "Unable to open file |" << argv[1] << "|\n";
    exit(-1);
  }

  G = createGraph<Graphl>(fid);
  if (G == NULL) {
    cout << "Unable to create graph\n";
    exit(-1);
  }

  Gprint(G);
  return 0;
}
