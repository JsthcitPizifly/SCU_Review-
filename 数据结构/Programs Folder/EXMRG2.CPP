// Simple external merge demonstration.
// Second in a series of three programs.
// This version builds initial runs of full memory size, then combines
// the runs with a 2-way merge.

#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>
#include <stdio.h>

#include "book.h"
#include "compare.h"

const int THRESHOLD=0;
template <class Elem, class Comp>
void inssort(Elem A[], int n) { // Insertion Sort
  for (int i=1; i<n; i++)       // Insert i'th record
    for (int j=i; (j>0) && (Comp::lt(A[j], A[j-1])); j--)
      swap(A, j, j-1);
}

template <class Elem> int findpivot(Elem A[], int i, int j)
  { return (i+j)/2; }

template <class Elem, class Comp>
int partition(Elem A[], int l, int r, Elem& pivot) {
  do {             // Move the bounds inward until they meet
    while (Comp::lt(A[++l], pivot));     // Move l right and
    while ((r != 0) && Comp::gt(A[--r], pivot)); // r left
    swap(A, l, r);              // Swap out-of-place values
  } while (l < r);              // Stop when they cross
  swap(A, l, r);                // Reverse last, wasted swap
  return l;      // Return first position in right partition
}

template <class Elem, class Comp>
void qsort(Elem array[], int i, int j) {
  if ((j-i) <= THRESHOLD) return; // Don't sort short list
  int pivotindex = findpivot(array, i, j);
  swap(array, pivotindex, j); // stick pivot at end
  int k = partition<Elem,Comp>(array, i-1, j, array[j]);
  swap(array, k, j);          // Put pivot value in place
  qsort<Elem,Comp>(array, i, k-1);
  qsort<Elem,Comp>(array, k+1, j);
}

#define RecsPerBlock 1024  // Number of records/block
int BlocksPerRun;          // Blocks per run.  Determined by file size.
#define RecsPerRun BlocksPerRun*RecsPerBlock // Number of records/run

// Return type from getnext().  Signifies no more records in file
#define EMPTY -2

// Define indices for run files.
// These indices get swapped around as necessary to switch input files
// to become output files on alternate passes.
#define IN 0
#define IN1 0
#define IN2 1
#define OUT 2
#define OUT1 2
#define OUT2 3

// This is a simple example of external sorting, with the records being
// nothing more than an integer value.
typedef int Elem;

// Maintain info on the run files -- two input files, two output files
// Posit indicates the current position in the given file
int Posit[4] = {RecsPerBlock, RecsPerBlock, 0, 0};
// Recinblock indicates number for records now in the current block
//   of the given file
int Recinblock[4] = {0, 0, 0, 0};
// Buffers for the four run files
Elem Array[4][RecsPerBlock];
// File pointers for the four run files
fstream FS[4];
// Names of the four run files
char Name[4][30];

// Return in val the next record from the file fpindex.
// This supports buffered reading from the input file, one block at a time.
bool getnext(int fpindex, Elem& val) {
  if (Posit[fpindex] >= Recinblock[fpindex]) { // page fault
    FS[fpindex].read(&Array[fpindex], sizeof(Elem)*RecsPerBlock);
    Recinblock[fpindex] = FS[fpindex].gcount()/sizeof(Elem);
/* cout << "Read " << Recinblock[fpindex] << " records from "
     << fpindex << endl;
cout << "Now at position" << FS[fpindex].tellg() << endl; */
    if (Recinblock[fpindex] == 0) { val = EMPTY; return false; }
    Posit[fpindex] = 0;
  }
  val = Array[fpindex][Posit[fpindex]++];
  return true;
}


// Write a record (in val) to the output file fpindex.
// This supports buffered writing to the output file, one block at a time.
void putout(int fpindex, Elem val) {
  int dum;
  if (Posit[fpindex] == RecsPerBlock) { // page fault
    FS[fpindex].write(Array[fpindex], sizeof(Elem)*RecsPerBlock);
    Posit[fpindex] = 0;
  }
  Array[fpindex][Posit[fpindex]++] = val;
}


// Flush an output block to disk
void myflush(int fpindex) {
  FS[fpindex].write(Array[fpindex], sizeof(Elem)*Posit[fpindex]);
}

void sort(Elem* array, int n) {
  qsort<Elem,intintCompare>(array, 0, n-1);
  inssort<Elem,intintCompare>(array, n); // Cleanup sort
}

