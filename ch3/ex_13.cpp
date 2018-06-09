#include <cstdio>
#include <iostream>
using namespace std;

#define MAXSIZE 100

typedef struct {
  int data[MAXSIZE];
  int front, rear;
} SqQueue;

int main(void) {
  SqQueue DigitQueue[10];
  for (int i = 0; i < 10; i++) {
    DigitQueue[i].front = -1;
    DigitQueue[i].rear = 0;
  }

  int input, inputCounter = 0;
  while (1) {
    cout << "Enter the No. " << inputCounter++ << " number" << endl;

    if (!(cin >> input))
      break;
    else if (input > 10)
      continue;

    DigitQueue[input].data[++DigitQueue[input].rear] = input;
  }
  cout << endl;

  cout << "Final queue: " << endl;
  for (int i = 0; i <= 9; i++) {
    if (DigitQueue[i].rear == 0) continue;

    for (int j = 0; j < DigitQueue[i].rear; j++) printf("%d ", i);
  }

  return 0;
}