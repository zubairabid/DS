#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main() {

  set<int> S;
  S.insert(10);
  S.insert(20);
  S.insert(30);
  S.insert(40);
  S.insert(50);
  S.insert(60);
  S.insert(70);
  S.insert(80);

  set<int>::iterator it = S.find(10);

  for(it = S.begin(); it != S.end(); it++) {
    cout << *it << ' ';
  }
  cout << '\n';

  // if you perform an operation modifying the container, all iterators before are invalidated
  // eg:
  it = S.begin();
  S.insert(1);
  it = S.begin(); // needed

  for(it = S.begin(); it != S.end(); it++) {
    cout << *it << ' ';
  }
  cout << '\n';

  return 0;
}
