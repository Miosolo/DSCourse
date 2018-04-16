#include <algorithm>
#include <iostream>
using namespace std;

class LkNode {
 public:
  int num;
  LkNode *next;

 public:
  LkNode(void) { next = NULL; }

  ~LkNode(void) {
    if (next != NULL) delete next;
  }

  void CreateList(LkNode *&head, const int *arr, const int len) {
    head = new LkNode;

    for (int i = 0; i < len; i++) {
      InsertNode(head, *(arr + i));
    }
    return;
  }

  void PrintList(void) {
    for (LkNode *p = next; p->next != NULL; p = p->next) {
      cout << p->num << " ";
    }
    cout << endl;

    return;
  }

  bool FindElem(int n) {
    for (LkNode *p = next; p->next != NULL; p = p->next) {
      if (p->num == n) return true;
    }
    return false;
  }

 private:
  void InsertNode(LkNode *&head, const int n) {
    for (LkNode *p = head;; p = p->next) {
      if (p == head && p->num > n) {
        LkNode *newHead = new LkNode;
        newHead->next = head;
        newHead->num = n;
        head = newHead;
        break;
      } else if (p->num < n && (p->next == NULL || p->next->num > n)) {
        LkNode *newNode = new LkNode;
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

void GetCombSet(LkNode *h1, LkNode *h2) {
  cout << "Combined Set: " << endl;
  LkNode *curList = h1->next, *oppoList = h2->next;
  if (curList == NULL || oppoList == NULL) {
    if (oppoList == NULL) swap(curList, oppoList);

    goto PrintToEnd;
  }
  if (h1->num > h2->num) swap(h1, h2);

  while (1) {
    if (oppoList == NULL) {
    PrintToEnd:
      while (curList != NULL) {
        cout << curList->num;
        curList = curList->next;
      }
      cout << endl;
      return;
    } else
      do {
        cout << curList->num << " ";
        curList = curList->next;
      } while (curList != NULL && curList->num < oppoList->num);

    if (curList != NULL && curList->num == oppoList->num) {
      oppoList = oppoList->next;
      continue;
    } else {
      swap(curList, oppoList);
    }
  }
}

void GetInterSet(LkNode *h1, LkNode *h2) {
  cout << "Intersection Set: " << endl;
  LkNode *curList = h1->next, *oppoList = h2->next;

  if (curList == NULL || oppoList == NULL) {
    return;
  } else {
    if (curList->num < oppoList->num) {
      swap(curList, oppoList);
    } else if (curList->num == oppoList->num) {
      cout << curList->num;
      curList = curList->next;
    }

    while (1) {
      do {
        oppoList = oppoList->next;
      } while (oppoList != NULL && curList->num > oppoList->num);
      if (oppoList == NULL) break;
      if (curList->num == oppoList->num) {
        cout << curList->num << " ";
        oppoList = oppoList->next;
      }
      swap(curList, oppoList);
    }
  }
}

/*void GetSubSet(LkNode *list1, LkNode *list2) {
  cout << "Difference Set: " << endl;
  list1 = list1->next, list2 = list2->next;
  if (list1 == NULL) {
    return;
  } else if (list2 == NULL) {
    while (list1 != NULL) {
      cout << list1->num << " ";
      list1 = list1->next;
    }
    cout << endl;
  } else {
    while (list1 != NULL && list1->num < list2->num) {
      cout << list1->num << " ";
      list1 = list1->next;
    }
    if (list1 == NULL) {
      cout << endl;
      return;
    } else if (list1->num == list2->num) {
      list1 = list1->next;
    }

    while (1) {
      while (list1 != NULL && list1->num) }
  }
}* main(void) {
  LkNode *h1 = new LkNode, *h2 = new LkNode;
  int arr1[5] = {1, 2, 3, 10, 9}, arr2[5] = {2, 4, 5, 8, 10};

  h1->CreateList(h1, arr1, sizeof(arr1) / sizeof(int));
  h2->CreateList(h2, arr2, sizeof(arr2) / sizeof(int));

  GetInterSet(h1, h2);

  return 0;
}*/
