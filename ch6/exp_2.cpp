#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <random>
using namespace std;

#define N 10
#define FindIndex(row, col) (row) * ((row)-1) / 2 + (col)-1

typedef int ElemType;
typedef struct SymMartrix {
 public:
  ElemType data[(1 + N) * N / 2];

 public:
  inline ElemType GetData(int row, int col) {
    if (col > row) swap(col, row);
    return data[row * (row - 1) / 2 + col - 1];
  }
  inline bool WriteData(int row, int col, ElemType val) {
    if (row <= col) {
      data[row * (row - 1) / 2 + col - 1] = val;
      return true;
    } else
      return false;
  }
} SymMartrix;

typedef struct Martrix {
  ElemType data[N][N];
} Martrix;

void SymMartrixSum(SymMartrix* m1, SymMartrix* m2, SymMartrix* sum) {
  ElemType *p1 = m1->data, *p2 = m2->data, *ps = sum->data;
  for (int i = 0; i < N * (N + 1) / 2; ++i) *ps++ = *p1++ + *p2++;
}

void SymMartrixProduct(SymMartrix* m1, SymMartrix* m2, Martrix* pro) {
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) {
      ElemType s = 0;
      for (int k = 1; k <= N; k++) s += m1->GetData(i, k) * m2->GetData(k, j);
      pro->data[i][j] = s;
    }
}

int main(void) {
  SymMartrix sym1, sym2, sym3;
  default_random_engine e;
  uniform_int_distribution<ElemType> u(0, 99);

  for (int i = 0; i < N * (N + 1) / 2; i++) {
    sym1.data[i] = u(e);
    sym2.data[i] = u(e);
  }

  cout << endl << "Martrix A" << endl;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) cout << setw(3) << sym1.GetData(i, j);
    cout << endl;
  }

  cout << endl << "Martrix B" << endl;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) cout << setw(3) << sym2.GetData(i, j);
    cout << endl;
  }

  cout << endl << "Martrix A+B" << endl;
  SymMartrixSum(&sym1, &sym2, &sym3);
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) cout << setw(4) << sym3.GetData(i, j);
    cout << endl;
  }

  Martrix M;
  SymMartrixProduct(&sym1, &sym2, &M);
  cout << endl << "Martrix AB" << endl;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) cout << setw(8) << M.data[i][j];
    cout << endl;
  }

  return 0;
}
