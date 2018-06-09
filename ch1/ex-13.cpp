#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int N = 500;

typedef int ElemType;
typedef struct ASet {
  ElemType data[N];
  int amount;
} Aset;

// Declarations
bool InitSetFromArray(ElemType*, int, ASet&);
void DispSet(ASet&);
bool IsInSet(ASet&, ElemType);
ASet& GetCombinedSet(ASet&, ASet&);
ASet& GetComplementarySet(ASet&, ASet&);
ASet& GetIntersection(Aset&, Aset&);

// Fuction Difinitions
bool InitSetFromArray(ElemType* array, int len, ASet& set) {
  if (len <= 0 || len > N) return false;

  for (int i = 0; i < len; i++) {
    if (array[i] <= 0) break;

    if (!IsInSet(set, array[i])) set.data[set.amount++] = array[i];
  }

  cout << set.amount << " elements ware successfully inserted, "
       << len - set.amount
       << " elements were skipped because they were negative or repeated."
       << endl;
  return true;
}

void DispSet(ASet& set) {
  for (int i = 0; i < set.amount; i++) cout << set.data[i] << " ";
  cout << endl;
  return;
}

inline bool IsInSet(ASet& set, ElemType e) {
  for (int i = 0; i < set.amount; i++)
    if (set.data[i] == e) return true;
  return false;
}

ASet& GetComplementarySet(ASet& setA, ASet& setB) {
  ASet *temp = new ASet, &comp = *temp;
  comp.amount = 0;

  if (setB.amount == 0)
    return setA;
  else if (setA.amount == 0)
    return comp;

  ElemType *bucketsA[20], *bucketsB[20];
  for (int i = 0; i < 20; i++) {
    bucketsA[i] = new ElemType[setA.amount];
    bucketsB[i] = new ElemType[setB.amount];
  }

  int bucketTopA[20] = {0}, bucketTopB[20] = {0};

  register int bucketNum;
  for (int i = 0; i < setA.amount; i++) {
    bucketNum = setA.data[i] % 20;
    *(bucketsA[bucketNum] + bucketTopA[bucketNum]++) = setA.data[i];
  }
  for (int i = 0; i < setB.amount; i++) {
    bucketNum = setB.data[i] % 20;
    *(bucketsB[bucketNum] + bucketTopB[bucketNum]++) = setB.data[i];
  }

  const ElemType INVALID = 0xd0000000;
  for (int buk = 0; buk < 20; buk++) {
    for (int i = 0; i < bucketTopA[buk]; i++) {
      for (int j = 0; j < bucketTopB[buk]; j++)
        if (*(bucketsA[buk] + i) == *(bucketsB[buk] + j)) {
          *(bucketsA[buk] + i) = INVALID;
          break;
        }
    }
    for (int i = 0; i < bucketTopA[buk]; i++)
      if (*(bucketsA[buk] + i) != INVALID)
        comp.data[comp.amount++] = *(bucketsA[buk] + i);
  }

  for (int i = 0; i < 20; i++) {
    delete[] bucketsA[i];
    delete[] bucketsB[i];
  }
  return comp;
}

ASet& GetIntersection(ASet& setA, ASet& setB) {
  ASet *temp = new ASet, &inter = *temp;
  inter.amount = 0;

  if (setA.amount == 0 || setB.amount == 0) return inter;

  ElemType *bucketsA[20], *bucketsB[20];
  for (int i = 0; i < 20; i++) {
    bucketsA[i] = new ElemType[setA.amount];
    bucketsB[i] = new ElemType[setB.amount];
  }

  int bucketTopA[20] = {0}, bucketTopB[20] = {0};

  register int bucketNum;
  for (int i = 0; i < setA.amount; i++) {
    bucketNum = setA.data[i] % 20;
    *(bucketsA[bucketNum] + bucketTopA[bucketNum]++) = setA.data[i];
  }
  for (int i = 0; i < setB.amount; i++) {
    bucketNum = setB.data[i] % 20;
    *(bucketsB[bucketNum] + bucketTopB[bucketNum]++) = setB.data[i];
  }

  const ElemType INVALID = 0xd0000000;
  for (int buk = 0; buk < 20; buk++) {
    for (int i = 0; i < bucketTopA[buk]; i++) {
      bool IsInB = false;
      for (int j = 0; j < bucketTopB[buk]; j++)
        if (*(bucketsA[buk] + i) == *(bucketsB[buk] + j)) {
          IsInB = true;
          break;
        }
      if (!IsInB) *(bucketsA[buk] + i) = INVALID;
    }

    for (int i = 0; i < bucketTopA[buk]; i++)
      if (*(bucketsA[buk] + i) != INVALID)
        inter.data[inter.amount++] = *(bucketsA[buk] + i);
  }

  for (int i = 0; i < 20; i++) {
    delete[] bucketsA[i];
    delete[] bucketsB[i];
  }
  return inter;
}

