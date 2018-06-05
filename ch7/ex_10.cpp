#include <algorithm>
#include <iostream>
#include <sstream>
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

  cout << GetStringBTree(&NodeList[1]) << endl;
}
