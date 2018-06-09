#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

#define INV 0

typedef char ElemType;
typedef struct BTreeNode {
  ElemType data;
  BTreeNode *lchild, *rchild;
} BTreeNode;

void GetStringBTreeRecur(BTreeNode *root, ostringstream &oss) {
  if (root != NULL) {
    oss << root->data;
    if (root->lchild != NULL || root->rchild != NULL) {
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

inline ElemType GetNodeValue(BTreeNode *p) {
  if (!p)
    return INV;
  else
    return p->data;
}

bool IsomorphicTree(BTreeNode *root) {
  if (!root)
    return false;
  else if (!root->rchild && !root->lchild)
    return true;
  else if ((!root->rchild && root->lchild) || (root->rchild && !root->lchild))
    return false;
  else {
    queue<BTreeNode *> qu1, qu2;
    qu1.push(root->lchild);
    qu2.push(root->rchild);

    BTreeNode *p1, *p2;
    while (!qu1.empty()) {
      p1 = qu1.front(), qu1.pop();
      p2 = qu2.front(), qu2.pop();
      bool p2LRSwap;

      if ((GetNodeValue(p1->lchild) == GetNodeValue(p2->lchild)) &&
          (GetNodeValue(p1->rchild) == GetNodeValue(p2->rchild)))
        p2LRSwap = false;
      else if ((GetNodeValue(p1->lchild) == GetNodeValue(p2->rchild)) &&
               (GetNodeValue(p1->rchild) == GetNodeValue(p2->lchild)))
        p2LRSwap = true;
      else
        return false;

      if (!p2LRSwap) {
        if (p1->lchild) {
          qu1.push(p1->lchild);
          qu2.push(p2->lchild);
        }
        if (p1->rchild) {
          qu1.push(p1->rchild);
          qu2.push(p2->rchild);
        }
      } else {
        if (p1->lchild) {
          qu1.push(p1->lchild);
          qu2.push(p2->rchild);
        }
        if (p1->rchild) {
          qu1.push(p1->rchild);
          qu2.push(p2->lchild);
        }
      }
    }

    return true;
  }
}
int main() {
  const char seq[17] = "00aabccbdefgfged";
  BTreeNode NodeList[16];

  for (int i = 1; i <= 15; i++) {
    NodeList[i].data = seq[i];
    NodeList[i].lchild = NodeList[i].rchild = NULL;
  }

  for (int i = 1; i <= 15; i++) {
    if (2 * i <= 15) NodeList[i].lchild = &NodeList[2 * i];
    if (2 * i + 1 <= 15) NodeList[i].rchild = &NodeList[2 * i + 1];
  }

  cout << GetStringBTree(&NodeList[1]);
  cout << endl
       << "Whether the root's 2 subtree is isomorphic is: " << boolalpha
       << IsomorphicTree(&NodeList[1]) << endl;
  return 0;
}
