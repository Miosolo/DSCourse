#include <iostream>
#include <stack>
using namespace std;

bool IsWellNested(char *Expression) {
  stack<char> OpStack;
  char *ExpPosi = Expression;

  while (*ExpPosi) {
    if (*ExpPosi == '(' || *ExpPosi == '[' || *ExpPosi == '{') {
      OpStack.push(*ExpPosi);
    } else if (*ExpPosi == ')' || *ExpPosi == ']' || *ExpPosi == '}') {
      char LastOp = OpStack.top();
      switch (*ExpPosi) {
        case ')':
          if (LastOp == '(') {
            OpStack.pop();
            break;
          } else
            return false;
        case ']':
          if (LastOp == '[') {
            OpStack.pop();
            break;
          } else
            return false;
        case '}':
          if (LastOp == '{') {
            OpStack.pop();
            break;
          } else
            return false;
      }
    }
    ExpPosi++;
  }

  return true;
}

int main(void) {
  char str[1000] = "{[][(()]}";
  cout << IsWellNested(str) << endl;

  return 0;
}