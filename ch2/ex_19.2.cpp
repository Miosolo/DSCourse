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

void TailInsert(LNode *&tail, ElemType InsetedData) {
  tail->next = new LNode;
  tail->next->data = InsetedData;
  tail->next->next = NULL;
  tail = tail->next;
}
void GetCombinedIncreSet(LNode *h1, LNode *h2, LNode *&h3) {
  LNode *cur = h1->next, *oppo = h2->next;
  h3 = new LNode, h3->next = NULL;
  LNode *tail = h3;

  if (cur == NULL && oppo == NULL) {
    return;
  } else if (cur == NULL || cur->data > oppo->data) {
    swap(cur, oppo);
  }

  while (1) {
    if (oppo == NULL) {
      while (cur != NULL) {
        TailInsert(tail, cur->data);
        ElemType preData = cur->data;
        do {
          cur = cur->next;
        } while (cur != NULL && cur->data == preData);
      }
      break;
    } else if (oppo->data == cur->data) {
      oppo = oppo->next;
      continue;
    } else {
      TailInsert(tail, cur->data);
      ElemType preData = cur->data;
      do {
        cur = cur->next;
      } while (cur != NULL && cur->data == preData);

      if (cur == NULL || cur->data >= oppo->data) swap(cur, oppo);
    }
  }
}

int main(void) {
  srand((unsigned)time(0));

  LNode *list1 = new LNode;
  list1->data = 0xF0000000;
  LNode *p = list1;
  for (int i = 1; i < 6; i++) {
    p->next = new LNode;
    p->next->data = 2 * i;
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
    p->next->data = 2 * i + 1;
    p = p->next;
  }
  p->next = NULL;
  cout << "List 2: " << endl;
  for (LNode *p = list2->next; p; p = p->next) cout << p->data << " -> ";
  cout << " ∧ " << endl;

  LNode *listMI;
  GetCombinedIncreSet(list1, list2, listMI);
  cout << "Merged Incresing List: " << endl;
  for (LNode *p = listMI->next; p; p = p->next) cout << p->data << " -> ";
  cout << " ∧ " << endl;

  return 0;
}