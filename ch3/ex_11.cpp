#include <iostream>
using namespace std;

#define MAXLEN 100
#define ElemType char

typedef struct {
  ElemType data[MAXLEN - 1];
  int front, rear;
} CirQueue;

void function(char *exp) {
  CirQueue EleCircle = {.front = -1, .rear = -1};
  char *p = exp;

  while ((EleCircle.rear + 1) % MAXLEN != EleCircle.front) {
    cout << "Input is " << *p << ", ";
    if ('0' <= *p && *p <= '9') {
      cout << "enqueue: ";
      EleCircle.rear = (EleCircle.rear + 1) % MAXLEN;
      EleCircle.data[EleCircle.rear] = *p;
    } else if ('a' <= *p && *p <= 'z') {
      if (EleCircle.front != EleCircle.rear) {
        cout << "dequeue: ";
        EleCircle.front = (EleCircle.front + 1) % MAXLEN;
      } else {
        cout << "Nothing to enqueue. " << endl;
        return;
      }
    } else {
      return;
    }

    if (EleCircle.front == EleCircle.rear) cout << "ø";

    for (int i = EleCircle.front + 1; i <= EleCircle.rear; i++)
      cout << EleCircle.data[i] << " ";
    cout << endl;

    if (*(++p) == 0) return;
  }
}

int main(void) {
  char str[50];
  while (1) {
    cout << "Enter your expression: ";
    if (!(cin >> str)) break;

    function(str);
  }

  return 0;
}