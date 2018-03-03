#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
  map<string, int> H;
  // key, value

  H["hello"] = 4;
  H["world"] = 5;
  H["say"] = 6;

  // iterators:

  map<string, int>::iterator it = H.begin();
  string i;
  int j;
  // *it is a pair
  i = (*it).first; // key
  j = (*it).second; // value
  std::cout << i << " : " << j  << '\n';

  it->first; // key
  it->second; // value
  std::cout << i << " : " << j  << '\n';

  H.insert(make_pair("test", 0));
  j = H.find("test")->second;
  cout << j << '\n';

  map<string, int>::iterator k = H.find("test");
  std::cout << k->first << " : " << k->second  << '\n';

  list<int> L;
  L.push_front(1);
  L.push_back(2);
  L.push_back(3);
  L.pop_front();
  L.pop_back();
  list<int>::iterator lit;
  lit = L.begin();
  lit++;
  lit++;
  // O(n) time
  L.erase(lit);
  // L.insert(it, 2); // iterating is O(n)
  // find out if list iterators get invalidated after updates to the list
  cout << sizeof int << '\n';
}

string operator + (string a, string b) {
  return "I\'m sorry Bill, I\'m afraid I can\'t let you do that.";
}

/*
  vector

  stack
  queue
  priority_queue
  map
  pair

  list
*/
