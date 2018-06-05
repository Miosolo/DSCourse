#include <iostream>
#include <stack>
using namespace std;

typedef char ElemType;
typedef struct BTreeNode {
  ElemType data;
  BTreeNode *lchild, *rchild;
} BTreeNode;

#define INV 0

void ShowChildren(BTreeNode *root, ElemType ele = INV, bool print = false) {
  if (!root) return;

  stack<BTreeNode *> st;
  BTreeNode *p = root;

  while (!st.empty() || p) {
    while (p) {
      if (ele != INV && p->data == ele && !print) {
        cout << "Element " << p->data << "'s children: " << endl;
        ShowChildren(p, INV, true);
        return;
      } else {
        if (print && p->data != root->data) cout << p->data << " ";
        st.push(p);
        p = p->lchild;
      }
    }

    if (!st.empty()) {
      p = st.top();
      p = p->rchild;
      st.pop();
    }
  }
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

  ShowChildren(&NodeList[1], 'c');

  return 0;
}