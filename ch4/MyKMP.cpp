#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

char *MyKMP(char *, char *);
void GenerateNextArr(char *, int *);

char *MyKMP(char *str, char *pat) {
  int StrLen = strlen(str), PatLen = strlen(pat);
  int next[PatLen];
  GenerateNextArr(pat, next);
  int Match = 0, MatchLen = next[Match];

  while (1) {
    if (Match + MatchLen >= StrLen) return NULL;

    if (MatchLen == -1) Match++, MatchLen++;

    while (str[Match + MatchLen] == pat[MatchLen]) {
      MatchLen++;

      if (MatchLen == PatLen) return (str + Match);
    }
    Match += MatchLen - next[MatchLen], MatchLen = next[MatchLen];
  }
}

void GenerateNextArr(char *pat, int *next) {
  int PatLen = strlen(pat);
  int cur = 0, k = -1;
  next[0] = k;

  while (cur < PatLen) {
    if (k == -1 || pat[cur] == pat[k]) {
      k++, cur++;
      if (pat[cur] != pat[k])
        next[cur] = k;
      else
        next[cur] = next[k];
    } else
      k = next[k];
  }
  return;
}

int main(void) {
  char str[] = "BBC ABCDAB ABCDABCDABDE";
  char pat[] = "ABCDABD";

  cout << "Pattern Matched at charactor No." << (MyKMP(str, pat) - str + 1)
       << endl;
  return 0;
}