#include <algorithm>
#include <iostream>
using namespace std;

#define MAXLEN 20
#define ElemType int

typedef struct {
  ElemType data[MAXLEN];
  int front, rear;
} CirQueue;

void ReverseCirQueue(CirQueue *CQ) {
  CQ->front = (CQ->front + 1) % MAXLEN;
  CQ->front = MAXLEN - 1 - CQ->front;
  CQ->rear = MAXLEN - 1 - CQ->rear;
  swap(CQ->front, CQ->rear);
  CQ->front = (CQ->front - 1) % MAXLEN;

  int i, j;
  for (i = 0, j = MAXLEN - 1; i <= j; i++, j--) {
    if (i > CQ->rear && j < CQ->front)
      break;
    else if (i < CQ->front && j > CQ->rear)
      continue;

    swap(CQ->data[i], CQ->data[j]);
  }
  return;
}

int main(void) {
  CirQueue CQ = {.front = 19, .rear = 9};
  for (int i = 0; i < 10; i++) {
    CQ.data[i] = i;
  }

  ReverseCirQueue(&CQ);

  return 0;
}