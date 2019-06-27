#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "book.h"

#define NumRec 1024

void GSbell(void)
{
  cout << "";
}

typedef int Elem;

int main(int argc, char** argv) {
  int filesize;
  Elem Array[NumRec];
  int i, j, dum;
  FILE* fp;

  if (argc < 3) {
    cout << "Error: Need a file name and size parameter.\n";
    cout << "Size is measured in blocks of 4096 bytes.\n";
    exit(-1);
  }
  if ((fp = fopen(argv[1], "wb")) == NULL) {
    cout << "Unable to open file :" << argv[1] << ":\n";
    exit(-1);
  }
  filesize = atoi(argv[2]);
  Randomize();
  for (i=0; i<filesize; i++) {
    for (j=0; j<NumRec; j++)
      Array[j] = (8224 << 16) + Random(26) + 0x2041;
    if ((dum = fwrite(Array, sizeof(Elem), NumRec, fp)) != NumRec) {
      cout << "Unable to write a block: " << dum << "\n";
      GSbell();
      exit(1);
    }
  }
  return(0);
}
