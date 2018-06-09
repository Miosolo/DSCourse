#include "graph.h"
#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;

// Fuction Definitions

static inline int GetMax(int a, int b, int c) {
  int max = (a > b) ? a : b;
  return (max > c) ? max : c;
}

void MatGraphToAdjGraph(MatGraph &matg, AdjGraph &adjg) {
  adjg.e = matg.e;
  adjg.v = matg.v;

  for (int i = 0; i < matg.v; i++)
    for (int j = 0; j < matg.v; j++) {
      if (matg.edges[i][j] != 0 && matg.edges[i][j] != INF) {
        ArcNode *temp = new ArcNode;
        temp->weight = matg.edges[i][j];
        temp->adjVertex = j;
        temp->next = adjg.adjList[i];
        adjg.adjList[i] = temp;
      }
    }

  return;
}

void InsertNodeToMatGraph(MatGraph &G) {
  cout << endl
       << "Matrix Graph Initialization: " << endl
       << "Input the pair of nodes: (from), (to), (weight)" << endl
       << "Enter 0 0 0 to finish" << endl;

  int nodeU, nodeV;
  int edgesCounter = 0;
  weight_t w;

  while (cin >> nodeU >> nodeV >> w) {
    if (!nodeU && !nodeV && !w) break;

    edgesCounter++;
    G.edges[nodeU][nodeV] = w;
    G.e++;
    G.v = GetMax(G.v, nodeU, nodeV);
  }

  cout << edgesCounter << " edges have been sucessfully inserted. " << endl
       << endl;

  return;
}

void DispMatGraph(MatGraph &G) {
  cout<< "Martrix Graph" << endl
                       << "Nodes: " << G.v << "\t"
                       << "Edges: " << G.e << endl
                       << endl;

  cout << "    ";
  for (int i = 0; i < G.v; i++) cout << setw(4) << i;
  cout << endl;

  for (int i = 0; i < G.v; i++) {
    cout << setw(4) << i;
    for (int j = 0; j < G.v; j++) {
      if (G.edges[i][j] != INF)
        cout << setw(4) << G.edges[i][j];
      else
        cout << "   ∞";
    }
    cout << endl;
  }
  cout << endl;
  return;
}

void DispAdjGraph(AdjGraph &A) {
  cout << "Adjacent Graph" << endl
       << "Nodes: " << A.v << "\t"
       << "Edges: " << A.e << endl
       << endl;

  for (int i = 0; i < A.v; i++) {
    cout << "[" << i << "]\t";
    for (ArcNode *p = A.adjList[i]; p; p = p->next)
      cout << p->adjVertex << " -> ";
    cout << "∧" << endl;
  }

  return;
}