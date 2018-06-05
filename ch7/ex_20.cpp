#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
#define MAXNODES 100

typedef char ElemType;
typedef struct BTreeNode {
  ElemType data;
  BTreeNode *lchild, *rchild;
} BTreeNode;

bool IsCompleteBTree(BTreeNode *root) {
  if (!root) return false;

  vector<BTreeNode *> SeqTree(MAXNODES, 0x0);
  SeqTree[1] = root;

  for (int depth = 0;; depth++) {
    bool AllLeaves, full;

    for (int i = pow(2, depth); i < pow(2, depth + 1); i++) {
      AllLeaves = true, full = true;

      if (!SeqTree[i]) {
        if (i + 1 <= pow(2, depth + 1) && SeqTree[i + 1]) return false;
        full = false;
      } else if (SeqTree[i]->lchild || SeqTree[i]->rchild) {
        AllLeaves = false;
        if (SeqTree[i]->lchild) SeqTree[2 * i] = SeqTree[i]->lchild;
        if (SeqTree[i]->rchild) SeqTree[2 * i + 1] = SeqTree[i]->rchild;
      }

      if (!AllLeaves && !full) return false;
    }
    // end inner-for
    if (AllLeaves) return true;
  }

  return false;
}

int main() {
  BTreeNode NodeList[27];
  for (int i = 1; i <= 26; i++) {
    NodeList[i].data = (i - 1) + 'a';
    NodeList[i].lchild = NodeList[i].rchild = NULL;
  }

  for (int i = 1; i <= 26; i++) {
    /*if (i == 5) {
      NodeList[i].lchild = NodeList[i].rchild = NULL;
      continue;
    }*/
    if (2 * i <= 25) NodeList[i].lchild = &NodeList[2 * i];
    if (2 * i + 1 <= 25) NodeList[i].rchild = &NodeList[2 * i + 1];
  }

  cout << boolalpha << IsCompleteBTree(&NodeList[1]) << endl;

  return 0;
}