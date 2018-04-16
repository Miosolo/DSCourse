#include <iostream>
using namespace std;

int main(void) {
  int b = 0b1100;
  cout << b << endl;

  b = b >> 2;
  cout << b;
}