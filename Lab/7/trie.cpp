#include <bits/stdc++.h>

#define MAXM 26;

struct Node {
  struct Node * ptr[MAXM];
  Node() {
    for(int i = 0; i < MAXM; i++) {
      ptr[i] = NULL;
    }
  }
};
