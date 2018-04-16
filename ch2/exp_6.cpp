#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

#define ElemType int

typedef struct LNode {
  ElemType data;
  LNode *next;
} LNode;

bool Partition(LNode *const L, ElemType pivot) {
  if (L->next == NULL) return false;

  LNode *LLarge = new LNode;
  LLarge->next = NULL;

  LNode *p, *pre;
  for (p = L->next, pre = L; p != NULL;) {
    if (p->data > pivot) {
      pre->next = p->next;
      p->next = LLarge->next;
      LLarge->next = p;
      p = pre->next;
    } else {
      pre = p;
      p = p->next;
    }
  }

  pre->next = LLarge->next;
  delete LLarge;
  return true;
}

int main(void) {
  LNode *list = new LNode;
  list->data = 0xF0000000;
  LNode *p = list;
  for (int i = 1; i < 6; i++) {
    p->next = new LNode;
    p->next->data = 10 - i;
    p = p->next;
  }
  p->next = NULL;

  Partition(list, 7);

  for (LNode *p = list->next; p != NULL; p = p->next) {
    cout << p->data << " ";
  }
  cout << endl;
}