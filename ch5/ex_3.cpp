#include <cmath>
#include <iostream>
using namespace std;

inline int GetDigits(unsigned long long n) { return ceil(log(n) / log(10)); }

int main(void) {
  unsigned long long n = 12345678901234567890;
  cout << GetDigits(n) << endl;
}