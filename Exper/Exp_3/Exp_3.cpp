#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

typedef int weight_t;
const weight_t INF = -1;

// DS of Matrix Graph
typedef struct MatGraph {
 private:
  weight_t *edges;

 public:
  int v, e;

 public:
  MatGraph(int nodes) : v(nodes), e(0) {
    edges = new weight_t[(1 + nodes) * nodes / 2];
    memset(edges, INF, sizeof(weight_t) * ((1 + nodes) * nodes / 2));
  }
  ~MatGraph() { delete[] edges; }

  void Assign(int i, int j, weight_t w) {
    if (i < j) swap(i, j);
    edges[i * (i - 1) / 2 + j - 1] = w;
  }
  weight_t GetVal(int i, int j) {
    if (i > v || j > v)
      return INF;
    else if (i < j)
      swap(i, j);

    return edges[i * (i - 1) / 2 + j - 1];
  }
} MatGraph;

// Function Declarations
bool isConnectedGraph(MatGraph &);
void InsertEdge(MatGraph &, int, int, weight_t);
void Kruskal(MatGraph &);

// Function Definitions
bool isConnectedGraph(MatGraph &G) {
  queue<int> nodeQ;
  bool *visited = new bool[G.v + 1];
  memset(visited, 0, sizeof(bool) * (G.v + 1));
  int nodeCt = 0, cur;
  nodeQ.push(1);
  visited[1] = true;

  while (!nodeQ.empty()) {
    cur = nodeQ.front();
    nodeQ.pop();
    nodeCt++;

    for (int i = 1; i <= G.v; i++) {
      if (G.GetVal(cur, i) != INF && !visited[i]) {
        visited[i] = true;
        nodeQ.push(i);
      }
    }
  }

  delete[] visited;
  return nodeCt == G.v;
}

void InsertEdge(MatGraph &G, int u, int v, weight_t w) {
  bool toInsert = true;

  if ((u > G.v || v > G.v) || u == v) {
    cout << "Error: Please input different nodes from 1 to " << G.v << ". "
         << endl;
    toInsert = false;
  } else if (G.GetVal(u, v) != INF) {
    cout << "Warning: Duplicate edges, cover with new weight? (y / n)  ";
    char control;
    cin >> control;
    toInsert = (control == 'y') ? true : false;
  }

  if (toInsert) {
    G.Assign(u, v, w);
    G.e++;
  }

  return;
}

void Kruskal(MatGraph &G) {
  if (!isConnectedGraph(G)) {
    cout << "Error: The graph is not connected." << endl;
    return;
  } else
    cout << endl << "Check: The graph is connected.";

  typedef struct Arc {
    int u, v;
    weight_t w;
  } Arc;

  Arc *arcWArr = new Arc[G.e];
  Arc *cur = arcWArr;
  register weight_t tempw;
  for (int i = 1; i <= G.v; i++) {
    for (int j = 1; j <= i; j++) {
      if ((tempw = G.GetVal(i, j)) != INF) {
        cur->u = i;
        cur->v = j;
        cur->w = tempw;
        cur++;
      }
    }
  }

  sort(arcWArr, arcWArr + G.e, [](Arc &a1, Arc &a2) { return a1.w < a2.w; });

  int *vSet = new int[G.v];
  for (int i = 0; i < G.v; i++) vSet[i] = i;

  int treeEdgeCount = 0;
  weight_t MSL = 0;

  cout << endl << "Edges in the MST: " << endl << " (u, v) : weight" << endl;
  do {
    for (int i = 0; i < G.e && treeEdgeCount < G.v - 1; i++) {
      if (vSet[arcWArr[i].u] == vSet[arcWArr[i].v]) {
        continue;
      } else {
        vSet[arcWArr[i].u] = vSet[arcWArr[i].v];
        treeEdgeCount++;
        cout << " (" << arcWArr[i].u << ", " << arcWArr[i].v
             << ") : " << arcWArr[i].w << endl;
        MSL += arcWArr[i].w;
      }
    }
  } while (treeEdgeCount < G.v - 1);

  cout << "Minimum sum of weight: " << MSL << endl;
  delete[] arcWArr;
  return;
}

int main() {
  cout << "Enter the number of nodes in the graph: ";
  int n;
  cin >> n;
  MatGraph matg(n);

  int u, v;
  weight_t w;
  cout << "Insert the edges: enter u, v and w (enter \"0 0 0\" to finish. "
       << endl;
  while (cin >> u >> v >> w) {
    if (!u && !v && !w)
      break;
    else
      InsertEdge(matg, u, v, w);
  }

  cout << endl
       << "Graph initialized." << endl
       << "Amount of nodes: " << matg.v << endl
       << "Amount of edges: " << matg.e << endl;

  Kruskal(matg);

  system("Pause");
  return 0;
}
