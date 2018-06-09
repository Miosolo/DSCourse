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

void GetCombinedSet(LNode *const h1, LNode *const h2, LNode *&h3) {
  LNode *p = h1;
  h3 = new LNode;
  h3->next = NULL;

  bool JumptoH2 = false;
  while (1) {
    if ((p = p->next)) {
      for (LNode *pnew = h3; pnew != NULL; pnew = pnew->next) {
        if (pnew->next == NULL || pnew->next->data > p->data) {
          LNode *NewNode = new LNode;
          NewNode->data = p->data;
          NewNode->next = pnew->next;
          pnew->next = NewNode;
          break;
        } else if (pnew->next->data == p->data) {
          break;
        }
      }
    } else if (!JumptoH2) {
      p = h2;
      JumptoH2 = true;
    } else {
      break;
    }
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

  LNode *listM;
  GetCombinedSet(list1, list2, listM);
  cout << "Merged List: " << endl;
  for (LNode *p = listM->next; p; p = p->next) cout << p->data << " -> ";
  cout << " ∧ " << endl;

  return 0;
}
