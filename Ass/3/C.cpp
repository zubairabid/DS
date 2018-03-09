#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef long long LL;
const LL MAX = 26;

struct Trie {
  LL priority; // stores the max priority of all the possible words
  LL length; // stores the length of the word depicted by priority
  bool word; // signifies if the node contains a word end or not
  Trie* edges[MAX];
}

// Transforms the character into the integer index equivalent
LL transform(char c) {
  return (int)(c - 'a'); // in this case
}

// defaults everything in new node
void init(Trie* node, LL prty, LL len) {
  node->priority = prty;
  node->length = len;
  node->word = false;
  LL i;
  for(i = 0; i < MAX; i++) {
    node->edges[i] = NULL;
  }
}

// normal addition to dictionary trie, storing priority and length as well
void addWord(Trie* root, string word, LL prty, LL len) {
  if(word.length() == 0) {
    root->word = true;
    return;
  }
  char fchar = word[0];
  LL child = transform(fchar);

  if(root->edges[child] == NULL) { // new branch. Modify priority and length
    root->edges[child] = (Trie*)(malloc(sizeof(Trie)));
    init(root->edges[child], prty, len);
  }
  addWord(edges[child], word.substr(1), prty, len);
}

LL searchWord(Trie* root, string key) {

}

int main() {
  LL M, N, i;
  string temp;

  Trie* root = (Trie*)(malloc(sizeof(Trie)));

  cin >> M >> N;
  for(i = 0; i < M; i++) {
    cin >> temp;
    addWord(root, temp, (M-i), temp.length());
  }

  for(i = 0; i < N; i++) {
    cin >> temp;

  }
}
