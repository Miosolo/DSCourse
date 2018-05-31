#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

typedef struct HuffmanNode {
  char data;
  int weight;
  HuffmanNode *parent, *lchild, *rchild;

 public:
  HuffmanNode(char d = '\0', int w = 0, HuffmanNode* p = NULL,
              HuffmanNode* l = NULL, HuffmanNode* r = NULL)
      : data(d), weight(w), parent(p), lchild(l), rchild(r) {}
} HuffmanNode;

typedef struct HuffmanTree {
  int AmountOfData;
  HuffmanNode* root;

 public:
  HuffmanTree(int n = 0, HuffmanNode* r = NULL) : AmountOfData(n), root(r) {}
} HuffmanTree;

int Myisalnum(char);
HuffmanTree* InitHuffmanTree(char*);
void InsertNode(list<HuffmanNode*>& ls, HuffmanNode& ele);
void ShowHuffmanCode(HuffmanTree&);

inline int Myisalnum(char c) {
  if ('0' <= c && c <= '9')
    return 1;
  else if ('a' <= c && c <= 'z')
    return 2;
  else if ('A' <= c && c <= 'Z')
    return 3;
  else
    return 0;
}

inline void InsertNode(list<HuffmanNode*>& ls, HuffmanNode* ele) {
  if (ls.empty()) {
    ls.assign(1, ele);
    return;
  } else if (ele->weight <= (*ls.begin())->weight) {
    ls.insert(ls.begin(), ele);
    return;
  }

  list<HuffmanNode*>::iterator iter, niter;

  for (iter = ls.begin(), niter = next(iter); niter != ls.end();
       iter++, niter++) {
    if ((*iter)->weight <= ele->weight && ele->weight < (*niter)->weight) break;
  }

  ls.insert(niter, ele);
  return;
}

HuffmanTree* InitHuffmanTree(char* RawData) {
  if (RawData[0] == 0) return NULL;

  typedef struct TempHuffmanNode {
    char data;
    int amount = 0;
  } TempHuffmanNode;
  TempHuffmanNode TempHuffmanNodeList[10 + 26 * 2];
  const int NumBegin = 0, LowerLetterBeg = 10, UpperLetterBeg = 36;
  const int IsNum = 1, IsLowerLetter = 2, IsUpperLetter = 3;

  for (int i = 0; i < 10 + 26 * 2; i++) {
    if (NumBegin <= i && i < LowerLetterBeg)
      TempHuffmanNodeList[i].data = i + '0';
    else if (LowerLetterBeg <= i && i < UpperLetterBeg)
      TempHuffmanNodeList[i].data = i - LowerLetterBeg + 'a';
    else
      TempHuffmanNodeList[i].data = i - UpperLetterBeg + 'A';
  }

  for (int i = 0; RawData[i] != 0; i++) {
    switch (Myisalnum(RawData[i])) {
      case IsNum:
        TempHuffmanNodeList[NumBegin + RawData[i] - '0'].amount++;
        break;
      case IsLowerLetter:
        TempHuffmanNodeList[LowerLetterBeg + RawData[i] - 'a'].amount++;
        break;
      case IsUpperLetter:
        TempHuffmanNodeList[UpperLetterBeg + RawData[i] - 'A'].amount++;
        break;
    }
  }

  cout << "Task 1: Analyse the characers' frenquency:" << endl
       << "Source: Moon Stone" << endl
       << "---------------" << endl;

  for (int i = 0; i < 10 + 26 * 2; i++) {
    cout << TempHuffmanNodeList[i].data << "\t" << TempHuffmanNodeList[i].amount
         << endl;
  }
  cout << "---------------" << endl << endl;

  list<HuffmanNode*> HuffmanNodePendingList;

  for (int i = 0; i < 10 + 26 * 2; i++) {
    HuffmanNode* NewLeaf = new HuffmanNode(TempHuffmanNodeList[i].data,
                                           TempHuffmanNodeList[i].amount);
    if (i == 0)
      HuffmanNodePendingList.assign(1, NewLeaf);
    else {
      InsertNode(HuffmanNodePendingList, NewLeaf);
    }
  }

  while (HuffmanNodePendingList.size() > 1) {
    HuffmanNode* NewInterNode = new HuffmanNode();
    NewInterNode->lchild = HuffmanNodePendingList.front();
    HuffmanNodePendingList.pop_front();
    NewInterNode->rchild = HuffmanNodePendingList.front();
    HuffmanNodePendingList.pop_front();
    NewInterNode->weight =
        NewInterNode->lchild->weight + NewInterNode->rchild->weight;
    NewInterNode->lchild->parent = NewInterNode->rchild->parent = NewInterNode;

    InsertNode(HuffmanNodePendingList, NewInterNode);
  }

  HuffmanTree* HT =
      new HuffmanTree(10 + 26 * 2, HuffmanNodePendingList.front());

  return HT;
}

void ShowHuffmanCode(HuffmanTree& HT) {
  stack<HuffmanNode*> NodeSt;
  vector<bool> trace;
  NodeSt.push(HT.root);
  HuffmanNode* p;

  cout << "Task 2: Show the Huffman Code: " << endl
       << "---------------" << endl;

  while (!NodeSt.empty()) {
    p = NodeSt.top();
    NodeSt.pop();

    if (p->data != 0) {
      cout << p->data << "\t";

      trace.clear();
      HuffmanNode* q = p;
      while (q != HT.root) {
        if (q == q->parent->lchild)
          trace.push_back(0);
        else
          trace.push_back(1);
        q = q->parent;
      }

      for (vector<bool>::iterator iter = --trace.end();; iter--) {
        cout << *iter;
        if (iter == trace.begin()) break;
      }
      cout << endl;
    } else {
      NodeSt.push(p->rchild);
      NodeSt.push(p->lchild);
    }
  }
  cout << "---------------" << endl;
  return;
}

const int MaxFileLength = (int)1e7;
char buf[MaxFileLength];

int main() {
  FILE* raw = fopen("./The_Moonstone.txt", "rb+");
  if (raw == NULL) return 1;

  int len = fread(buf, 1, MaxFileLength, raw);
  buf[len] = 0;
  HuffmanTree* HT;

  HT = InitHuffmanTree(buf);
  ShowHuffmanCode(*HT);

  system("Pause");
  return 0;
}
