#include <stdio.h>

typedef long long int Llint;
Llint hp[10000007];
Llint ind = 0; // stores the index of the last element

void siftheap(Llint index) {
  if(index == 1)
    return;
  printf("Checking validity at heap[%lld] = %lld, parent is heap[%lld] as %lld\n", index, hp[index], index/2, hp[index/2]);
  if(hp[index] > hp[index/2]) {
      Llint temp = hp[index];
      hp[index] = hp[index/2];
      hp[index/2] = temp;
      siftheap(index/2);
  }
}
// heap implementation: a[x] = parent, a[2x], a[2x+1] = children, start indexing at 1.
// Best question of heap: running median

void heap_insert(Llint data) {
  printf("Inserting %lld into heap index %lld \n", data, (ind+1));
  // insert value to end of array
  hp[++ind] = data;
  printf("Inserted %lld. hp[%lld] = %lld now\n", data, ind, hp[ind]);
  // if hp[end] < hp[end/2] (the parent), then swap hp[end] and hp[end] / 2;
  siftheap(ind);
  // call this one the new val too.
}

void printh() {
  for (Llint i = 1; i <= ind; i++) {
    printf("%lld ", hp[i]);
  }
  printf("\n");
}

int main() {
  /* code */
  Llint temp;
  /*hp[1] = 10;
  hp[2] = 7;
  hp[3] = 6;
  hp[4] = 2;
  hp[5] = 5;
  ind = 5;
  printh();*/
  for (Llint i = 1; i <= 10; i++) {
    scanf("%lld\n", &temp);
    heap_insert(temp);
    printh();
  }
  return 0;
}
