#include <bits/stdc++.h>

using namespace std;
int sum = 0;
int Limit = 200000;
set <string> k;

struct TNode {
  bool word;
  char allowed;
  TNode* next[26];

  TNode() {
    for(int i = 0; i < 26; i++) {
      this->next[i] = NULL;
    }
    this->word = false;
  }
};

void addTrie(char allowed, string name, TNode* root) {
  cout << "Adding string " << name << " with allowed state " << allowed << "\n";
  int len = name.length();
  char x;

  for(int i = 0; i < len; i++) {
    x = name[i];
    if(i == len - 1) {
      root->word = true;
    }

    if(root->next[ (int)(x - 'a') ] == NULL) {
      root->next[ (int)(x - 'a') ] = (TNode*)malloc(sizeof(TNode));
      root->next[ (int)(x - 'a') ]->allowed = allowed;
      cout << "Appended " << x << " with allowed state" << allowed << "\n";
    }
    else if(allowed == '+') {
      root->next[ (int)(x - 'a') ]->allowed = '+';
      cout << "Changed " << x << " to +\n";
      if(root->next[ (int)(x - 'a') ]->word) {
        sum = Limit * 2;
        return;
      }
    }

    root = root->next[ (int)(x - 'a') ];
  }
}

void dfs(TNode* root, int level, string st) {
  for(int i = 0; i < 26; i++) {
    if(root->next[i] != NULL) {
      cout << "Lvl: " << level << "; string: " << st << "; next: " << (char)(i+'a') << "; allowed of next: " << root->next[i]->allowed << "\n";
      if(root->next[i]->allowed == '-') {
        // insert string into set
        cout << "next: " << (char)(i + 'a') << " is the end of string " << (st + (char)(i + 'a')) << " to be inserted to set\n";
        if(k.insert((st + (char)(i + 'a'))).second) {
          sum += level;
          if(sum >= Limit)
            return;
        }
      }
      else {
        dfs(root->next[i], level + 1, (st + (char)(i + 'a')) );
        if(sum >= Limit)
          return;
      }
    }
  }
}

int main() {
  int siteNum, i, j;
  char allowed;
  string name;

  TNode* root = (TNode*)malloc(sizeof(TNode));

  cin >> siteNum;
  for(i = 0; i < siteNum; i++) {
    cin >> allowed >> name;
    addTrie(allowed, name, root);
  }

  dfs(root, 1, "");
  if(sum >= Limit) {
    cout << "-1" << '\n';
  }
  else {
    int siz = k.size();
    cout << siz << '\n';
    set <string> :: iterator it = k.begin();
    for(it = k.begin(); it != k.end(); it++)
      cout << *it << '\n';
  }

}
