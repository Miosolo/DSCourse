#include <algorithm>
#include <iostream>
using namespace std;

#define ElemType int

typedef struct LNode {
  ElemType data;
  LNode *next;
} LNode;

bool RemoveRedun(LNode *const ListHead, LNode *&tail) {
  bool redundancy = false;
  LNode *p = ListHead->next;
  for (; p != tail; p = p->next) {
    if (p->data == tail->data) {
      redundancy = true;
      break;
    }
  }

  if (redundancy) {
    LNode *pretail;
    for (; p != tail; p = p->next) pretail = p;
    pretail->next = tail->next;
    delete p;
  }

  return redundancy;
}
void GetDiffSet(LNode *const WholeList, LNode *const DesubList) {
  if (DesubList->next == NULL) return;

  LNode *tail = DesubList->next, *DesubTail, *pretail = DesubList;
  for (; tail != NULL; tail = pretail->next) {
    if (!RemoveRedun(DesubList, tail)) pretail = tail;
  }
  DesubTail = pretail;

  tail = DesubTail->next = WholeList->next;
  for (; tail != NULL; tail = pretail->next) {
    if (!RemoveRedun(DesubList, tail)) pretail = tail;
  }

  WholeList->next = DesubTail->next;
  return;
}

void GetDiffIncreSet(LNode *const WholeList, LNode *const DesubList) {
  if (DesubList->next == NULL || WholeList->next == NULL) return;

  LNode *WPreTail = WholeList, *WTail = WholeList->next, *DPreTail = DesubList,
        *DTail = DesubList->next;
  while (DTail != NULL) {
    if (DPreTail == DesubList || DTail->data > DPreTail->data) {
      DPreTail = DTail;
      DTail = DTail->next;
    } else {
      DPreTail->next = DTail->next;
      delete DTail;
      DTail = DPreTail->next;
    }
  }

  while (WTail != NULL) {
    if (WTail->data < DTail->data) {
      WPreTail = WTail;
      WTail = WTail->next;
      continue;
    } else if (WTail->data == DTail->data) {
      WPreTail = WTail;
      do {
        WTail = WTail->next;
      } while (WTail != NULL && WTail->data == WPreTail->data);
    }
  }
}

int main(void) {
  LNode *list1 = new LNode;
  list1->data = 0xF0000000;
  LNode *p = list1;
  for (int i = 1; i < 6; i++) {
    p->next = new LNode;
    p->next->data = 2 * i;
    p = p->next;
  }
  p->next = NULL;

  LNode *list2 = new LNode;
  list2->data = 0xF0000000;
  p = list2;
  for (int i = 1; i < 6; i++) {
    p->next = new LNode;
    p->next->data = 2 * i;
    p = p->next;
  }
  p->next = NULL;

  GetDiffSet(list1, list2);

  return 0;
}