#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

typedef char ElemType;
typedef struct BTreeNode {
  ElemType data;
  BTreeNode *lchild, *rchild;
} BTreeNode;

void GetStringBTreeRecur(BTreeNode *root, ostringstream &oss) {
  if (root != NULL) {
    oss << root->data;
    if (root->rchild != NULL || root->rchild != NULL) {
      oss << "(";
      if (root->lchild != NULL) GetStringBTreeRecur(root->lchild, oss);
      oss << ",";
      if (root->rchild != NULL) GetStringBTreeRecur(root->rchild, oss);
      oss << ")";
    }
  }
  return;
}

string GetStringBTree(BTreeNode *root) {
  ostringstream oss;

  if (root != NULL) {
    oss << "(";
    GetStringBTreeRecur(root, oss);
    oss << ")";
  }

  return oss.str();
}

BTreeNode *GetBTreeCopy(BTreeNode *source) {
  stack<BTreeNode *> sts, stt;
  BTreeNode *target = new BTreeNode;

  if (source != NULL) {
    sts.push(source);
    stt.push(target);
    BTreeNode *ps, *pt;

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
  BTreeNode NodeList[27];
  for (int i = 1; i <= 26; i++) {
    NodeList[i].data = (i - 1) + 'a';
    NodeList[i].lchild = NodeList[i].rchild = NULL;
  }

  for (int i = 1; i <= 26; i++) {
    if (2 * i <= 25) NodeList[i].lchild = &NodeList[2 * i];
    if (2 * i + 1 <= 25) NodeList[i].rchild = &NodeList[2 * i + 1];
  }

  cout << "Oringinal Tree: " << GetStringBTree(&NodeList[1]) << endl << endl;
  cout << "Copied Tree:" << GetStringBTree(GetBTreeCopy(&NodeList[1])) << endl;

  return 0;
}
