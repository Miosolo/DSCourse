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
  SqList arr = {10, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
  SqList *L = &arr;
  cout << "Original array: ";
  for (int i = 0; i < arr.length; i++) cout << arr.data[i] << " ";
  cout << endl;

  while (1) {
    ElemType ele;
    cout << "Enter the number to insert: ";

    if (cin >> ele)
      InsertElem(L, ele);
    else
      break;

    cout << "Current array: ";
    for (int i = 0; i < L->length; i++) printf("%d ", L->data[i]);
    cout << endl;
  }
  return 0;
}
