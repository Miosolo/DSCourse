#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int MaxVertex = 20;
typedef int vector_index_t;
typedef int weight_t;
weight_t Inf = -1;
typedef struct {
  // Nothing now
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

bool InitGraph(ifstream &infile, MatGraph &G) {
  if (!infile.is_open()) return false;

  infile.seekg(0, ios::beg);
  char buffer[MaxVertex * 5];
  int RowCounter = 0, EdgeCounter = 0;

  while (infile.getline(buffer, sizeof(buffer))) {
    int ColCounter = 0;
    weight_t w = 0;
    for (char *p = buffer; *p;) {
      if (!sscanf(p, "%d", &w))
        break;
      else {
        G.edges[RowCounter][ColCounter] = G.edges[ColCounter][RowCounter] = w;
        EdgeCounter++;
        ColCounter++;
        w = 0;
        while (p) {
          if (*(p++) == ',') break;
        }
      }
    }
    RowCounter++;
  }

  G.v = RowCounter;
  G.e = EdgeCounter;

  return true;
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
}
