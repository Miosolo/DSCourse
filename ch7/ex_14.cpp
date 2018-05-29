#include <iostream>
#include <stack>
using namespace std;

typedef int ElemType;
typedef struct BTreeNode {
  ElemType data;
  BTreeNode *lchild, *rchild;
} BTreeNode;

BTreeNode *GetBTreeCopy(BTreeNode *source) {
  stack<BTreeNode *> sts, stt;
  BTreeNode *target = NULL;

  if (source != NULL) {
    sts.push(source);
    stt.push(target);
    BTreeNode *ps, *pt;
    pt = new BTreeNode;

    while (!sts.empty()) {
      ps = sts.top(), sts.pop();
      pt = stt.top(), stt.pop();
      pt->data = ps->data;
      pt->rchild = pt->lchild = NULL;

      if (ps->rchild != NULL) {
        sts.push(ps->rchild);
        pt->rchild = new BTreeNode;
        stt.push(pt->rchild);
      }
      if (ps->lchild != NULL) {
        sts.push(ps->lchild);
        pt->lchild = new BTreeNode;
        stt.push(pt->lchild);
      }
    }
  }

  return target;
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
}