#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
using namespace std;

#define MAXM 8
#define MAXN 8
#define MAXQUEUE 500

typedef struct {
  int i, j, LastIndex;
} Box;

class SqBoxQueue {
 private:
  Box data[MAXQUEUE];
  int front, rear;

 public:
  SqBoxQueue() : front(-1), rear(-1) {}
  bool empty() { return front == rear; }
  bool full();
  bool enQueue(Box);
  Box head();
  void deQueue();
  void PrintRoute(int, int);
};
bool SqBoxQueue::full() { return rear == MAXQUEUE - 1; }
bool SqBoxQueue::enQueue(Box B) {
  if (this->full()) return false;

  data[++rear] = B;
  return true;
}
Box SqBoxQueue::head() { return data[front + 1]; }
void SqBoxQueue::deQueue() { front++; }
void SqBoxQueue::PrintRoute(int FinI, int FinJ) {
  int FinIndex = rear;
  for (; data[FinIndex].i == FinI && data[FinIndex].j == FinJ; FinIndex--)
    ;

  list<Box> BoxList;
  Box TempBox = data[FinIndex];
  BoxList.push_front(TempBox);

  while (TempBox.LastIndex != -1) {
    TempBox = data[TempBox.LastIndex];
    BoxList.push_front(TempBox);
  }
  BoxList.push_front(TempBox);

  while (!BoxList.empty()) {
    printf("(%d, %d) -> ", BoxList.front().i, BoxList.front().j);
    BoxList.pop_front();
  }

  return;
}

Box InitBox(int i, int j, int Pre) {
  Box B;
  B.i = i;
  B.j = j;
  B.LastIndex = Pre;

  return B;
}

bool BFS(bool Maze[][MAXN + 2], const int InitI, const int InitJ,
         const int FinI, const int FinJ) {
  if (Maze[InitI][InitJ] == 0 || Maze[FinI][FinJ] == 0) return false;

  SqBoxQueue BoxQ;
  Box TempBox;
  BoxQ.enQueue(InitBox(InitI, InitJ, -1));
  int FrontCounter = 0;
  Maze[InitI][InitJ] = 0;

  while (!BoxQ.empty()) {
    TempBox = BoxQ.head();
    BoxQ.deQueue();

    if (TempBox.i == FinI && TempBox.j == FinJ) {
      BoxQ.PrintRoute(FinI, FinJ);
      return true;
    }

    if (Maze[TempBox.i + 1][TempBox.j]) {
      BoxQ.enQueue(InitBox(TempBox.i + 1, TempBox.j, FrontCounter++));
      Maze[TempBox.i + 1][TempBox.j] = 0;
    }
    if (Maze[TempBox.i][TempBox.j + 1]) {
      BoxQ.enQueue(InitBox(TempBox.i, TempBox.j + 1, FrontCounter++));
      Maze[TempBox.i][TempBox.j + 1] = 0;
    }
    if (Maze[TempBox.i - 1][TempBox.j]) {
      BoxQ.enQueue(InitBox(TempBox.i - 1, TempBox.j, FrontCounter++));
      Maze[TempBox.i - 1][TempBox.j] = 0;
    }
    if (Maze[TempBox.i][TempBox.j - 1]) {
      BoxQ.enQueue(InitBox(TempBox.i, TempBox.j - 1, FrontCounter++));
      Maze[TempBox.i][TempBox.j - 1] = 0;
    }
  }
  return false;
}

int main(void) {
  bool Maze[MAXM + 2][MAXN + 2] = {{0},
                                   {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                                   {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                                   {0, 1, 1, 1, 1, 0, 0, 1, 1, 0},
                                   {0, 1, 0, 0, 0, 1, 1, 1, 1, 0},
                                   {0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
                                   {0, 1, 0, 1, 1, 1, 0, 1, 1, 0},
                                   {0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
                                   {0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
                                   {0}};

  if (BFS(Maze, 1, 1, 3, 3)) {
    cout << "Success" << endl;
  } else {
    cout << "Fail" << endl;
  }

  return 0;
}