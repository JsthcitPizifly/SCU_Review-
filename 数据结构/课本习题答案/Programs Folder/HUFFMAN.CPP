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

template <class Elem>
class HuffNode {        // Node abstract base class
public:
  virtual int weight() = 0;
  virtual bool isLeaf() = 0;
  virtual HuffNode* left() const = 0;
  virtual void setLeft(HuffNode*) = 0;
  virtual HuffNode* right() const = 0;
  virtual void setRight(HuffNode*) = 0;
};

template <class Elem>   // Leaf node subclass
class LeafNode : public HuffNode<Elem> {
private:
  FreqPair<Elem>* it;                   // Frequency pair
public:
  LeafNode(const Elem& val, int freq)   // Constructor
    { it = new FreqPair<Elem>(val, freq); }
  int weight() { return it->weight(); } // Return frequency
  FreqPair<Elem>* val() { return it; }
  bool isLeaf() { return true; }
  virtual HuffNode* left() const { return NULL; }
  virtual void setLeft(HuffNode*) { }
  virtual HuffNode* right() const { return NULL; }
  virtual void setRight(HuffNode*) { }
};

template <class Elem>   // Internal node subclass
class IntlNode : public HuffNode<Elem> {
private:
  HuffNode<Elem>* lc;   // Left child
  HuffNode<Elem>* rc;   // Right child
  int wgt;              // Subtree weight
public:
  IntlNode(HuffNode<Elem>* l, HuffNode<Elem>* r)
    { wgt = l->weight() + r->weight(); lc = l; rc = r; }
  int weight() { return wgt; }    // Return frequency
  bool isLeaf() { return false; }
  HuffNode<Elem>* left() const { return lc; }
  void setLeft(HuffNode<Elem>* b) { lc = (HuffNode*)b; }
  HuffNode<Elem>* right() const { return rc; }
  void setRight(HuffNode<Elem>* b) { rc = (HuffNode*)b; }
};

template <class Elem, class Comp>
ostream& operator << (ostream& s, HuffNode<Elem>* z)
{
  if (z->isLeaf())
    return s << ((LeafNode<Elem>*)z)->val();
  else
    return s << ((IntlNode<Elem>*)z)->weight();
}

// HuffTree is a template of two parameters: the element
//  type being coded and a comparator for two such elements.
template <class Elem>
class HuffTree {
private:
  HuffNode<Elem>* theRoot;
public:
  HuffTree(Elem& val, int freq)
    { theRoot = new LeafNode<Elem>(val, freq); }
  HuffTree(HuffTree<Elem>* l, HuffTree<Elem>* r)
    { theRoot = new IntlNode<Elem>(l->root(), r->root()); }
  ~HuffTree() {}
  HuffNode<Elem>* root() { return theRoot; }
  int weight() { return theRoot->weight(); }
};

// Compare two Huffman trees by total weight
template <class Elem> class HHCompare {
public:
  static bool lt(HuffTree<Elem>* x, HuffTree<Elem>* y)
    { return x->weight() < y->weight(); }
  static bool eq(HuffTree<Elem>* x, HuffTree<Elem>* y)
    { return x->weight() == y->weight(); }
  static bool gt(HuffTree<Elem>* x, HuffTree<Elem>* y)
    { return x->weight() > y->weight(); }
};

// Overload for the HuffTree << operator
template <class Elem>
ostream& operator << (ostream& s, HuffTree<Elem>* z)
  { return s << z->weight(); }


class ccCompare {
public:
  static bool lt(char x, char y) { return x < y; }
  static bool eq(char x, char y) { return x == y; }
  static bool gt(char x, char y) { return x > y; }
};


// Read the list of frequencies, make the forest, and set the
// list of entries into the code table.
void read_freqs(SLList<HuffTree<char>*,
				       HHCompare<char> >* forest,
                CodeTable<char, ccCompare>* ct, FILE* fp)
{ // Read a list of strings and frequencies from standard input,
  // building a list of Huffman coding tree nodes
  char buff[100];
  char buff2[100];
  char *ptr;
  char *ptr2;
  int freq;
  HuffTree<char>* temptree;

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
    temptree = new HuffTree<char>(buff2[0], freq);

    // put in the list in sorted order
    // WARNING: This may be considered buggy.  Nodes with equal weight will
    // be put in reverse order of appearance, not in alphabetical order.
    forest->insert(temptree);
  }
}

// Build a Huffman tree from list fl
template <class Elem>HuffTree<Elem>*
buildHuff(SLList<HuffTree<Elem>*, HHCompare<Elem> >* fl) {
  HuffTree<Elem> *temp1, *temp2, *temp3;
  for (fl->setStart(); fl->leftLength()+fl->rightLength()>1;
       fl->setStart()) { // While at least two items left
    fl->remove(temp1);   // Pull first two trees  
    fl->remove(temp2);   //   off the list
    temp3 = new HuffTree<Elem>(temp1, temp2);
    fl->insert(temp3);   // Put the new tree back on list
    delete temp1;        // Must delete the remnants
    delete temp2;        //   of the trees we created
  }
  return temp3;
}


void decode(HuffTree<char>* theTree, char* code, char& msg, int& cnt) {
  HuffNode<char>* currnode = theTree->root();
  while (!currnode->isLeaf()) {
    cnt++;
    if (code[cnt-1] == '0') currnode = currnode->left();
    else if (code[cnt-1] == '1') currnode = currnode->right();
    else Assert(false, "Bad code character");
  }
  msg = (((LeafNode<char>*)currnode)->val())->val();
}

void buildcode(HuffNode<char>* subroot, CodeTable<char, ccCompare>* ct,
	       char* prefix, int level, double& total) {
  if (subroot->isLeaf()) {
    cout << (((LeafNode<char>*)subroot)->val())->val()
         << "\t" << prefix << "\n";
    strcpy(ct->getcode((((LeafNode<char>*)subroot)->val())->val()), prefix);
    total += level * (((LeafNode<char>*)subroot)->val())->weight();
  }
  else {
    prefix[level] = '0';
    prefix[level+1] = '\0';
    buildcode(subroot->left(), ct, prefix, level+1, total);
    prefix[level] = '1';
    prefix[level+1] = '\0';
    buildcode(subroot->right(), ct, prefix, level+1, total);
    prefix[level] = '\0';
  }
}


void do_commands(HuffTree<char>* theTree,
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
        decode(theTree, &buff[currchar], msg, cnt);
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
  SLList<HuffTree<char>*, HHCompare<char> >* forest =
      new SLList<HuffTree<char>*, HHCompare<char> >;
  // This will be the eventual Huffman tree
  HuffTree<char>* theTree;
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
  buildcode(theTree->root(), theTable, prefix, 0, total);
  cout << "Average code length is "
       << total/(double)theTree->weight() << "\n";

  // Finally, do the encode/decode commands to test the system.
  do_commands(theTree, theTable, fp);
  return 0;
}
