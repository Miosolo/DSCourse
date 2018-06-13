#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int MaxVertex = 20;
typedef int weight_t;
weight_t INF = -1;

// DS of Matrix Graph
typedef struct MatGraph {
 private:
  weight_t edges[(1 + MaxVertex) * MaxVertex / 2];

 public:
  int v, e;
  void Assign(int i, int j, weight_t w) {
    if (i < j) swap(i, j);
    edges[i * (i - 1) / 2 + j - 1] = w;
  }
  weight_t GetVal(int i, int j) {
    if (i > MaxVertex || j > MaxVertex)
      return INF;
    else if (i < j)
      swap(i, j);

    return edges[i * (i - 1) / 2 + j - 1];
  }
} MatGraph;

bool InitGraph(ifstream &infile, MatGraph &G) {
  if (!infile.is_open()) return false;

  infile.seekg(0, ios::beg);
  char buffer[MaxVertex * 5];
  int RowCounter = 0, EdgeCounter = 0;
  register weight_t temp;

  for (; infile.getline(buffer, sizeof(buffer) - 1); RowCounter++) {
    char *p = buffer;
    for (int c = 0; c <= RowCounter; c++) {
      sscanf(p, "%d", &temp);
      G.Assign(RowCounter + 1, c + 1, temp);
      if (temp != INF) {
        EdgeCounter++;
      }
      while (*p && *(p++) != ',')
        ;
    }
  }

  G.v = RowCounter;
  G.e = EdgeCounter;
  return true;
}

void Kruskal(MatGraph &G) {
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

  cout << "Edges in the MSL tree: " << endl;
  do {
    for (int i = 0; i < G.e && treeEdgeCount < G.v - 1; i++) {
      if (vSet[arcWArr[i].u] == vSet[arcWArr[i].v]) {
        continue;
      } else {
        vSet[arcWArr[i].u] = vSet[arcWArr[i].v];
        treeEdgeCount++;
        cout << " <" << arcWArr[i].u << ", " << arcWArr[i].v << "> ";
        MSL += arcWArr[i].w;
      }
    }
  } while (treeEdgeCount < G.v - 1);

  cout << "MSL: " << MSL << endl;
  delete[] arcWArr;
  return;
}

int main() {
  ifstream infile;
  infile.open(
      "C:/Users/mx_028/Dropbox/Programming/C++/DSCourse/Exper/"
      "Exp_3/Graph.csv",
      ios::in);

  MatGraph matg;
  matg.v = matg.e = 0;

  InitGraph(infile, matg);

  cout << matg.v << " " << matg.e << endl;
  Kruskal(matg);

  system("Pause");
  return 0;
}
