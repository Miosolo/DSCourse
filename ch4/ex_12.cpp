#include <iostream>
using namespace std;

typedef char ElemType;
typedef struct LNode {
  ElemType data;
  LNode *next;
} LNode;
typedef LNode LStrNode;

void DeleteChar(LStrNode *strHead, char elem) {
  LStrNode *cur, *pre;

  for (cur = strHead->next, pre = strHead; cur; pre = cur, cur = cur->next) {
    if (cur->data == elem) {
      pre->next = cur->next;
      delete cur;
      cur = pre;
    }
  }

  return;
}

int main(void) {
  char str[200];
  while (1) {
    cout << "Enter a string: " << endl;
    if (!(cin >> str)) break;

    LStrNode *head = new LStrNode, *pNode = head;
    for (char *p = str; *p; p++) {
      pNode->next = new LStrNode;
      pNode = pNode->next;
      pNode->data = *p;
      pNode->next = NULL;
    }

    ElemType del;
    cout << "Enter the element you'd like to remove: ";
    if (!(cin >> del)) break;

    DeleteChar(head, del);
    cout << "Result: " << endl;
    for (LStrNode *p = head->next; p != NULL; p = p->next) {
      cout << p->data << " ";
    }
    cout << endl << endl;
  }

  return 0;
}