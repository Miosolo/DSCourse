#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <cstring>
#include <iostream>

// constants
const int MAX_VERTEX = 20;
typedef int weight_t;
const weight_t INF = -1;

// DS of Matrix Graph
typedef struct MatGraph {
  weight_t edges[MAX_VERTEX][MAX_VERTEX];
  int v, e;

  MatGraph(int nodes = 0) : v(nodes), e(0) {
    memset(edges, INF, sizeof(edges));
  };
} MatGraph;

// DS of Adjacent Graph
typedef struct ArcNode {
  weight_t weight;
  int adjVertex;
  ArcNode *next;

  ~ArcNode() {
    if (next) delete next;
  }
} ArcNode;

typedef struct AdjGraph {
  ArcNode *adjList[MAX_VERTEX];
  int v, e;

  AdjGraph(int nodes = 0) : v(nodes), e(0) {
    for (int i = 0; i < MAX_VERTEX; i++) adjList[i] = NULL;
  }
  ~AdjGraph() {
    for (int i = 0; i < v; i++) delete adjList[i];
  }
} AdjGraph;

// Derived Structs
typedef struct AdjGraphWithFlag : public AdjGraph {
  bool visited[MAX_VERTEX];

  AdjGraphWithFlag(int nodes = 0) : AdjGraph(nodes) {
    memset(visited, 0, sizeof(visited));
  }
} AdjGraphWithFlag;

typedef struct MatGraphWithFlag : public MatGraph {
  bool visited[MAX_VERTEX];

  MatGraphWithFlag(int nodes = 0) : MatGraph(nodes) {
    memset(visited, 0, sizeof(visited));
  }
} MatGraphWithFlag;

// Fuction Declarations
void MatGraphToAdjGraph(MatGraph &, AdjGraph &);
void InsertNodeToMatGraph(MatGraph &);
void AdjGraphDFSRecur(AdjGraphWithFlag &, int);
void AdjGraphDFSNonRecur(AdjGraphWithFlag &, int);
void AdjGraphBFS(AdjGraphWithFlag &, int);

#endif
