#include <iostream>
using namespace std;

typedef char ElemType;
typedef struct LNode {
  ElemType data;
  LNode *next;
} LNode;
typedef LNode LStrNode;

void DeleteChar(LStrNode *str, char elem) {
  LStrNode *cur, *pre;

  cur = str->next;
  while (cur->data == elem) cur = cur->next;
  pre = str->next;

  while (cur != NULL) {
    if (cur->data == elem) {
      pre->next = cur->next;
      delete cur;
      cur = pre->next;
    } else {
      pre = cur;
      cur = cur->next;
    }
  }

  return;
}

int main(void) {
  char str[] = "12A6343AAGA";
  LStrNode *head = new LStrNode, *pNode = head;
  for (char *p = str; *p; p++) {
    pNode->next = new LStrNode;
    pNode = pNode->next;
    pNode->data = *p;
    pNode->next = NULL;
  }

  DeleteChar(head, 'A');
  for (LStrNode *p = head->next; p != NULL; p = p->next) {
    cout << p->data << " ";
  }
  cout << endl;
}