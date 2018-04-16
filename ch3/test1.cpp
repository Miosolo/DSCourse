#include <cstring>
#include <iostream>
using namespace std;

#define MaxSize 100
#define ElemType int

class SqStack {
 private:
  ElemType data[MaxSize];
  int top;

 public:
  SqStack(void) : top(-1) {}
  void InitStack(SqStack *&s) { s = new SqStack; }
  bool push(ElemType e) {
    if (!IsFull()) {
      data[++top] = e;
      return true;
    } else {
      return false;
    }
  }
  bool pop() bool IsFull(void) { return top < MaxSize; }
  void DestroyStack(SqStack *&s) { delete s; }
}