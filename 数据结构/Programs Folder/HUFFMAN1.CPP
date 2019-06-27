/* Huffman coding tree example program.
First, read from the data file a set of strings and associated frequencies.
These are placed onto a list of (single node) Huffman trees.
Next, build a single Huffman coding tree for the set.  The strings and their
codes are then output, with CodeTable storing the coding for each input string.
Next, read commands to "encode" or "decode" strings, providing the
appropriate output. */

#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "book.h"

#include "freqpair.h"

// Overload for the FreqPair << operator
template <class Elem>
ostream& operator << (ostream& s, FreqPair<Elem>* pair)
  // Assume that the Freqpair element is printable
  { return(s << pair->val() << "|" << pair->weight()); }

// Include files for sorted linked lists
#include "linkFL.h"
#include "llist.h"
#include "sllist.h"

#define MAXCODELEN 20       // Max length of a huffman code
#define CODETABLELEN 100    // Maximum number of codes storable

// CodeTable maps objects to their associated codes.
template <class Elem, class Compare>
class CodeTable {
private:
  Elem* obs;             // Objects
  char** codes;  // Associated code values
  int currsize;  // Current number of objects in table
  int maxsize;  // Max objects permitted in table
public:
  CodeTable(int size) {
    obs = new Elem[size];
    codes = new char*[size];
	for (int i = 0; i<size; i++) {
	  codes[i] = new char[MAXCODELEN+1];
      for(int j=0; j<=MAXCODELEN; j++)
		  codes[i][j] = '-';
	  codes[i][MAXCODELEN] = '\0';
	}
	  maxsize = size;  currsize = 0;
  }
  void addobject(Elem& obj) {
    Assert(currsize < maxsize, "CodeTable is full!");
    obs[currsize++] = obj;
  }
  char* getcode(Elem& obj) {
	for (int i=0; i<currsize; i++)
	  if(Compare::eq(obj, obs[i])) return codes[i];
	return NULL;
  }
};  

template <class Elem, class Comp>
class HuffNode {    // Node abstract base class
public:
  virtual int weight() = 0;
  virtual void buildcode(CodeTable<Elem, Comp>*, char*, int, double&) = 0;
  virtual bool isLeaf() = 0;
  virtual void decode(char*, Elem&, int&) = 0;
};

template <class Elem, class Comp> // Leaf node subclass
class LeafNode : public HuffNode<Elem, Comp> {
private:
  FreqPair<Elem>* it;               // Frequency pair
public:
  LeafNode(const Elem& val, int freq) // Constructor
    { it = new FreqPair<Elem>(val, freq); }
  int weight() { return it->weight(); }    // Return frequency
  virtual void buildcode(CodeTable<Elem, Comp>* ct, char* prefix,
                         int level, double& total) {
    cout << it->val() << "\t" << prefix << "\n";
    strcpy(ct->getcode(it->val()), prefix);
    total += level * it->weight();
  }
  FreqPair<Elem>* val() { return it; }
  bool isLeaf() { return true; }
  void decode(char* code, Elem& msg, int& cnt)
    { msg = it->val(); }
};

template <class Elem, class Comp> // Internal node subclass
class IntlNode : public HuffNode<Elem, Comp> {
private:
  HuffNode<Elem, Comp>* lc;                  // Left child
  HuffNode<Elem, Comp>* rc;                 // Right child
  int wgt;                   // Subtree weight
public:
  IntlNode(HuffNode<Elem, Comp>* l, HuffNode<Elem, Comp>* r)
    { wgt = l->weight() + r->weight(); lc = l; rc = r; } // Constructor
  int weight() { return wgt; }    // Return frequency
  virtual void buildcode(CodeTable<Elem, Comp>* ct, char* prefix,
                         int level, double& total) {
    prefix[level] = '0';
    prefix[level+1] = '\0';
    lc->buildcode(ct, prefix, level+1, total);
    prefix[level] = '1';
    prefix[level+1] = '\0';
    rc->buildcode(ct, prefix, level+1, total);
    prefix[level] = '\0';
  }
  bool isLeaf() { return false; }
  void decode(char* code, Elem& msg, int& cnt) {
    cnt++;
    if (code[cnt-1] == '0') lc->decode(code, msg, cnt);
    else if (code[cnt-1] == '1') rc->decode(code, msg, cnt);
    else Assert(false, "Bad code character");
  }
};

template <class Elem, class Comp>
ostream& operator << (ostream& s, HuffNode<Elem, Comp>* z)
{
  if (z->isLeaf())
    return s << ((LeafNode<Elem, Comp>*)z)->val();
  else
    return s << ((IntlNode<Elem, Comp>*)z)->weight();
}

// HuffTree is a template of two parameters: the object
//   type being coded and a comparator for two such objects.
template <class Elem, class Comp>
class HuffTree {
private:
  HuffNode<Elem, Comp>* theRoot;
public:
  HuffTree(Elem& val, int freq)
    { theRoot = new LeafNode<Elem, Comp>(val, freq); }
  HuffTree(HuffTree<Elem, Comp>* l, HuffTree<Elem, Comp>* r)
    { theRoot = new IntlNode<Elem, Comp>(l->theRoot,
                                         r->theRoot); }
  ~HuffTree() {}
  void buildcode(CodeTable<Elem, Comp>* ct, char* pre, int lev,
                 double& tot)
    { theRoot->buildcode(ct, pre, lev, tot); }
  int weight() { return theRoot->weight(); }
  void decode(char* code, Elem& msg, int& cnt)
    { theRoot->decode(code, msg, cnt); }
};

