#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

typedef double Elemtype;
#define MAXSIZE 200
#define INF 0x0FFFFFFF

class ValueStack {
 private:
  Elemtype stack[MAXSIZE];
  int top;

 public:
  ValueStack(void);
  static bool StackEmpty(ValueStack *const S);
  static bool Push(ValueStack *const S, Elemtype E);
  static bool Pop(ValueStack *const S, Elemtype &E);
  static bool GetTop(ValueStack *const S, Elemtype &E);
};

class OpStack {
 private:
  char stack[MAXSIZE];
  int top;

 public:
  OpStack(void);
  static bool StackEmpty(OpStack *const S);
  static bool Push(OpStack *const S, char C);
  static bool Pop(OpStack *const S, char &C);
  static bool GetTop(OpStack *const S, char &C);
};

typedef struct {
  bool IsValue;
  union {
    Elemtype value;
    char op;
  } Frag;
} ExpFrag;

ValueStack::ValueStack(void) : top(-1) {}
bool ValueStack::StackEmpty(ValueStack *const S) {
  return S->top == -1 ? true : false;
}
bool ValueStack::Push(ValueStack *const S, Elemtype E) {
  if (S->top == MAXSIZE - 1) return false;

  S->stack[++S->top] = E;
  return true;
}
bool ValueStack::Pop(ValueStack *const S, Elemtype &E) {
  if (StackEmpty(S)) return false;

  E = S->stack[S->top--];
  return true;
}
bool ValueStack::GetTop(ValueStack *const S, Elemtype &E) {
  if (StackEmpty(S)) return false;

  E = S->stack[S->top];
  return true;
}

OpStack::OpStack(void) : top(-1) {}
bool OpStack::StackEmpty(OpStack *const S) {
  return S->top == -1 ? true : false;
}
bool OpStack::Push(OpStack *const S, char E) {
  if (S->top == MAXSIZE - 1) return false;

  S->stack[++S->top] = E;
  return true;
}
bool OpStack::Pop(OpStack *const S, char &E) {
  if (StackEmpty(S)) return false;

  E = S->stack[S->top--];
  return true;
}
bool OpStack::GetTop(OpStack *const S, char &E) {
  if (StackEmpty(S)) return false;

  E = S->stack[S->top];
  return true;
}

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
  ValueStack *VS = new class ValueStack;
  OpStack *OpS = new class OpStack;
  char *ExpPosi = Expression;
  ExpFrag *EF = new ExpFrag;

  while (1) {
    if (DivideExpression(ExpPosi, EF)) {  // Get a number
      if (EF->IsValue) {
        ValueStack::Push(VS, EF->Frag.value);
      } else {  // Get a symbol / Nothing
        char TempLastOp;

        if (OpStack::StackEmpty(OpS) && EF->Frag.op != '#') {
          // First Op
          OpStack::Push(OpS, EF->Frag.op);
        } else {
          while (1) {
            if (OpStack::StackEmpty(OpS) && EF->Frag.op == '#') {
              ValueStack::Pop(VS, result);
              return true;
            }

            if (OpStack::GetTop(OpS, TempLastOp)) {
              // >= 1 ops in the stack

              if (GetOpPiority(TempLastOp, EF->Frag.op) > 0) {
                // This op is higher than its previous one
                OpStack::Push(OpS, EF->Frag.op);
                break;
              } else {  // This is op is lower than its previous one
                OpStack::Pop(OpS, TempLastOp);
                if (EF->Frag.op == ')' && TempLastOp == '(') {  // if it meets()
                  break;
                } else {
                  Elemtype TempLastVal, TempSecLastVal, TempResult = 0;
                  ValueStack::Pop(VS, TempLastVal);
                  ValueStack::Pop(VS, TempSecLastVal);
                  if (SortOut(TempSecLastVal, TempLastOp, TempLastVal,
                              TempResult)) {
                    // legal expression
                    ValueStack::Push(VS, TempResult);
                  } else
                    // Illegal expression
                    return false;
                }
              }
            } else {  // This is the first op of this expression
              OpStack::Push(OpS, EF->Frag.op);
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
