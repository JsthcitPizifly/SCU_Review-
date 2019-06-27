#include <stdio.h>
#include <ctype.h>

// Used by the mark array
#define UNVISITED 0
#define VISITED 1

#include "link.h"
#include "llist.h"

#include "graph.h"


class Edge {
public:
  int vertex, weight;
  Edge() { vertex = -1; weight = -1; }
  Edge(int v, int w) { vertex = v; weight = w; }
};

// Overload for the Edge << operator
ostream& operator << (ostream& s, Edge e)
  { return(s << "(" << e.vertex << ", " << e.weight << ")"); }

class Graphl : public Graph { // Implement adjacency list
private:
  int numVertex, numEdge;     // Number of vertices, edges
  List<Edge>** vertex; // List headers
  int *mark;                  // Pointer to mark array
public:
  Graphl(int numVert) { // Make graph with numVert vertices
    int i, j;
    numVertex = numVert;  numEdge = 0;
    mark = new int[numVert]; // Initialize mark array
    for (i=0; i<numVertex; i++) mark[i] = UNVISITED;
    // Create and initialize adjacency lists
    vertex = (List<Edge>**) new List<Edge>*[numVertex];
    for (i=0; i<numVertex; i++)
      vertex[i] = new LList<Edge>();
  }

  ~Graphl() {       // Destructor
    delete [] mark; // Return dynamically allocated memory
    for (int i=0; i<numVertex; i++) delete [] vertex[i];
    delete [] vertex;
  }

  int n() { return numVertex; } // Number of vertices
  int e() { return numEdge; }   // Number of edges

  int first(int v) { // Return first neighbor of v
    Edge it;
    vertex[v]->setStart();
    if (vertex[v]->getValue(it)) return it.vertex;
    else return numVertex;  // Return n if none
  }

  int next(int v1, int v2) { // Gete v1's neighbor after v2
    Edge it;
    vertex[v1]->getValue(it);
    if (it.vertex == v2) vertex[v1]->next();
    else { // Start from beginning of list
      vertex[v1]->setStart();
      while (vertex[v1]->getValue(it) && (it.vertex <= v2))
        vertex[v1]->next();
    }
    if (vertex[v1]->getValue(it)) return it.vertex;
    else return numVertex;  // Return n if none
  }

  // Set edge (v1, v2) to wgt
  void setEdge(int v1, int v2, int wgt) {
    Assert(wgt>0, "Illegal weight value");
    Edge it(v2, wgt);
    Edge curr;
    vertex[v1]->getValue(curr);
    if (curr.vertex != v2) // If not already there, search
      for (vertex[v1]->setStart();
           vertex[v1]->getValue(curr); vertex[v1]->next())
        if (curr.vertex >= v2) break;
    if (curr.vertex == v2)  // Clear out the current one
      vertex[v1]->remove(curr);
    else numEdge++;
    vertex[v1]->insert(it);
  }

  void delEdge(int v1, int v2) { // Delete edge (v1, v2)
    Edge curr;
    vertex[v1]->getValue(curr);
    if (curr.vertex != v2)  // If not already there, search
      for (vertex[v1]->setStart();
           vertex[v1]->getValue(curr); vertex[v1]->next())
        if (curr.vertex >= v2) break;
    if (curr.vertex == v2) {  // If not, then there is none
      vertex[v1]->remove(curr);
      numEdge--;
    }
  }

  int weight(int v1, int v2) { // Return weight of (v1, v2)
    Edge curr;
    vertex[v1]->getValue(curr);
    if (curr.vertex != v2) // If not already there, search
      for (vertex[v1]->setStart();
           vertex[v1]->getValue(curr); vertex[v1]->next())
        if (curr.vertex >= v2) break;
    if (curr.vertex == v2)
      return curr.weight;
    else
      return 0;  // No such edge
  }

  int getMark(int v) { return mark[v]; }
  void setMark(int v, int val) { mark[v] = val; }
};

#include "graphutil.cpp"
