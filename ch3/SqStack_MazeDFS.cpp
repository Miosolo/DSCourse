#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>
#include <stack>
using namespace std;

#define MAXM 8
#define MAXN 8

typedef struct {
  int i;
  int j;
  int NextDir;
} Box;

bool DFS(bool **, const int, const int, const int, const int);
void SetBox(Box *, int, int, int);
void PrintRoute(stack<Box> *);

void SetBox(Box *B, int i, int j, int dir) {
  B->i = i;
  B->j = j;
  B->NextDir = dir;

  return;
}

void PrintRoute(stack<Box> *BoxStack) {
  list<Box> BoxList;

  while (!BoxStack->empty()) {
    BoxList.push_front(BoxStack->top());
    BoxStack->pop();
  }

  while (!BoxList.empty()) {
    printf("(%d, %d) -> ", BoxList.front().i, BoxList.front().j);
    BoxList.pop_front();
  }

  return;
}

bool DFS(bool Maze[][MAXN + 2], const int InitI, const int InitJ,
         const int FinI, const int FinJ) {
  if (Maze[InitI][InitJ] == 0 || Maze[FinI][FinJ] == 0) return false;

  stack<Box> SqBoxStack;
  Box TempBox;

  SetBox(&TempBox, InitI, InitJ, 0);
  SqBoxStack.push(TempBox);

  while (!SqBoxStack.empty()) {
    TempBox = SqBoxStack.top();
    SqBoxStack.pop();

    if (TempBox.i == FinI && TempBox.j == FinJ) {
      SqBoxStack.push(TempBox);
      PrintRoute(&SqBoxStack);
      return true;
    }

    Maze[TempBox.i][TempBox.j] = false;
    for (bool FindDir = false; TempBox.NextDir <= 4; TempBox.NextDir++) {
      if (FindDir) break;

      switch (TempBox.NextDir) {
        case 0:
          if (Maze[TempBox.i + 1][TempBox.j]) FindDir = true;
          break;
        case 1:
          if (Maze[TempBox.i][TempBox.j + 1]) FindDir = true;
          break;
        case 2:
          if (Maze[TempBox.i - 1][TempBox.j]) FindDir = true;
          break;
        case 3:
          if (Maze[TempBox.i][TempBox.j - 1]) FindDir = true;
          break;
      }
    }

    TempBox.NextDir--;  // 以上For循环会使退出时NextDir多加1
    if (0 <= TempBox.NextDir && TempBox.NextDir <= 3) {
      SqBoxStack.push(TempBox);
      switch (TempBox.NextDir) {
        case 0:
          SetBox(&TempBox, TempBox.i + 1, TempBox.j, 0);
          break;
        case 1:
          SetBox(&TempBox, TempBox.i, TempBox.j + 1, 0);
          break;
        case 2:
          SetBox(&TempBox, TempBox.i - 1, TempBox.j, 0);
          break;
        case 3:
          SetBox(&TempBox, TempBox.i, TempBox.j - 1, 0);
          break;
      }
      SqBoxStack.push(TempBox);
      Maze[TempBox.i][TempBox.j] = true;
    }
  }

  return false;
}

int main(void) {
  bool Maze[10][10] = {{0},
                       {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                       {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                       {0, 1, 1, 1, 1, 0, 0, 1, 1, 0},
                       {0, 1, 0, 0, 0, 1, 1, 1, 1, 0},
                       {0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
                       {0, 1, 0, 1, 1, 1, 0, 1, 1, 0},
                       {0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
                       {0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
                       {0}};

  if (DFS(Maze, 1, 1, 8, 8)) {
    cout << "Success" << endl;
  } else {
    cout << "Fail" << endl;
  }

  return 0;
}