#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
using namespace std;

typedef double Elemtype;
#define MAXSIZE 200
#define INF 0x0FFFFFFF

typedef struct {
  bool IsValue;
  union {
    Elemtype value;
    char op;
  } Frag;
} ExpFrag;

bool DivideExpression(char *&, ExpFrag *&);
int GetOpPiority(char, char);
bool Calc(char *, Elemtype &);
bool SortOut(Elemtype, char, Elemtype, Elemtype &);

bool DivideExpression(char *&ExpPosi, ExpFrag *&E) {
  if (*ExpPosi == 0) {
    E->Frag.op = '#';
    E->IsValue = false;
    return true;
  }

  if (('0' <= *ExpPosi && *ExpPosi <= '9') || *ExpPosi == '-' ||
      *ExpPosi == '.') {
    E->IsValue = true;

    E->Frag.value = atof(ExpPosi);
    do {
      ExpPosi++;
    } while (('0' <= *ExpPosi && *ExpPosi <= '9') || *ExpPosi == '-' ||
             *ExpPosi == '.' || *ExpPosi == 'e');
    return true;
  } else if (*ExpPosi == '+' || *ExpPosi == '-' || *ExpPosi == '*' ||
             *ExpPosi == '/' || *ExpPosi == '(' || *ExpPosi == ')') {
    E->IsValue = false;
    E->Frag.op = *ExpPosi;
    ExpPosi++;
    return true;
  } else {
    E->Frag.op = 0;
    return false;
  }
}

//-----------这里的优先级指op2->op1的----------------------
int GetOpPiority(char op1, char op2) {
  if ((op1 == '+' || op1 == '-' || op1 == '*' || op1 == '/' || op1 == '(' ||
       op2 == ')') &&
      (op2 == '+' || op2 == '-' || op2 == '*' || op2 == '/' || op2 == '(' ||
       op2 == ')' || op2 == '#')) {
    const int Op1Poirity[128] = {['+'] = 1, ['-'] = 1,  ['*'] = 2,
                                 ['/'] = 2, ['('] = -1, [')'] = 0};
    const int Op2Poirity[128] = {['+'] = 1, ['-'] = 1,  ['*'] = 2, ['/'] = 2,
                                 ['('] = 3, [')'] = -2, ['#'] = -3};
    return Op2Poirity[(int)op2] - Op1Poirity[(int)op1];
  } else {
    return INF;
  }
}

bool Calc(char *Expression, Elemtype &result) {
  stack<Elemtype> ValueStack;
  stack<char> OpStack;
  char *ExpPosi = Expression;
  ExpFrag *EF = new ExpFrag;

  while (1) {
    if (DivideExpression(ExpPosi, EF)) {  // Get a number
      if (EF->IsValue) {
        ValueStack.push(EF->Frag.value);
      } else {  // Get a symbol / Nothing
        char TempLastOp;

        if (OpStack.empty() && EF->Frag.op != '#') {
          // First Op
          OpStack.push(EF->Frag.op);
        } else {
          while (1) {
            if (OpStack.empty() && EF->Frag.op == '#') {
              result = ValueStack.top();
              ValueStack.pop();
              return true;
            }

            if (!OpStack.empty()) {
              // >= 1 ops in the stack
              TempLastOp = OpStack.top();
              if (GetOpPiority(TempLastOp, EF->Frag.op) > 0) {
                // This op is higher than its previous one
                OpStack.push(EF->Frag.op);
                break;
              } else {  // This is op is lower than its previous one
                OpStack.pop();
                if (EF->Frag.op == ')' && TempLastOp == '(') {  // if it meets()
                  break;
                } else {
                  Elemtype TempLastVal, TempSecLastVal, TempResult = 0;

                  TempLastVal = ValueStack.top();
                  ValueStack.pop();
                  TempSecLastVal = ValueStack.top();
                  ValueStack.pop();

                  if (SortOut(TempSecLastVal, TempLastOp, TempLastVal,
                              TempResult)) {
                    // legal expression
                    ValueStack.push(TempResult);
                  } else
                    // Illegal expression
                    return false;
                }
              }
            } else {  // This is the first op of this expression
              OpStack.push(EF->Frag.op);
              break;
            }
          }
        }
      }
    } else
      return false;  // Got invaild symbols
  }
}

bool SortOut(Elemtype v1, char op, Elemtype v2, Elemtype &result) {
  switch (op) {
    case '+':
      result = v1 + v2;
      return true;
    case '-':
      result = v1 - v2;
      return true;
    case '*':
      result = v1 * v2;
      return true;
    case '/':
      if (v2) {
        result = v1 / v2;
        return true;
      }  // intentional drop-off
    default:
      return false;
  }
}

int main(void) {
  char str[50];

  while (1) {
    cout << "Input the Expression" << endl;
    memset(str, 0, size(str));
    if (cin >> str) {
      Elemtype result;
      if (Calc(str, result)) {
        cout << result << endl;
      } else {
        cout << "Illegal Input" << endl;
      }
    }
  }
  return 0;
}
