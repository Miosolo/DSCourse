#include <iostream>
#include <string>
using namespace std;

typedef struct SeqTree {
  string data;
  const char blank = '_';
} SeqTree;

int GetLeavesAmount(SeqTree *sqt) {
  int len = sqt->data.length();
  int amount = 0;

  for (int i = 0; i < len; i++)
    if (sqt->data[i] != sqt->blank &&
        ((i + 1) * 2 > len || (sqt->data[2 * (i + 1) - 1] == sqt->blank &&
                               sqt->data[2 * (i + 1)] == sqt->blank)))
      amount++;

  return amount;
}

int main() {
  string s = "abc_e_g__jk___o";
  SeqTree sqt;
  sqt.data = s;

  cout << "Sequtial Tree: " << s << endl;
  cout << "Amount of leaves: " << GetLeavesAmount(&sqt) << endl;

  return 0;
}