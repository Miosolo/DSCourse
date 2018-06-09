#include <iostream>
#include <stack>
using namespace std;

typedef char ElemType;

typedef struct BTreeNode {
  ElemType data;
  BTreeNode *lchild, *rchild;
} BTreeNode;

ElemType GetMinNode(BTreeNode *root) {
  stack<BTreeNode *> st;
  ElemType min = 'z';

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
  BTreeNode NodeList[27];
  for (int i = 1; i <= 26; i++) {
    NodeList[i].data = (i - 1) + 'a';
    NodeList[i].lchild = NodeList[i].rchild = NULL;
  }

  for (int i = 1; i <= 26; i++) {
    if (2 * i <= 25) NodeList[i].lchild = &NodeList[2 * i];
    if (2 * i + 1 <= 25) NodeList[i].rchild = &NodeList[2 * i + 1];
  }

  cout << "Minimum node: "<< GetMinNode(&NodeList[1]) << endl;
}