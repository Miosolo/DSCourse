#include <iostream>
using namespace std;

typedef double ElemType;

ElemType GetAvgTailRecur(ElemType[], int, int, ElemType);
ElemType GetAvgTailRecur(ElemType[], int);
ElemType GetAvgRecur(ElemType[], int);

ElemType GetAvgTailRecur(ElemType A[], int sizeofA) {
  return GetAvgTailRecur(A, sizeofA, sizeofA - 1, 0);
}

ElemType GetAvgTailRecur(ElemType A[], int sizeofA, int index, ElemType acc) {
  if (index == -1) return acc;

  return GetAvgTailRecur(
      A, sizeofA, index - 1,
      (acc * (sizeofA - 1 - index) + A[index]) / (sizeofA - index));
}

ElemType GetAvgRecur(ElemType A[], int n) {
  if (n == 1) return A[0];

  return (GetAvgRecur(A, n - 1) * (n - 1) + A[n - 1]) / n;
}

int main(void) {
  ElemType A[5];
  for (int i = 0; i < sizeof(A) / sizeof(ElemType); i++) A[i] = i;

  cout << GetAvgRecur(A, sizeof(A) / sizeof(ElemType)) << endl;
  cout << GetAvgTailRecur(A, sizeof(A) / sizeof(ElemType)) << endl;
}