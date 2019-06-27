// Simple external merge demonstration.
// Third in a series of three programs.
// This version builds initial runs of the given run size, then combines
// the runs with a single multi-way merge.

#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>
#include <stdio.h>

//#include <string.h>
//#include <ctype.h>

#define BIGKEY 600000000L // HACK!!

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

// This is a simple example of external sorting, with the records being
// nothing more than an integer value.
typedef int Elem;

Elem OutBuff[RecsPerBlock];
int OutPos = 0;

// Return type from getnext().  Signifies no more records in file
#define EMPTY -2

void sort(Elem* array, int n) {
  qsort<Elem,intintCompare>(array, 0, n-1);
  inssort<Elem,intintCompare>(array, n); // Cleanup sort
}

// First pass of merge sort.
// Break the file into runs, putting them into the temp file
void pass1(fstream& infile, fstream& tempfile, int numruns)
{
  // Declare the space for building the initial runs.
  Elem *BigArray = new Elem[RecsPerRun];
  for (int i=0; i<numruns; i++) {
    infile.read(BigArray, sizeof(Elem)*RecsPerRun);
    if (!infile) cout << "Error reading run " << i << endl;
    sort(BigArray, RecsPerRun);
    tempfile.write(BigArray, sizeof(Elem)*RecsPerRun);
    if (!tempfile) cout << "Error writing run " << i << endl;
  }
  delete [] BigArray;
}


// Return index of run with the least value from the current candidates
int getleast(Elem** BlockSpace, int* Posit, int numruns) {
  Elem temp = BIGKEY;
  int index = -1;

  for (int i=0; i<numruns; i++)
    if ((BlockSpace[i][Posit[i]] != EMPTY) &&
        (BlockSpace[i][Posit[i]] < temp)) {
      temp = BlockSpace[i][Posit[i]];
      index = i;
    }
  return index;
}


// Update the run buffer that just got taken from
void getnext(int index, fstream& tempfile,
             int* Posit, int* Count, Elem**BlockSpace) {
  if (Count[index] > BlocksPerRun) return; // Already exhausted
  if (Posit[index] == (RecsPerBlock-1)) { // Page Fault
    if (Count[index] == BlocksPerRun)
      BlockSpace[index][0] = EMPTY;  // Flag as exhausted
    else {
      // Read in a new block
      tempfile.seekg(index*RecsPerRun*sizeof(Elem) +
                     Count[index]*RecsPerBlock*sizeof(Elem));
      tempfile.read(BlockSpace[index], sizeof(Elem)*RecsPerBlock);
    }
    Count[index]++;
    Posit[index] = 0;
  }
  else Posit[index]++;
}


// Put a new value to the buffered output file
void putout(fstream& outfile, Elem val) {
  if (OutPos == RecsPerBlock) { // page fault
    outfile.write(OutBuff, sizeof(Elem)*RecsPerBlock);
    OutPos = 0;
  }
  OutBuff[OutPos++] = val;
}


// Return true iff all runs are exhausted
bool AllEmpty(Elem** BlockSpace, int* Posit, int numruns) {
  for (int i=0; i<numruns; i++)
    if (BlockSpace[i][Posit[i]] != EMPTY)
      return false;
  return true;
}

// Do the real work here
void exmergesort(char* inname, char* outname, int numruns) {
  fstream infile;
  fstream tempfile;
  fstream outfile;
  int i;

  // Open input file and temporary run file
  infile.open(inname, ios::in | ios::binary);
  if (!infile) cout << "Error opening " << inname << endl;
  tempfile.open("temp", ios::out | ios::binary);
  if (!tempfile) cout << "Error opening " << "temp" << endl;

  // Create the initial run file
  pass1(infile, tempfile, numruns);
  infile.close();
  tempfile.close();

cout << "Done pass1\n";

  // Now, merge runs with a single multiway merge.
  // Begin by allocating enough space.
  Elem** BlockSpace = (Elem**)new Elem*[numruns];
  for (i=0; i<numruns; i++)
    BlockSpace[i] = (Elem*)new Elem[RecsPerBlock];

  // Now, get the files ready
  tempfile.open("temp", ios::in | ios::binary);
  if (!tempfile) cout << "Error opening " << "temp" << endl;
  outfile.open(outname, ios::out | ios::binary);
  if (!outfile) cout << "Error opening " << outname << endl;

  // Do the multiway merge
  // Initialize the run space
  for (i=0; i<numruns; i++) {
    tempfile.seekg(i*RecsPerRun*sizeof(Elem));
    tempfile.read(BlockSpace[i], sizeof(Elem)*RecsPerBlock);
    if (!tempfile) cout << "Error reading run " << i << endl;
  }

  // Space to store the current run positions
  int* Posit = new int[numruns];
  int* Count = new int[numruns];
  for (i=0; i<numruns; i++) {
    Posit[i] = 0;
    Count[i] = 1;
  }

  while (!AllEmpty(BlockSpace, Posit, numruns)) {
    int index = getleast(BlockSpace, Posit, numruns);
    putout(outfile, BlockSpace[index][Posit[index]]);
    getnext(index, tempfile, Posit, Count, BlockSpace);
  }

  // Flush final block
  outfile.write(OutBuff, sizeof(Elem)*RecsPerBlock);
  if (!outfile) cout << "Error writing last block\n";
  
  // Close everything up
  tempfile.close();
  outfile.close();
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

  // Start timing from here
  Settime();
  exmergesort(argv[1], argv[2], numblocks/BlocksPerRun);
  cout << "Time is " << Gettime() << "seconds\n";

  return 0;
}
