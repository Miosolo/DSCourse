#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

#define ElemType int

typedef struct LNode {
  ElemType data;
  LNode *next;
} LNode;

bool RemoveRedun(LNode *const ListHead, LNode *&tail) {
  bool redun = false;
  LNode *p = ListHead->next;
  for (; p != tail; p = p->next) {
    if (p->data == tail->data) {
      redun = true;
      break;
    }
  }

  if (redun) {
    LNode *pretail = NULL;
    for (; p != tail; p = p->next) pretail = p;
    pretail->next = tail->next;
    delete p;
  }

  return redun;
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
  for (LNode *p = DesubList; p && p != WholeList->next; p = p->next) {
    LNode *t = p->next;
    delete p;
    p = t;
  }

  return;
}

int main(void) {
  srand((unsigned)time(0));

  LNode *list1 = new LNode;
  list1->data = 0xF0000000;
  LNode *p = list1;
  for (int i = 1; i < 6; i++) {
    p->next = new LNode;
    p->next->data = rand() % 20;
    p = p->next;
  }
  p->next = NULL;
  cout << "List 1: " << endl;
  for (LNode *p = list1->next; p; p = p->next) cout << p->data << " -> ";
  cout << " ∧ " << endl;

  LNode *list2 = new LNode;
  list2->data = 0xF0000000;
  p = list2;
  for (int i = 1; i < 6; i++) {
    p->next = new LNode;
    p->next->data = rand() % 20;
    p = p->next;
  }
  p->next = NULL;
  cout << "List 2: " << endl;
  for (LNode *p = list2->next; p; p = p->next) cout << p->data << " -> ";
  cout << " ∧ " << endl;

  GetDiffSet(list1, list2);
  cout << "List 1 - List 2: " << endl;
  for (LNode *p = list1->next; p; p = p->next) cout << p->data << " -> ";
  cout << " ∧ " << endl;

  return 0;
}
