// Sorting main function for running timings.
// To use: <sortname> [+/-] <size_of_test> <threshold>
//  + means increasing values, - means decreasing value and no
//    parameter means random values;
// <size_of_test> controls the size of an individual test out
// of an array of size ARRAYSIZE.  For example, inssort 10 will run
// a series of sorts on lists of size 10.
// <threshold> controls the threshold parameter for certain sorts, e.g.,
//   cutoff point for quicksort sublists.

long count1 = 0;
long count2 = 0;
int THRESHOLD = 0;

#define ARRAYSIZE 1000000

#define print(X, Y)

/* void print(int* array, int listsize) {
  for(int i=0; i<listsize; i++)
    cout << array[i] << " ";
  cout << "\n";
} */


int main(int argc, char** argv)
{
  int* array;
  int i;
  int listsize;
  int currarg;
  int input = 0;  // Type to sort: -1 -- descending; +1 - ascending;
                  //                0 -- random values

  Randomize();

  array = new int[ARRAYSIZE];

  if ((argc < 2) || (argc > 4)) {
    cout << "Usage: <sortname> [+/-] <size> [<threshold>]\n";
    exit(-1);
  }
  currarg = 1;
  if (argv[currarg][0] == '-') {
    input = -1;
    currarg++;
  }
  else if (argv[currarg][0] == '+') {
    input = 1;
    currarg++;
  }
  listsize = atoi(argv[currarg++]);
  if (argc > currarg)
    THRESHOLD = atoi(argv[currarg]);
  if ((listsize > ARRAYSIZE) || (listsize < 0)) {
    cout << "Selected list size is too big\n";
    exit(-1);
  }
  cout << "Input: " << input << ", size: " << listsize << ", threshold: "
       << THRESHOLD << "\n";

  if (input == -1)
    for (i=0; i<ARRAYSIZE; i++)
      array[i] = ARRAYSIZE - i;  // Reverse sorted
  else if (input == 0)
    for (i=0; i<ARRAYSIZE; i++)
      array[i] = Random(32003);  // Random
  else
    for (i=0; i<ARRAYSIZE; i++)
      array[i] = i;              // Sorted

  Settime();
  for (i=0; i<ARRAYSIZE; i+=listsize) {
    sort<int,intintCompare>(&array[i], listsize);
    print(&array[i], listsize);
  }
  cout << "Sort with list size " << listsize
	   << ", array size " << ARRAYSIZE
       << ", and threshold " << THRESHOLD << ": "
       << Gettime() << " seconds\n";
/*  cout << "Count1 is " << count1 << ", Count2 is " << count2 << "\n";
  cout << "Qcomps is " << qcomps << ", icomps is "
	   << icomps << ", and the total is "
	   << qcomps + icomps << endl; */

  for (i=0; i<ARRAYSIZE; i+=listsize)
    for(int j=i+1; j<i+listsize; j++)
      if(array[j-1] > array[j])
        cout << "ERROR!!!\n";
  return(0);
}
