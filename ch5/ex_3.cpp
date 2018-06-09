#include <cmath>
#include <iostream>
using namespace std;

int main(void) {
  unsigned long long n;
  cout << "Enter the numbers: " << endl;

  while (cin >> n) cout << ceil(log(n) / log(10)) << " digits. " << endl;

  return 0;
}