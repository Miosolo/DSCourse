#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int GetNextArrMax(char *pat) {
  int PatLen = strlen(pat);
  int cur = 1, k = -1;
  int *next = new int[PatLen + 1];
  // next[n]显示了前面字串的前缀-后缀重复，为了求得每个字符的前缀重复串长度构造(n+1)项
  next[0] = k;

  while (cur < PatLen) {
    if (k == -1 || pat[cur] == pat[k]) {
      k++, cur++;
      next[cur] = k;
    } else
      k = next[k];
  }

  int result = *max_element(next + 1, next + PatLen + 1);
  delete[] next;
  return result;
}

void GetMaxSubString(char *str, int &MaxIndex, int &Length) {
  int StrLen = strlen(str);
  Length = 0, Length = 0;

  for (int i = 0; i < StrLen; i++) {
    int ThisMax = GetNextArrMax(str + i);
    if (ThisMax >= Length) {
      Length = ThisMax;
      MaxIndex = i;
    }
  }
  return;
}

int main(void) {
  char str[100];
  int MI, L;
  while (1) {
    cout << "Enter a string: ";
    if (!(cin >> str)) break;

    GetMaxSubString(str, MI, L);
    cout << "Max substring index: ";
    if (L != 0)
      cout << MI;
    else
      cout << "N/A";

    cout << "\t"
         << "Max substring length: " << L << endl;
  }

  return 0;
}