#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

#define ElemType int

typedef struct LNode {
  ElemType data;
  LNode *next;
} LNode;

bool MergeLList(LNode *const hx, LNode *const hy, LNode *&NewList) {
  if (hx == NULL && hy == NULL) {
    return false;
  } else if (hx == NULL || hy == NULL) {
    NewList = hx ? hx : hy;
    return true;
  } else {
    LNode *newend = NewList;
    newend->next = NULL;

    LNode *px = hx->next, *prex = hx, *py = hy->next, *prey = hy;
    for (; px != NULL && py != NULL;) {
      prex->next = px->next;
      px->next = newend->next;
      newend->next = px;
      px = prex->next;
      newend = newend->next;

      prey->next = py->next;
      py->next = newend->next;
      newend->next = py;
      py = prey->next;
      newend = newend->next;
    }

    if (px == NULL && py == NULL) {
      ;
    } else {
      newend->next = (px) ? px : py;
    }

    return true;
  }
}

int main(void) {
  LNode *list1 = new LNode;
  list1->data = 0xF0000000;
  LNode *p = list1;
  for (int i = 1; i < 10; i++) {
    p->next = new LNode;
    p->next->data = 2 * i - 1;
    p = p->next;
  }
  p->next = NULL;

  LNode *list2 = new LNode;
  list2->data = 0xF0000000;
  p = list2;
  for (int i = 1; i < 3; i++) {
    p->next = new LNode;
    p->next->data = 2 * i;
    p = p->next;
  }
  p->next = NULL;

  LNode *MergedList = new LNode;
  if (MergeLList(list1, list2, MergedList))
    for (p = MergedList->next; p != NULL; p = p->next) {
      cout << p->data << " ";
    }
  cout << endl;

  return 0;
}