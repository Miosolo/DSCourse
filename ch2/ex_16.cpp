#include <iostream>
using namespace std;

#define ElemType int

typedef struct DNode {
  ElemType data;
  int freq;
  DNode *piror;
  DNode *next;
} DNode;

bool LocateNode(DNode *const h, ElemType x) {
  if (h->next == NULL) return false;

  DNode *freqHead = h;
  int xFound = 0;

  while (1) {
    int ComFreq = freqHead->next->freq;
    DNode *p;

    for (p = freqHead->next; p != NULL && p->freq == ComFreq; p = p->next) {
      if (p->data == x) {
        p->freq++;

        DNode *pre = p->piror;
        p->next->piror = pre;
        pre->next = p->next;
        freqHead->next->piror = p;
        p->next = freqHead->next;
        p->piror = freqHead;
        freqHead->next = p;
      }
    }
    if (p != NULL) {
      freqHead = p->piror;
    } else {
      break;
    }
  }

  return (xFound > 0) ? true : false;
}

int main(void) {
  DNode *DH = new DNode, *p = DH;
  DH->piror = NULL, DH->data = DH->freq = -1;

  for (int i = 0; i < 10; i++) {
    p->next = new DNode;
    p->next->piror = p;
    p->next->freq = (10 - i) / 2;
    p->next->data = i;
    p = p->next;
  }
  p->next = NULL;

  LocateNode(DH, 2);

  return 0;
}