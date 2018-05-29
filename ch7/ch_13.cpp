#include <iostream>
#include <stack>
using namespace std;

typedef int ElemType;
const ElemType INF = 0xddddddd;

typedef struct BTreeNode {
  ElemType data;
  BTreeNode *lchild, *rchild;
} BTreeNode;

ElemType GetSingleBranchNodeAmount(BTreeNode *root) {
  stack<BTreeNode *> st;
  ElemType min = INF;

  if (root != NULL) {
    st.push(root);
    BTreeNode *p;

    while (!st.empty()) {
      p = st.top(), st.pop();
      if (p->data < min) min = p->data;

      if (p->rchild != NULL) st.push(p->rchild);
      if (p->lchild != NULL) st.push(p->lchild);
    }
  }

  return min;
}

int main() {
  BTreeNode NodeList[32];
  for (int i = 1; i <= 31; i++) {
    NodeList[i].data = i;
    NodeList[i].lchild = NodeList[i].rchild = NULL;
  }

  for (int i = 1; i <= 31; i++) {
    if (2 * i <= 31) NodeList[i].lchild = &NodeList[2 * i];
    if (2 * i + 1 <= 31) NodeList[i].rchild = &NodeList[2 * i + 1];
  }

  cout << GetSingleBranchNodeAmount(&NodeList[1]) << endl;
}