#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

#define ElemType int

typedef struct DNode {
  ElemType data;
  DNode *piror;
  DNode *next;
} DNode;

#ifndef CDNode
#define CDNode DNode
#endif

bool MergeCicularDoubleLink(CDNode *const h1, CDNode *h2, int i) {
  CDNode *InsertPosi;
  if (i < 0) {
    return false;
  } else if (i == 0) {
    InsertPosi = h1;
  } else {
    InsertPosi = h1;
    for (int j = 0; j < i; j++) {
      if (InsertPosi->next == h1) {
        break;
      } else {
        InsertPosi = InsertPosi->next;
      }
    }
  }

  h2->piror->next = InsertPosi->next;
  InsertPosi->next->piror = h2->piror;
  InsertPosi->next = h2->next;
  h2->next->piror = h1;

  delete h2;
  return true;
}

int main(void) {
  DNode *list1 = new DNode;
  list1->data = 0xF0000000;
  DNode *p = list1;
  for (int i = 1; i < 6; i++) {
    p->next = new DNode;
    p->next->piror = p;
    p->next->data = 2 * i - 1;
    p = p->next;
  }
  p->next = list1;
  list1->piror = p;
  cout << "List 1: " << endl;
  for (DNode *p = list1->next; p && p != list1; p = p->next)
    cout << p->data << " <-> ";
  cout << "↺" << endl << endl;

  DNode *list2 = new DNode;
  list2->data = 0xF0000000;
  p = list2;
  for (int i = 1; i < 6; i++) {
    p->next = new DNode;
    p->next->piror = p;
    p->next->data = i * 2;
    p = p->next;
  }
  p->next = list2;
  list2->piror = p;
  cout << "List 2: " << endl;
  for (DNode *p = list2->next; p && p != list2; p = p->next)
    cout << p->data << " <-> ";
  cout << "↺" << endl << endl;

  cout << "Enter your opreation code i: " << endl;
  int i;
  cin >> i;
  if (!MergeCicularDoubleLink(list1, list2, i)) {
    cout << "Merged List: " << endl;
    for (DNode *p = list1->next; p && p != list1; p = p->next)
      cout << p->data << " <-> ";
    cout << "↺" << endl << endl;
  } else {
    cout << "Invalid Opreation. " << endl;
  }

  return 0;
}