#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#define HASHSIZE 101

int HT[HASHSIZE];
int M = HASHSIZE;

int ELFhash(char* key) {
  unsigned long h = 0;
  while(*key) {
    h = (h << 4) + *key++;
    unsigned long g = h & 0xF0000000L;
    if (g) h ^= g >> 24;
    h &= ~g;
  }
  return h % M;
}

int h(char* x) {
  int i, sum;
  for (sum=0, i=0; x[i] != '\0'; i++)
    sum += (int) x[i];
  return(sum % M);
}

int h(int x) {
  return(x % 16);
}

template <class Key>
int p(Key K, int i) { return i; }

int main() {
return 0;
}
