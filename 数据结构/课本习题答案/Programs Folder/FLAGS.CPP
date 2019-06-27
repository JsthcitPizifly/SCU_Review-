#include <iostream.h>
#include <stdlib.h>

#include "book.h"

struct btype {
int f0 : 1;
int f1 : 1;
int f2 : 1;
int f3 : 1;
int f4 : 1;
int f5 : 1;
int f6 : 1;
int f7 : 1;
int f8 : 1;
int f9 : 1;
int f10 : 1;
int f11 : 1;
int f12 : 1;
int f13 : 1;
int f14 : 1;
int f15 : 1;
int f16 : 1;
int f17 : 1;
int f18 : 1;
int f19 : 1;
int f20 : 1;
int f21 : 1;
int f22 : 1;
int f23 : 1;
int f24 : 1;
int f25 : 1;
int f26 : 1;
int f27 : 1;
int f28 : 1;
int f29 : 1;
int f30 : 1;
int f31 : 1;
};

struct cstruct {
  char pos[32];
};

struct sstruct {
  short pos[32];
};

struct lstruct {
  long pos[32];
};


int main(int argc, char** argv)
{
  struct cstruct cs;
  struct sstruct ss;
  struct lstruct ls;
  struct btype b;

  char csa[32];
  short ssa[32];
  long lsa[32];

  long count;
  long i;

  Assert(argc == 2, "Usage: flags <number_of_iterations>");

  count = atol(argv[1]);

  cs.pos[0] = true;
  ss.pos[0] = true;
  ls.pos[0] = true;
  csa[0] = true;
  ssa[0] = true;
  lsa[0] = true;
  b.f0 = true;

  Settime();
  for (i=0; i<count; i++) {
    csa[1] = csa[0];
    csa[2] = csa[1];
    csa[3] = csa[2];
    csa[4] = csa[3];
    csa[5] = csa[4];
    csa[6] = csa[5];
    csa[7] = csa[6];
    csa[8] = csa[7];
    csa[9] = csa[8];
    csa[10] = csa[9];
    csa[11] = csa[10];
    csa[12] = csa[11];
    csa[13] = csa[12];
    csa[14] = csa[13];
    csa[15] = csa[14];
    csa[16] = csa[15];
    csa[17] = csa[16];
    csa[18] = csa[17];
    csa[19] = csa[18];
    csa[20] = csa[19];
  }
  cout << "Time for characters (20 assigns): " << count
       << " iterations: " << Gettime() << " seconds\n";

  Settime();
  for (i=0; i<count; i++) {
    ssa[1] = ssa[0];
    ssa[2] = ssa[1];
    ssa[3] = ssa[2];
    ssa[4] = ssa[3];
    ssa[5] = ssa[4];
    ssa[6] = ssa[5];
    ssa[7] = ssa[6];
    ssa[8] = ssa[7];
    ssa[9] = ssa[8];
    ssa[10] = ssa[9];
    ssa[11] = ssa[10];
    ssa[12] = ssa[11];
    ssa[13] = ssa[12];
    ssa[14] = ssa[13];
    ssa[15] = ssa[14];
    ssa[16] = ssa[15];
    ssa[17] = ssa[16];
    ssa[18] = ssa[17];
    ssa[19] = ssa[18];
    ssa[20] = ssa[19];
}
  cout << "Time for shorts (20 assigns): " << count
       << " iterations: " << Gettime() << " seconds\n";

  Settime();
  for (i=0; i<count; i++) {
    lsa[1] = lsa[0];
    lsa[2] = lsa[1];
    lsa[3] = lsa[2];
    lsa[4] = lsa[3];
    lsa[5] = lsa[4];
    lsa[6] = lsa[5];
    lsa[7] = lsa[6];
    lsa[8] = lsa[7];
    lsa[9] = lsa[8];
    lsa[10] = lsa[9];
    lsa[11] = lsa[10];
    lsa[12] = lsa[11];
    lsa[13] = lsa[12];
    lsa[14] = lsa[13];
    lsa[15] = lsa[14];
    lsa[16] = lsa[15];
    lsa[17] = lsa[16];
    lsa[18] = lsa[17];
    lsa[19] = lsa[18];
    lsa[20] = lsa[19];
  }
  cout << "Time for longs (20 assigns): " << count
       << " iterations: " << Gettime() << " seconds\n";

  Settime();
  for (i=0; i<count; i++) {
    b.f1 = b.f0;
    b.f2 = b.f1;
    b.f3 = b.f2;
    b.f4 = b.f3;
    b.f5 = b.f4;
    b.f6 = b.f5;
    b.f7 = b.f6;
    b.f8 = b.f7;
    b.f9 = b.f8;
    b.f10 = b.f9;
    b.f11 = b.f10;
    b.f12 = b.f11;
    b.f13 = b.f12;
    b.f14 = b.f13;
    b.f15 = b.f14;
    b.f16 = b.f15;
    b.f17 = b.f16;
    b.f18 = b.f17;
    b.f19 = b.f18;
    b.f20 = b.f19;
  }
  cout << "Time for bitfields (20 assigns): " << count
       << " iterations: " << Gettime() << " seconds\n";

 return 0;
}

