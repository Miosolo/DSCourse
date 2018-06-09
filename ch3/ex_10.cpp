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
  cout << "Enter your expression to check whether it's well nested. " << endl
       << endl;

  char str[1000];
  while (cin >> str) cout << boolalpha << IsWellNested(str) << endl << endl;

  return 0;
}