#include <iostream>
using namespace std;

class LkNode {
 public:
  int num;
  LkNode* next;

 public:
  ~LkNode(void) {
    cout << "Node " << num << " destroyed." << endl;
    if (next != NULL) {
      delete next;
    } else {
      cout << "All destroyed." << endl;
    }
  }
};

int main(void) {
  LkNode* h1 = new LkNode;
  h1->next = new LkNode;

  h1->next->num = 1;
  h1->next->next = new LkNode;

  h1->next->next->num = 2;
  h1->next->next->next = NULL;

  delete h1;
}