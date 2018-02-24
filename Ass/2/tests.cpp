#include <bits/stdc++.h>
#include <iostream>

typedef struct name_t {
  int a;
  int b;
} n;

typedef std::vector<n *> vec;

vec arr[10];

int main() {

  for (int i = 0; i < 10; i++) {
    /* code */
    arr[i].reserve(10);
    for (int j = 0; j < 20; j++) {
      std::cout << arr[i].size() << ' ';
      n * p = (n*)malloc(sizeof(n));
      p->a = j;
      p->b = i-j;
      arr[i].push_back(p);
    }
  }

  for (int i = 0; i < 10; i++) {
    arr[i].reserve(10);

    for(int j = 0; j < arr[i].size(); j++) {
      n * p = arr[i][j];
      std::cout << p->a << ' ' << p->b << '\t';
    }

    // for (n* p : arr[i]) {
    //   std::cout << p->a << ' ' << p->b << '\t';
    // }
    std::cout << '\n';
  }

  return 0;
}
