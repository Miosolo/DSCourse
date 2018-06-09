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
  const int MAX_LEN = 50;
  ElemType A[MAX_LEN];

  ElemType buf;
  cout << "Enter a series of values: " << endl;

  int counter = 0;
  while (counter < MAX_LEN && (cin >> buf)) {
    A[counter++] = buf;
  }
  if (counter == 0) return 1;

  cout << "Get the average value recursively: " << GetAvgRecur(A, counter)
       << endl;
  cout << "Get the average value using tail recursion: "
       << GetAvgTailRecur(A, counter) << endl;

  return 0;
}