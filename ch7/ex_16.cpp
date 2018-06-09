#include <iostream>
#include <stack>
using namespace std;

typedef char ElemType;
typedef struct BTreeNode {
  ElemType data;
  BTreeNode *lchild, *rchild;
} BTreeNode;

bool IsBTreeBrother(BTreeNode *root, ElemType x, ElemType y) {
  stack<BTreeNode *> st;
  BTreeNode *cur, *pre;

  cur = root, pre = NULL;
  while (!st.empty() || cur) {
    while (cur) {
      st.push(cur);
      cur = cur->lchild;
    }
    if (!st.empty()) {
      cur = st.top();
      if (cur->rchild == NULL || cur->rchild == pre) {
        if (cur->data == x || cur->data == y) {
          st.pop();
          BTreeNode *p = st.top();
          if ((p->lchild->data == x && p->rchild->data == y) ||
              (p->lchild->data == y && p->rchild->data == x))
            return true;
          else
            return false;
        } else {
          pre = cur;
          cur = NULL;
          st.pop();
        }
      } else {
        cur = cur->rchild;
      }
    }
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
    if (2 * i <= 25) NodeList[i].lchild = &NodeList[2 * i];
    if (2 * i + 1 <= 25) NodeList[i].rchild = &NodeList[2 * i + 1];
  }

  cout << "Enter a pair of values: " << endl;
  ElemType e1, e2;
  cin >> e1 >> e2;
  cout << boolalpha << IsBTreeBrother(&NodeList[1], e1, e2) << endl;

  return 0;
}