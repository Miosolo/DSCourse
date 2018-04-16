// 题目描述有误，所谓“中间位置”元素应为去除头节点后ceiling(n / 2)位置的元素

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

#define ElemType int

typedef struct LNode {
  ElemType data;
  LNode *next;
} LNode;

LNode *FindMidPoint(const LNode *head) {
  if (head->next == NULL) {
    return NULL;
  } else if (head->next->next == NULL) {
    return head->next;
  } else {
    LNode *mid = head->next, *end = head->next->next;
    while (end != NULL && end->next != NULL) {
      mid = mid->next;
      end = end->next->next;
    }
    return mid;
  }
}

int main(void) {
  LNode *list = new LNode;
  list->data = 0xF0000000;
  LNode *p = list;
  for (int i = 1; i < 6; i++) {
    p->next = new LNode;
    p->next->data = i;
    p = p->next;
  }
  p->next = NULL;

  LNode *mid = FindMidPoint(list);
  cout << mid->data << endl;

  return 0;
}