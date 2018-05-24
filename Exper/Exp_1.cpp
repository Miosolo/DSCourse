
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

typedef struct {
  char Name[20];
  int Age;
  char StuID[20];
} StuInfo;

typedef struct StuNode {
  StuInfo Data;
  StuNode *next;

  ~StuNode() {
    if (this->next) delete this->next;
  }
} StuNode;

bool InitList(fstream *, StuNode *);
void InsertNode(StuNode *, StuNode *);
StuNode *GetMergedList(StuNode *, StuNode *);
void ReverseList(StuNode *);

bool InitList(fstream *infile, StuNode *list) {
  if (!infile->is_open()) return false;

  char buffer[50];
  infile->seekg(0, ios::beg);
  infile->getline(buffer, 100);

  while (infile->getline(buffer, 100)) {
    StuNode *TempNode = new StuNode;
    TempNode->next = NULL;

    char *pin, *pout;

    pin = buffer, pout = TempNode->Data.Name;
    while (*pin != ',') *pout++ = *pin++;
    *pout = 0, ++pin;

    pout = TempNode->Data.StuID;
    while (*pin != ',') *pout++ = *pin++;
    *pout = 0, ++pin;

    int TempValue = 0;
    while (*pin != ',' && *pin != 0) TempValue = TempValue * 10 + *pin++ - '0';
    TempNode->Data.Age = TempValue;

    InsertNode(TempNode, list);
  }

  infile->close();
  return true;
}

void InsertNode(StuNode *stu, StuNode *list) {
  char ThisID[20];
  strcpy(ThisID, stu->Data.StuID);

  StuNode *pnode;
  for (pnode = list;
       pnode->next != NULL && (strcmp(pnode->next->Data.StuID, ThisID) < 0);
       pnode = pnode->next)
    ;

  stu->next = pnode->next;
  pnode->next = stu;
}

StuNode *GetMergedList(StuNode *list1, StuNode *list2) {
  StuNode *p1 = list1, *p2 = list2->next;
  while (p1->next != NULL && p2 != NULL) {
    int dis = strcmp(p1->next->Data.StuID, p2->Data.StuID);
    if (dis < 0) {
      p1 = p1->next;
    } else if (dis == 0) {
      p2->Data.Age = max(p1->next->Data.Age, p2->Data.Age);
      StuNode *temp = p2;
      p2 = p2->next;
      temp->next = p1->next->next;
      p1->next->next = NULL;
      delete p1->next;
      p1->next = temp;
    } else {
      StuNode *temp = p2;
      p2 = p2->next;
      temp->next = p1->next;
      p1->next = temp;
    }
  }

  if (p2 != NULL) p1->next = p2;
  list2->next = NULL;
  delete list2;
  return list1;
}

void ReverseList(StuNode *list) {
  StuNode *TempHead = new StuNode;
  TempHead->next = NULL;

  for (StuNode *p = list->next; p != NULL;) {
    StuNode *temp = p;
    p = p->next;
    temp->next = TempHead->next;
    TempHead->next = temp;
  }

  list->next = TempHead->next;
}

int main(void) {
  //------------------task 1---------------------------
  fstream *csv1 = new fstream;
  csv1->open(
      "C:/Users/mx_028/Dropbox/Programming/C++/DSCourse/Exper/Exp1_"
      "StuInfo1.csv",
      ios::in);
  StuNode *list1 = new StuNode;
  list1->next = NULL;

  if (InitList(csv1, list1)) {
    cout << "\nTask1: Create linked list in the increasing order of Student "
            "ID\n\n";
    for (StuNode *p = list1->next; p != NULL; p = p->next)
      cout << p->Data.Name << " " << p->Data.Age << " " << p->Data.StuID
           << endl;
  }

  //--------------------task 2----------------------
  cout << "\nTask 2: Insert the info of students (enter \"#\" as student ID to "
          "exit)\n\n";
  while (1) {
    StuNode *InputStu = new StuNode;
    InputStu->next = NULL;
    cout << "Input the student's name: " << endl;
    cin >> InputStu->Data.Name;
    cout << "Input the student's age: " << endl;
    cin >> InputStu->Data.Age;
    cout << "Input the student's Student ID: " << endl;
    cin >> InputStu->Data.StuID;

    if (InputStu->Data.StuID[0] != '#')
      InsertNode(InputStu, list1);
    else {
      delete InputStu;
      break;
    }
  }

  //------------------task 3-------------------------
  fstream *csv2 = new fstream;
  csv2->open(
      "C:/Users/mx_028/Dropbox/Programming/C++/DSCourse/Exper/Exp1_"
      "StuInfo2.csv",
      ios::in);
  StuNode *list2 = new StuNode;
  list2->next = NULL;
  InitList(csv2, list2);
  list1 = GetMergedList(list1, list2);

  cout << "\nTask 3: Get merged list\n\n";
  for (StuNode *p = list1->next; p != NULL; p = p->next)
    cout << p->Data.Name << " " << p->Data.Age << " " << p->Data.StuID << endl;

  //---------------task 4--------------------------------
  cout << "\nTask 4: Reverse the merged linked list\n\n";
  ReverseList(list1);
  for (StuNode *p = list1->next; p != NULL; p = p->next)
    cout << p->Data.Name << " " << p->Data.Age << " " << p->Data.StuID << endl;

  delete list1;  //递归释放所有结点（见析构函数）
  return 0;
}
