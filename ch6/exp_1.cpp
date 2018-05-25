#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

#define MaxSize 16
#define M 4
#define N 4

typedef int ElemType;
typedef struct {
  int row, col;
  ElemType d;
} TNode;
typedef struct {
  int rows = M, cols = N;
  int num = 0;
  TNode data[MaxSize];
} TSMartrix;

TSMartrix* InitTSM(ElemType**, const int);
void PrintTransTSM(TSMartrix*);
void PrintTSMSum(TSMartrix*, TSMartrix*);
void PrintTSMProduct(TSMartrix*, TSMartrix*);
void GetTSMTranIndex(TSMartrix*, int[]);

TSMartrix* InitTSM(ElemType A[M][N]) {
  TSMartrix* TSM = new TSMartrix;

  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++)
      if (A[i][j] != 0) {
        TSM->data[TSM->num].row = i;
        TSM->data[TSM->num].col = j;
        TSM->data[TSM->num].d = A[i][j];
        TSM->num++;
      }

  return TSM;
}

void PrintTransTSM(TSMartrix* TSM) {
  int index[MaxSize];
  GetTSMTranIndex(TSM, index);

  for (int i = 0; index[i] >= 0; i++)
    cout << TSM->data[index[i]].col << " " << TSM->data[index[i]].row << " "
         << TSM->data[index[i]].d << endl;

  return;
}

void GetTSMTranIndex(TSMartrix* TSM, int index[]) {
  int ColAmount[N] = {0};
  memset(index, -1, sizeof(int) * MaxSize);

  for (TNode* p = TSM->data; p < &TSM->data[TSM->num]; p++) ColAmount[p->col]++;

  for (int i = 1; i < N; i++) ColAmount[i] += ColAmount[i - 1];

  for (int i = 0; i < TSM->num; i++) {
    int k = (TSM->data[i].col > 0) ? ColAmount[TSM->data[i].col - 1] : 0;
    while (index[k] >= 0) k++;
    index[k] = i;
  }
}

void PrintTSMSum(TSMartrix* TSM1, TSMartrix* TSM2) {
  TNode *p1 = TSM1->data, *p2 = TSM2->data;

  while (p1 < &TSM1->data[TSM1->num] && p2 < &TSM2->data[TSM2->num]) {
    if (p1->row < p2->row || (p1->row == p2->row && p1->col < p2->col)) {
      cout << p1->row << " " << p1->col << " " << p1->d << endl;
      p1++;
    } else if (p1->row == p2->row && p1->col == p2->col) {
      cout << p1->row << " " << p1->col << " " << p1->d + p2->d << endl;
      p1++, p2++;
    } else {
      cout << p2->row << " " << p2->col << " " << p2->d << endl;
      p2++;
    }
  }

  return;
}

void PrintTSMProduct(TSMartrix* TSMa, TSMartrix* TSMb) {
  int TSMbTransIndex[MaxSize];
  GetTSMTranIndex(TSMb, TSMbTransIndex);
  int TSMaRowAm[M] = {0}, TSMbColAm[N] = {0};

  for (int i = 0; i < TSMa->num; i++) TSMaRowAm[TSMa->data[i].row]++;
  for (int i = 1; i < M; i++) TSMaRowAm[i] += TSMaRowAm[i - 1];
  for (int i = 0; i < TSMb->num; i++) TSMbColAm[TSMb->data[i].col]++;
  for (int i = 1; i < N; i++) TSMbColAm[i] += TSMbColAm[i - 1];

  for (int Pi = 0; Pi < M; Pi++) {
    for (int Pj = 0; Pj < N; Pj++) {
      ElemType TempProduct = 0;

      for (int k = 0; k < M; k++) {
        int aindex = -1, bindex = -1;
        for (aindex = (Pi > 0) ? TSMaRowAm[Pi - 1] : 0;
             aindex < TSMaRowAm[Pi] || ((aindex = -1) + 1);
             aindex++)  //利用短路运算使得遍历且找不到这样的aindex时，使aindex
                        //= -1
          if (TSMa->data[aindex].col == k)
            break;
          else if (TSMa->data[aindex].col > k) {
            aindex = -1;
            break;
          }
        // for-end

        if (aindex == -1) {
          continue;
        } else {
          for (bindex = ((TSMbColAm[Pj] > 0) ? TSMbColAm[Pj - 1] : 0);
               bindex < TSMbColAm[Pj] || ((bindex = -1) + 1); bindex++)
            if (TSMb->data[TSMbTransIndex[bindex]].row == k)
              break;
            else if (TSMb->data[TSMbTransIndex[bindex]].row > k) {
              bindex = -1;
              break;
            }
          // for-end

          if (bindex == -1) {
            continue;
          } else {
            TempProduct +=
                TSMa->data[aindex].d * TSMb->data[TSMbTransIndex[bindex]].d;
          }
        }
      }
      if (TempProduct != 0)
        cout << Pi << " " << Pj << " " << TempProduct << endl;
    }
  }
}

int main(void) {
  int a[M][N] = {{1, 0, 3, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}};
  int b[M][N] = {{3, 0, 0, 0}, {0, 4, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 2}};
  TSMartrix *TSMa, *TSMb;

  TSMa = InitTSM(a);
  TSMb = InitTSM(b);


  PrintTransTSM(TSMa);
  PrintTSMSum(TSMa, TSMb);
  PrintTSMProduct(TSMa, TSMb);

  return 0;
}