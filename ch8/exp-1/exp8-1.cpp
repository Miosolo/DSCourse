#include <iostream>
#include "graph.h"
using namespace std;

int main() {
  MatGraph matg(6);

  InsertNodeToMatGraph(matg);
  DispMatGraph(matg);

  AdjGraph adjg;
  MatGraphToAdjGraph(matg, adjg);
  DispAdjGraph(adjg);

  return 0;
}