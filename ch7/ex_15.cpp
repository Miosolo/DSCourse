#include <iostream>
#include <queue>
using namespace std;

typedef char ElemType;
typedef struct BTreeNode {
  ElemType data;
  BTreeNode *lchild, *rchild;
} BTreeNode;
typedef struct BTNodePtrWithDepth {
  BTreeNode *node;
  int depth;
  BTNodePtrWithDepth(BTreeNode *n, int d) : node(n), depth(d) {}
} BTNodePtrWithDepth;

int GetLeafAmountInDepth(BTreeNode *root, int n) {
  if (root == NULL) return 0;

  queue<BTNodePtrWithDepth *> qu;
  int leaves = 0;

  BTNodePtrWithDepth *p = new BTNodePtrWithDepth(root, 0);
  qu.push(p);

  while (!qu.empty()) {
    p = qu.front();
    qu.pop();
    if (p->depth < n) {
      if (p->node->lchild != NULL) {
        BTNodePtrWithDepth *q =
            new BTNodePtrWithDepth(p->node->lchild, p->depth + 1);
        qu.push(q);
      }
      if (p->node->rchild != NULL) {
        BTNodePtrWithDepth *q =
            new BTNodePtrWithDepth(p->node->rchild, p->depth + 1);
        qu.push(q);
      }
    } else if (p->depth == n && p->node->lchild == NULL &&
               p->node->rchild == NULL) {
      leaves++;
    }
  }

  return leaves;
}

int main() {
  BTreeNode NodeList[27];
  for (int i = 1; i <= 26; i++) {
    NodeList[i].data = (i - 1) + 'a';
    NodeList[i].lchild = NodeList[i].rchild = NULL;
  }

  for (int i = 1; i <= 26; i++) {
    if (2 * i <= 25) NodeList[i].lchild = &NodeList[2 * i];
    if (2 * i + 1 <= 25) NodeList[i].rchild = &NodeList[2 * i + 1];
  }

  cout << GetLeafAmountInDepth(&NodeList[1], 4) << endl;

  return 0;
}