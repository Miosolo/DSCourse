#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

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

// Declarations
void MatGraphToAdjGraph(MatGraph &, AdjGraph &);
void InsertNodeToMatGraph(MatGraph &);
void DispMatGraph(MatGraph &);
void DispAdjGraph(AdjGraph &);

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
  cout << "Input the pair of nodes: (from), (to), (weight)" << endl
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

  cout << edgesCounter << " edges have been sucessfully inserted. " << endl;

  return;
}

void DispMatGraph(MatGraph &G) {
  cout << "Nodes: " << G.v << "\t"
       << "Edges: " << G.e << endl
       << endl;

  cout << "    ";
  for (int i = 0; i < G.v; i++) cout << setw(4) << i;
  cout << endl;

  for (int i = 0; i < G.v; i++) {
    cout << setw(4) << i;
    for (int j = 0; j < G.v; i++) {
      if (G.edges[i][j] != INF)
        cout << setw(4) << G.edges[i][j];
      else
        cout << "  ∞";
    }
    cout << endl;
  }
  return;
}

void DispAdjGraph(AdjGraph &A) {
  cout << "Nodes: " << A.v << "\t"
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

int main() {
  MatGraph matg(6);

  InsertNodeToMatGraph(matg);
  DispMatGraph(matg);

  // AdjGraph adjg;
  // MatGraphToAdjGraph(matg, adjg);
  // DispAdjGraph(adjg);

  return 0;
}