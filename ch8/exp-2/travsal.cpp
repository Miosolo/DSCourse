#include <queue>
#include <stack>
#include "graph.h"
using namespace std;

// Function Definitions

void AdjGraphDFSRecur(AdjGraphWithFlag &G, int initV) {
  G.visited[initV] = true;
  cout << initV << " -> ";

  for (ArcNode *p = G.adjList[initV]; p; p = p->next)
    if (!G.visited[p->adjVertex]) AdjGraphDFSRecur(G, p->adjVertex);

  return;
}

void AdjGraphDFSNonRecur(AdjGraphWithFlag &G, int initV) {
  stack<int> st;
  G.visited[initV] = true;
  st.push(initV);

  int cur;
  while (!st.empty()) {
    cur = st.top();
    st.pop();
    cout << cur << " -> ";

    for (ArcNode *p = G.adjList[cur]; p; p = p->next)
      if (!G.visited[p->adjVertex]) {
        G.visited[p->adjVertex] = true;
        st.push(p->adjVertex);
      }
  }
  return;
}

void AdjGraphBFS(AdjGraphWithFlag &G, int initV) {
  queue<int> qu;
  G.visited[initV] = true;
  qu.push(initV);

  int cur;
  while (!qu.empty()) {
    cur = qu.front();
    qu.pop();
    cout << cur << " -> ";

    for (ArcNode *p = G.adjList[cur]; p; p = p->next)
      if (!G.visited[p->adjVertex]) {
        G.visited[p->adjVertex] = true;
        qu.push(p->adjVertex);
      }
  }

  return;
}