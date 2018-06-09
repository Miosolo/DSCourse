#include "graph.h"
using namespace std;

int main() {
  MatGraphWithFlag matg(6);
  InsertNodeToMatGraph(matg);

  AdjGraphWithFlag adjg;
  MatGraphToAdjGraph(matg, adjg);

  cout << "DFS on the adjacent graph recursively: " << endl;
  memset(adjg.visited, 0, sizeof(adjg.visited));
  AdjGraphDFSRecur(adjg, 0);
  cout << "∧"
       << "\n\n";

  cout << "DFS on the adjacent graph non-recursively: " << endl;
  memset(adjg.visited, 0, sizeof(adjg.visited));
  AdjGraphDFSNonRecur(adjg, 0);
  cout << "∧"
       << "\n\n";

  cout << "BFS on the adjacent graph: " << endl;
  memset(adjg.visited, 0, sizeof(adjg.visited));
  AdjGraphBFS(adjg, 0);
  cout << "∧"
       << "\n\n";
  return 0;
}