// First pass of merge sort.
// Split input into two files.
void pass1(int inindex, int outindex1, int outindex2, int numruns)
{
  // Declare the space for building the initial runs.
  Elem *BigArray = new Elem[RecsPerRun];
  for (int i=0; i<numruns; i++) {
    FS[inindex].read(BigArray, sizeof(Elem)*RecsPerRun);
    if (!FS[inindex]) cout << "Error reading run " << i << endl;

    sort(BigArray, RecsPerRun);

    FS[outindex1].write(BigArray, sizeof(Elem)*RecsPerRun);
    if (!FS[outindex1]) cout << "Error writing run " << i << endl;
  }
  delete [] BigArray;
}


// Do the real work here
void exmergesort(int in1, int in2, int out1, int out2, char* outname,
                 int numruns) {
  Elem val1, val2;
  Elem last = -1;
  bool DONE = false;

  // Open output files
  FS[out1].open(Name[out1], ios::out | ios::binary);
  if (!FS[out1]) cout << "Error opening " << Name[out1] << endl;
  FS[out2].open(Name[out2], ios::out | ios::binary);
  if (!FS[out2]) cout << "Error opening " << Name[out2] << endl;

  // Create the initial run files
  pass1(in1, out1, out2, numruns);
  FS[in1].close();
  FS[out1].close();
  FS[out2].close();

  // Now, merge runs into two output files.
  // Repeat that process until only one run is left.
  // This works by opening the files prior to the pass and closing them
  // after the pass.  This allows the system to track the number of records
  // in the files.  The alternative would be to explicitly  keep track of
  // the number of records in each file, and just have the files all be
  // both readable and writable.
  while (!DONE) {
cout << "Do Pass\n";
    swap(in1, out1);
    swap(in2, out2);
    FS[in1].open(Name[in1], ios::in | ios::binary);
    if (!FS[in1]) cout << "Error opening " << Name[in1] << endl;
    FS[in2].open(Name[in2], ios::in | ios::binary);
    if (!FS[in2]) cout << "Error opening " << Name[in2] << endl;
    FS[out1].open(Name[out1], ios::out | ios::binary);
    if (!FS[out1]) cout << "Error opening " << Name[out1] << endl;
    FS[out2].open(Name[out2], ios::out | ios::binary);
    if (!FS[out2]) cout << "Error opening " << Name[out2] << endl;

    Posit[out1] = Posit[out2] = 0;
    Posit[in1] = Posit[in2] = RecsPerBlock;
    DONE = true;
    last = -1;
    getnext(in1, val1);  getnext(in2, val2);

    // Here is where the actual merge takes place
    while ((val1 != EMPTY) || (val2 != EMPTY)) {
      if ((val1 < last) && (val2 < last)) // At end of these runs
	{ swap(out1, out2); last = -1; DONE = false; }
      if (val1 >= last) // Still stuff in run 1
	if (val2 >= last) // Still stuff in run 2
	  if (val1 < val2) // Put out one of the records
	    { putout(out1, val1); last = val1; getnext(in1, val1); }
          else
            { putout(out1, val2); last = val2; getnext(in2, val2); }
        else // Put out from run 1
          { putout(out1, val1); last = val1; getnext(in1, val1); }
      else // Put out from run 2
        { putout(out1, val2); last = val2; getnext(in2, val2); }
    }
    // Done this run, so flush output
    myflush(out1);
    myflush(out2);
    FS[in1].close(); FS[in2].close();
    FS[out1].close(); FS[out2].close();
  }
  rename(Name[out1], outname);
}


// Main routine.  Get everything ready
int main(int argc, char** argv) {

  if (argc < 4) {
    cout << "Usage: exqsort <infile> <outfile> <numblocks>.\n";
    cout << "Blocksize is " << RecsPerBlock * sizeof(Elem) << " bytes.\n";
    exit(-1);
  }

  int numblocks = atoi(argv[3]);
  if (numblocks <= 4096) BlocksPerRun = 64;
  else if (numblocks <= 65536) BlocksPerRun = 256;
  else {
    cout << "File size is too big.\n";
    exit(1);
  }
  cout << "Allocating " << RecsPerRun*sizeof(Elem)
       << " bytes of working space\n";

  // For first pass, need the original input file.  Won't use again
  FS[IN1].open(argv[1], ios::in | ios::binary);
  if (!FS[IN1]) cout << "Error opening " << argv[1] << endl;

  // build the names of the run files
  sprintf(Name[IN1], "%s%s", argv[1], ".1");
  sprintf(Name[IN2], "%s%s", argv[1], ".2");
  sprintf(Name[OUT1], "%s%s", argv[2], ".1");
  sprintf(Name[OUT2], "%s%s", argv[2], ".2");

  // Start timing from here
  Settime();
  exmergesort(IN1, IN2, OUT1, OUT2, argv[2], numblocks/BlocksPerRun);
  cout << "Time is " << Gettime() << "seconds\n";

  return 0;
}
