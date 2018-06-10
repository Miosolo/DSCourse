#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

#define ElemType int
#define MAXL 100
#define INV 0xF0000000

typedef struct SqList {
  int length;
  ElemType data[MAXL];
} SqList;

bool ZeroPartition(SqList *L) {
  switch (L->length) {
    case 0:
      return false;
    case 1:
      return true;
    default: {
      ElemType pivot = 0, *p = L->data, *q = &L->data[L->length - 1];
      while (1) {
        if (p >= q) break;
        while (p < q && *p <= pivot) p++;
        while (p < q && *q >= pivot) q--;
        swap(*p, *q);
      }
      return true;
    }
  }
}

int main(void) {
  srand((unsigned)time(0));
  const int LIST_LEN = 20;

  SqList arr = {.length = LIST_LEN};
  cout << "Random origianl array: " << endl;
  for (int i = 0; i < LIST_LEN; i++) {
    arr.data[i] = pow(-1, rand() % 2) * (rand() % 100);
    cout << arr.data[i] << " ";
  }

  ZeroPartition(&arr);

  cout << endl << "Current array: " << endl;
  for (int i = 0; i < arr.length; i++) printf("%d ", arr.data[i]);
  putchar('\n');

  return 0;
}