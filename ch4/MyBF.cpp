#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char *MyBF(char *str, char *pat) {
  int Match = 0, MatchLen = 0, StrLen = strlen(str), PatLen = strlen(pat);

  while (Match < StrLen) {
    while (str[Match] != pat[0] && Match < StrLen) Match++;

    while (str[Match + MatchLen] == pat[MatchLen]) {
      MatchLen++;

      if (MatchLen == PatLen) return str + Match;
    }

    Match++, MatchLen = 0;
  }

  return NULL;
}

int main(void) {
  char str[] = "acbd", pat[] = "ui";
  cout << MyBF(str, pat) << endl;

  return 0;
}