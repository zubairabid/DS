#include <bits/stdc++.h>
#include <string>

using namespace std;

typedef long long ll;

ll enc[30007];
ll key[30007];

struct TNode {
  ll count;
  TNode* edges[2];
};

TNode* newNode() {
  TNode* node = (TNode*)malloc(sizeof(TNode));

  node->count = 1;
  node->edges[0] = NULL;
  node->edges[1] = NULL;
}

ll binlength(ll num) { // calculates length of binary rep of number
  ll c = 1;
  while(num > 1) {
    c++;
    num /= 2;
  }
  return c;
}

void addTrie(Trie* root, string num) {
  ll len = num.length(), i, x, inc = 0;
  Trie* iter = root;

  for(i = 0; i < len; i++) {
    x = (int)(num[i] - 'a');

    if(iter->node[x] != NULL) {

    }
    else {
      iter->node[x] = newNode();
    }

    iter = iter->node[x];
    iter->count += inc;

  }
}

string tostr(ll num, ll destlen) {
  cout << "Entered tostr\n";
  ll len = binlength(num);
  ll shift = len - 1;
  string res = "";
  while(destlen - len > 0) {
    res += '0';
    destlen--;
  }
  while(num > 0) {
    res += to_string((num >> shift));
    num = num - ((num >> shift) << shift);
    shift--;
  }
  return res;
}

int main() {
  ll N, i, maxlen = 0;
  // input N
  cin >> N;

  // input N encrypted jokes
  for(i = 0; i < N; i++) {
    cin >> enc[i];
  }

  // input N keys
  for(i = 0; i < N; i++) {
    cin >> key[i];
    if(binlength(key[i]) > maxlen)
      maxlen = binlength(key[i]);
  }

  // add to the tries
  for(i = 0; i < N; i++) {
    addTrie(tostr(key[i], maxlen));
  }

  // for each joke, minimum XOR against trie


  return 0;
}
