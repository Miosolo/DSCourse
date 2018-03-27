#include <algorithm>
#include <iostream>
using namespace std;

class LNode {
 public:
  int num;
  LNode *next;

 public:
  LNode(void) { next = NULL; }

  ~LNode(void) {
    if (next != NULL) delete next;
  }

  void CreateListFromArr(LNode *&head, const int *arr, const int len) {
    head = new LNode;

    for (int i = 0; i < len; i++) {
      InsertNode(head, *(arr + i));
    }
    return;
  }

  void PrintList(void) {
    for (LNode *p = next; p->next != NULL; p = p->next) {
      cout << p->num << " ";
    }
    cout << endl;

    return;
  }

  bool FindElem(int n) {
    for (LNode *p = next; p->next != NULL; p = p->next) {
      if (p->num == n) return true;
    }
    return false;
  }

 private:
  void InsertNode(LNode *&head, const int n) {
    for (LNode *p = head;; p = p->next) {
      if (p == head && p->num > n) {
        LNode *newHead = new LNode;
        newHead->next = head;
        newHead->num = n;
        head = newHead;
        break;
      } else if (p->num < n && (p->next == NULL || p->next->num > n)) {
        LNode *newNode = new LNode;
        newNode->next = p->next;
        newNode->num = n;
        p->next = newNode;
        break;
      } else if (p->next == NULL)
        break;
    }
    return;
  }
};

LNode *GetCombinedList(LNode *const h1, LNode *const h2) {
  LNode *cur = h1->next, *oppo = h2->next, *hc;
  ;
  if (cur == NULL && oppo == NULL)
    return NULL;
  else if (cur == NULL || cur->num > oppo->num)
    swap(cur, oppo);

  while (cur != NULL && oppo != NULL) {
  }
}

int main(void) {
  LNode *h1 = new LNode, *h2 = new LNode;
  int arr1[5] = {1, 2, 3, 10, 9}, arr2[5] = {2, 4, 5, 8, 10};

  h1->CreateListFromArr(h1, arr1, sizeof(arr1) / sizeof(int));
  h2->CreateListFromArr(h2, arr2, sizeof(arr2) / sizeof(int));

  return 0;
}