template <class Elem, class Comp> class HHCompare {
public:
  static bool lt(HuffTree<Elem, Comp>* x,
                 HuffTree<Elem, Comp>* y)
    { return x->weight() < y->weight(); }
  static bool eq(HuffTree<Elem, Comp>* x,
                 HuffTree<Elem, Comp>* y)
    { return x->weight() == y->weight(); }
  static bool gt(HuffTree<Elem, Comp>* x,
                 HuffTree<Elem, Comp>* y)
    { return x->weight() > y->weight(); }
};

// Overload for the HuffTree << operator
template <class Elem, class Comp>
ostream& operator << (ostream& s, HuffTree<Elem, Comp>* z)
  { return s << z->weight(); }

class ccCompare {
public:
  static bool lt(char x, char y) { return x < y; }
  static bool eq(char x, char y) { return x == y; }
  static bool gt(char x, char y) { return x > y; }
};


// Read the list of frequencies, make the forest, and set the
// list of entries into the code table.
void read_freqs(SLList<HuffTree<char, ccCompare>*,
				       HHCompare<char, ccCompare> >* forest,
                CodeTable<char, ccCompare>* ct, FILE* fp)
{ // Read a list of strings and frequencies from standard input,
  // building a list of Huffman coding tree nodes
  char buff[100];
  char buff2[100];
  char *ptr;
  char *ptr2;
  int freq;
  HuffTree<char, ccCompare>* temptree;

  while (true) {
    Assert(fgets(buff, 99, fp) != NULL,   // Read the next entry
           "No more codes to read -- where is end?");

    // process the entry, creating a new HuffTree
    for(ptr=buff; *ptr==' '; ptr++);  // Read first word
    if (strncmp(ptr, "end", 3) == 0)  // OK, we're done reading entries
      return;
    Assert(*ptr == '"', "First char was not a quote mark.");
    for (ptr2=buff2,ptr++; *ptr!='"'; ptr++)
      *ptr2++ = *ptr;
    *ptr2 = '\0'; // End of string
    for (ptr++; *ptr==' '; ptr++);
    Assert(isdigit(*ptr) != 0, "Must be a digit here.");
    freq = atoi(ptr);
    ct->addobject(buff2[0]);
    temptree = new HuffTree<char, ccCompare>(buff2[0], freq);

    // put in the list in sorted order
    // WARNING: This may be considered buggy.  Nodes with equal weight will
    // be put in reverse order of appearance, not in alphabetical order.
    forest->insert(temptree);
  }
}

// Build Huffman tree from list tmplist
template <class Elem, class Comp>HuffTree<Elem, Comp>*
buildHuff(SLList<HuffTree<Elem, Comp>*,
          HHCompare<Elem, Comp> >* fl) {
  HuffTree<Elem, Comp> *temp1, *temp2, *temp3;
  for (fl->setStart(); fl->leftLength()+fl->rightLength()>1;
       fl->setStart()) { // While at least two items left
    fl->remove(temp1);   // Pull first two trees  
    fl->remove(temp2);   //   off the list
    temp3 = new HuffTree<Elem, Comp>(temp1, temp2);
    fl->insert(temp3);   // Put the new tree back on list
    delete temp1;        // Must delete the remnants
    delete temp2;        //   of the trees we created
  }
  return temp3;
}


void do_commands(HuffTree<char, ccCompare>* theTree,
                 CodeTable<char, ccCompare>* theTable, FILE *fp)
{
  int currchar;
  char buff[80];

  while (fgets(buff, 99, fp)) {
    if (strncmp(buff, "decode", 6) == 0) {
      for (currchar=0; buff[currchar] != '"'; currchar++);
      cout << "Decode " << &buff[currchar++];
	  while (buff[currchar] != '"') {
		int cnt = 0;
		char msg;
        theTree->decode(&buff[currchar], msg, cnt);
        cout << msg << endl;
		currchar += cnt;
	  }
    }
    else if(strncmp(buff, "encode", 6) == 0) {
      for (currchar=0; buff[currchar] != '"'; currchar++);
      cout << "Encode " << &buff[currchar++];
      for(; buff[currchar] != '"' ; currchar++) // Assume codes are characters.  Should generalize this.
        if (buff[currchar] == ' ') cout << ' ';
        else cout << theTable->getcode(buff[currchar]);
    }
    cout << "\n";
  }
}


main(int argc, char** argv)
{
  // This list holds the Huffman forest during construction
  SLList<HuffTree<char, ccCompare>*, HHCompare<char, ccCompare> >* forest =
      new SLList<HuffTree<char, ccCompare>*, HHCompare<char, ccCompare> >;
  // This will be the eventual Huffman tree
  HuffTree<char, ccCompare>* theTree;
  CodeTable<char, ccCompare>* theTable =
	   new CodeTable<char, ccCompare>(CODETABLELEN);
  // Working storage for the tree traversal that builds the code table
  char prefix[MAXCODELEN+1];
  // total is used to calculate the average code length
  double total = 0;
  FILE *fp;  // The file pointer

  // First, figure out where we are reading in the input from.
  if (argc == 1) fp = stdin;
  else fp = fopen(argv[1], "rt");

  // Now, read in the list of frequencies, and initialize the
  //   forest of Huffman trees.
  cout << "Read frequencies\n";
  read_freqs(forest, theTable, fp);

  forest->print();

  // Now, build the tree.
  cout << "Build the tree\n";
  theTree = buildHuff(forest);

  // Now, output the tree, which also creates the code table.
  cout << "Output the tree\n";
  theTree->buildcode(theTable, prefix, 0, total);
  cout << "Average code length is "
       << total/(double)theTree->weight() << "\n";

  // Finally, do the encode/decode commands to test the system.
  do_commands(theTree, theTable, fp);
  return 0;
}
