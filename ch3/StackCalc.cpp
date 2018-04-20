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
Elemtype Calc(char *);
Elemtype SortOut(Elemtype, char, Elemtype);

bool DivideExpression(char *&ExpPosi, ExpFrag *&E) {
  if (*ExpPosi == 0) {
    E->Frag.op = '#';
    return false;
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
  } else {
    E->Frag.op = 0;
    return false;
  }

  ExpPosi++;
  return true;
}

int GetOpPiority(char op1, char op2) {
  if ((op1 == '+' || op1 == '-' || op1 == '*' || op1 == '/' || op1 == ')' ||
       op2 == '+' || op1 == '#') &&
      (op2 == '+' || op2 == '-' || op2 == '(' || op2 == '*' || op2 == '/' ||
       op2 == ')')) {
    const int Op1Poirity[128] = {['+'] = 1, ['-'] = 1,  ['*'] = 2,
                                 ['/'] = 2, ['('] = -1, [')'] = 0};
    const int Op2Poirity[128] = {['+'] = 1, ['-'] = 1, ['*'] = 2,
                                 ['/'] = 2, ['('] = 3, [')'] = 0};
    return Op2Poirity[(int)op2] - Op1Poirity[(int)op1];
  } else {
    return INF;
  }
}

Elemtype Calc(char *Expression) {
  ValueStack *VS = new class ValueStack;
  OpStack *OpS = new class OpStack;
  char *ExpPosi = Expression;
  ExpFrag *EF = new ExpFrag;

  /*{ while (1) {
     bool InputEnd = false;
     if (!DivideExpression(ExpPosi, EF)) InputEnd = true;

     if (EF->IsValue) {
       ValueStack::Push(VS, EF->Frag.value);
     } else {
       char LastOp;
       int piority;

       if (OpStack::GetTop(OpS, LastOp)) {
         piority = GetOpPiority(LastOp, EF->Frag.op);
       } else {
         piority = 1;
       }

       if (piority > 0) {
         OpStack::Push(OpS, EF->Frag.op);
       } else {
         while (!ValueStack::StackEmpty(VS)) {
           if (OpStack::GetTop(OpS, LastOp)) {
             int TempPiority = GetOpPiority(LastOp, EF->Frag.op);

             if (TempPiority <= 0) {
               if (LastOp == '(') {
                 continue;
               } else {
                 OpStack::Pop(OpS, LastOp);
                 Elemtype LastValue, SecLastValue, CurValue;
                 ValueStack::Pop(VS, LastValue);
                 ValueStack::Pop(VS, SecLastValue);
                 CurValue = SortOut(SecLastValue, LastOp, LastValue);
                 if (CurValue == INF) {
                   return INF;
                 } else {
                   ValueStack::Push(VS, CurValue);
                 }
               }
             }
           }
         }
       }
     }
   }}
 }*/
}

Elemtype SortOut(Elemtype v1, char op, Elemtype v2) {
  switch (op) {
    case '+':
      return (v1 + v2);
    case '-':
      return (v1 - v2);
    case '*':
      return (v1 * v2);
    case '/':
      if (v2) {
        return (v1 / v2);
      } else {
        return INF;
      }
    default:
      return INF;
  }
}

int main(void) {
  char str[50] = "1+(2+3)";

  while (1) {
    cout << "Input the Expression" << endl;
    if (cin >> str) {
      Elemtype result = Calc(str);
      cout << result << endl;
    } else {
      break;
    }
  }

  free(str);

  return 0;
}
