#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

const int MaxVertex = 20;
typedef int weight_t;
weight_t Inf = 0xe0000000;
typedef struct {
  bool visited = 0;
} InfoType;

// DS of Matrix Graph
typedef struct {
  int no;
  InfoType info;
} MatGraphVertex;

typedef struct MatGraph {
  weight_t edges[MaxVertex][MaxVertex];
  int v, e;
  MatGraphVertex vertex[MaxVertex];
} MatGraph;

// DS of Adjacent Graph

struct VertexNode;
typedef struct ArcNode {
  weight_t weight;
  VertexNode *AdjVertex;
  ArcNode *next;

  ~ArcNode() {
    if (this->next) delete this->next;
  }
} ArcNode;

typedef struct VertexNode {
  InfoType info;
  ArcNode *FirstArc;
} VertexNode;

typedef struct AdjGraph {
  VertexNode AdjList[MaxVertex];
  int v, e;

  ~AdjGraph() {
    for (int i = 0; i < v; i++) delete AdjList[i].FirstArc;
  }
} AdjGraph;

void MatGraphToAdjGraph(MatGraph &matg, AdjGraph &adjg) {
  adjg.e = matg.e;
  adjg.v = matg.v;

  for (int i = 0; i < adjg.v; i++) adjg.AdjList[i].FirstArc = NULL;

  for (int i = 0; i < matg.v; i++)
    for (int j = 0; j < matg.v; j++) {
      if (matg.edges[i][j] != 0 && matg.edges[i][j] != Inf) {
        ArcNode *temp = new ArcNode;
        temp->weight = matg.edges[i][j];
        temp->AdjVertex = &adjg.AdjList[j];
        temp->next = adjg.AdjList[i].FirstArc;
        adjg.AdjList[i].FirstArc = temp;
      }
    }

  return;
}

void AdjGraghBFS(AdjGraph &G, int InitV) {
  queue<VertexNode *> qu;
  G.AdjList[InitV].info.visited = true;
  qu.push(&G.AdjList[InitV]);

  VertexNode *p;
  while (!qu.empty()) {
    p = qu.front();
    qu.pop();
    cout << p - G.AdjList << " ";

    ArcNode *q = p->FirstArc;
    while (q) {
      if (!q->AdjVertex->info.visited) {
        q->AdjVertex->info.visited = true;
        qu.push(q->AdjVertex);
      }
      q = q->next;
    }
  }

  return;
}

int main() {
  weight_t edges[MaxVertex][MaxVertex] = {
      {0, 1, 1, Inf}, {Inf, 0, 1, Inf}, {Inf, Inf, 0, 1}, {1, Inf, Inf, 0}};
  MatGraph matg;
  matg.v = 4;
  matg.e = 5;
  memcpy(matg.edges, edges, sizeof(edges));

  AdjGraph adjg;
  MatGraphToAdjGraph(matg, adjg);
  AdjGraghBFS(adjg, 0);

  return 0;
}
