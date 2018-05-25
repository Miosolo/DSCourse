#include <cstring>
#include <iostream>
using namespace std;

void GetReverseStrRec(char* str, char* rstr, int n = 0) {
  int len = strlen(str);

  if (n == len) {
    rstr[n] = 0;
    return;
  } else {
    rstr[n] = str[len - 1 - n];
    GetReverseStrRec(str, rstr, n + 1);
  }
  return;
}

int main(void) {
  char str[20] = "abcdefg";
  char rstr[20] = "\0";

  GetReverseStrRec(str, rstr);
  cout << rstr << endl;
}