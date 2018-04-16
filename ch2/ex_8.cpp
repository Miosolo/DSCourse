#include <algorithm>
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
  SqList arr = {8, {-5, -3, 4, 23, 5, -8, -9, -30}};
  ZeroPartition(&arr);

  for (int i = 0; i < arr.length; i++) printf("%d ", arr.data[i]);
  putchar('\n');

  return 0;
}