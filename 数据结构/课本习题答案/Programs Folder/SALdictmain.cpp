#include <iostream.h>
#include <stdlib.h>

#include "book.h"
#include "compare.h"

#include "alist.h"
#include "salist.h"

#include "SALdict.h"

// Driver class for sorted array-based dictionary

int main(int argc, char** argv) {
  SALdict<int, Int, intIntCompare, IntIntCompare> dict;
  Int val;


  dict.insert(10);
  if (dict.find(10, val))
    cout << "Found value " << val << " to match key value 10\n";
  else
    cout << "Nothing found to match key value 10\n";
  dict.insert(15);
  if (dict.find(5, val))
    cout << "Found value " << val << " to match key value 5\n";
  else
    cout << "Nothing found to match key value 5\n";
  dict.insert(10);
  cout << "Size is " << dict.size() << endl;
  if (dict.find(10, val))
    cout << "Found value " << val << " to match key value 10\n";
  else
    cout << "Nothing found to match key value 10\n";
  if (dict.remove(10, val))
    cout << "Removed value " << val << " to match key value 10\n";
  else
    cout << "Nothing found to match key value 10\n";
  if (dict.find(10, val))
    cout << "Found value " << val << " to match key value 10\n";
  else
    cout << "Nothing found to match key value 10\n";
  if (dict.remove(10, val))
	cout << "Remove value " << val << " to match key value 10\n";
  else
    cout << "Nothing found to remove with key value 10\n";
  if (dict.remove(10, val))
	cout << "Remove value " << val << " to match key value 10\n";
  else
    cout << "Nothing found to remove with key value 10\n";
  cout << "Size is " << dict.size() << endl;
  dict.clear();
  if (dict.find(10, val))
    cout << "Found value " << val << " to match key value 10\n";
  else
    cout << "Nothing found to match key value 10\n";
  cout << "Size is " << dict.size() << endl;

  cout << "Now, do interator\n";
  dict.insert(25);
  dict.insert(30);
  dict.insert(21);
  Int e;
  while (dict.removeAny(e))
    cout << "Got element " << e << endl;
	
  return 0;
}
