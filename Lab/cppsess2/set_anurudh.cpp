#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct fuck {
  int babby;
  int stork;
};

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

  // addition and subtraction are only enabled for random access operators
  // set is not a random access operator
  // so ++ works with set, but + b wont

  it = S.find(1209/*some random bullcrap*/);
  if(it == S.end()) {
    cout << "NOT FOUND\n";
  }


  // upper_bound is >
  // lesser_bound is >= if not there, <= otherwise, not sure
  // for 20:
  // 10 10 10 20 20 20 30 30 30
  //          ^lb            ^ub
  // 10 10 10 30 30
  //          ^^ ub, lb
  //


  set<int> bounds;
  bounds.insert(10);
  bounds.insert(10);
  bounds.insert(10);
  bounds.insert(20);
  bounds.insert(20);
  bounds.insert(30);
  bounds.insert(30);

  set<int>::iterator it3;

  for(it3 = bounds.begin(); it3 != bounds.end(); it3++) {
    cout << *it3 << "  ";
  }
  cout << '\n';

  set<int>::iterator it1 = bounds.lower_bound(100);
  set<int>::iterator it2 = bounds.upper_bound(100);

  cout << *it1 << ' ' << *it2 << '\n';
  cout << *(bounds.find(*it2)) << '\n';

  set<fuck> q;
  fuck ob1 = (fuck)malloc(sizeof(fuck));
  ob1.babby = 1;
  ob1.stork = 1;
  q.add(ob1);

  return 0;
}
