#include <iostream.h>
#include <stdlib.h>

typedef int MemHandle;

#include "MemMan.h"

class MemConc: public MemManager {
public:
  MemHandle insert(void* space, int length) {}
  void release(MemHandle h) {}
  void get(void* space, MemHandle h, int size) {}
};

int main(int argc, char** argv) {
  int i=5;
  int j=10;

  int* p = new int[5];
  int* q = new int[10];
  p = q;

  return 0;
}