ASet& GetCombinedSet(ASet& setA, ASet& setB) {
  if (setB.amount == 0)
    return setA;
  else if (setA.amount == 0)
    return setB;

  ASet *temp = new ASet, &comb = *temp;
  comb.amount = 0;

  ElemType *bucketsA[20], *bucketsB[20];
  for (int i = 0; i < 20; i++) {
    bucketsA[i] = new ElemType[setA.amount];
    bucketsB[i] = new ElemType[setB.amount];
  }

  int bucketTopA[20] = {0}, bucketTopB[20] = {0};

  register int bucketNum;
  for (int i = 0; i < setA.amount; i++) {
    bucketNum = setA.data[i] % 20;
    *(bucketsA[bucketNum] + bucketTopA[bucketNum]++) = setA.data[i];
  }
  for (int i = 0; i < setB.amount; i++) {
    bucketNum = setB.data[i] % 20;
    *(bucketsB[bucketNum] + bucketTopB[bucketNum]++) = setB.data[i];
  }

  const ElemType INVALID = 0xd0000000;
  for (int buk = 0; buk < 20; buk++) {
    for (int i = 0; i < bucketTopA[buk]; i++) {
      bool IsInB = false;
      for (int j = 0; j < bucketTopB[buk]; j++)
        if (*(bucketsA[buk] + i) == *(bucketsB[buk] + j)) {
          IsInB = true;
          break;
        }
      if (IsInB) *(bucketsA[buk] + i) = INVALID;
    }

    for (int i = 0; i < bucketTopA[buk]; i++)
      if (*(bucketsA[buk] + i) != INVALID)
        comb.data[comb.amount++] = *(bucketsA[buk] + i);

    for (int i = 0; i < bucketTopB[buk]; i++)
      comb.data[comb.amount++] = *(bucketsB[buk] + i);
  }

  for (int i = 0; i < 20; i++) {
    delete[] bucketsA[i];
    delete[] bucketsB[i];
  }
  return comb;
}

int main() {
  // Init buffer -> ASet
  srand((unsigned)time(0));
  ElemType buf1[N], buf2[N];
  const int SET_SIZE = 200;

  for (int i = 0; i < SET_SIZE; i++) {
    buf1[i] = rand() % SET_SIZE;
    buf2[i] = rand() % SET_SIZE;
  }

  ASet set1 = {.amount = 0}, set2 = {.amount = 0};
  cout << "Initialize Set 1:" << endl;
  InitSetFromArray(buf1, SET_SIZE, set1);
  cout << endl;
  cout << "Initialize Set 2:" << endl;
  InitSetFromArray(buf2, SET_SIZE, set2);
  cout << endl;

  // Show 2 sets
  cout << "Set 1: " << endl;
  DispSet(set1);
  cout << endl << endl;

  cout << "Set 2: " << endl;
  DispSet(set2);
  cout << endl << endl;

  // Calculate the combined set between sets, aka set1 ∪ set2
  ASet& comb = GetCombinedSet(set1, set2);

  cout << "Set 1 ∪ Set 2: " << endl;
  if (comb.amount == 0)
    cout << "Nothing";
  else
    DispSet(comb);
  cout << endl << endl;

  // Calculate the complementary set, aka set1 - set2
  ASet& comp = GetComplementarySet(set1, set2);

  cout << "Set 1 - Set 2: " << endl;
  if (comp.amount == 0)
    cout << "Nothing";
  else
    DispSet(comp);
  cout << endl << endl;

  // Calculate the intersection between sets, aka set1 ∩ set2
  ASet& inter = GetIntersection(set1, set2);

  cout << "Set 1 ∩ Set 2: " << endl;
  if (inter.amount == 0)
    cout << "Nothing";
  else
    DispSet(inter);
  cout << endl << endl;

  system("Pause");
  return 0;
}
