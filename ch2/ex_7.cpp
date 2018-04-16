#include <cstring>
#include <iostream>
using namespace std;

#define ElemType int
#define MAXL 100
#define INV 0xF0000000

typedef struct SqList {
  int length;
  ElemType data[MAXL];
} SqList;

bool InsertElem(SqList *&L, ElemType x) {
  if (L->length == MAXL) return false;

  int posi;
  for (posi = 0; posi < L->length && L->data[posi] < x; posi++)
    ;
  for (int i = L->length; i > posi; i--) {
    L->data[i] = L->data[i - 1];
  }
  L->data[posi] = x;
  L->length++;

  return true;
}

int main(void) {
  SqList arr = {10, {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}};
  SqList *L = &arr;
  InsertElem(L, 3);

  for (int i = 0; i < L->length; i++) printf("%d ", L->data[i]);
  putchar('\n');
  return 0;
}
