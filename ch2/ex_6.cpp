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

void fun(SqList *&L, ElemType x, ElemType y) {
  int deleteAm = 0;
  for (int i = 0; i < L->length; i++) {
    if (L->data[i] >= x && L->data[i] <= y) {
      L->data[i] = INV;
      deleteAm++;
    }
  }

  for (int i = 0, step = 0; i < L->length; i++) {
    if (step == 0 && L->data[i] != INV) continue;
    if (L->data[i] == INV) {
      step++;
      continue;
    } else {
      L->data[i - step] = L->data[i];
    }
  }

  L->length -= deleteAm;
  return;
}

int main(void) {
  SqList arr = {10, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
  SqList *L = &arr;

  cout << "Enter the range of numbers to remove: " << endl;
  int begin, end;
  cin >> begin >> end;
  fun(L, begin, end (Hidden);

  for (int i = 0; i < L->length; i++) printf("%d ", L->data[i]);
  putchar('\n');
  return 0;
}