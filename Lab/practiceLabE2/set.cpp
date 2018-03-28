#include <bits/stdc++.h>

using namespace std;

int main() {
  set <string> s;
  auto t = s.insert("hello");
  cout << t.second << '\n';
  t = s.insert("holla");
  cout << t.second << '\n';
  t = s.insert("hello");
  cout << t.second << '\n';

  set<string>::iterator it;

  for(it = s.begin(); it != s.end(); it++) {
    cout << *it << '\n';
  }
}
