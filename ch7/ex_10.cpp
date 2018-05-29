#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

typedef int ElemType;
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

  cout << GetStringBTree(&NodeList[1]) << endl;
}
