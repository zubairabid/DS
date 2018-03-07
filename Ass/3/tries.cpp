#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <stdlib.h>

using namespace std;

typedef long long LL;
const LL ELEM = 5;

struct Trie {
  LL words;
  LL prefixes;
  Trie* edges[ELEM];
};

// Transforms the character into the integer index eq
LL transform(char c) {
  return (int)(c - 'a'); // in this case
}

// Initialises everything in a new trie node to null
void init(Trie* node) {
  LL i;
  node->words = 0;
  node->prefixes = 0;
  for(i = 0; i < ELEM; i++) {
    node->edges[i] = NULL;
  }
}

// Assumes a character '$' which does not normally exist in word was added to it
void addWord(Trie* node, string word) {
  if(word.length() == 0) {
    node->words++;
  }
  else {
    char fchar; // stores the first character of the word
    LL child; // stores the index equivalent of fchar
    node->prefixes++; // obviously
    fchar = word[0];
    child = transform(fchar);
    if(node->edges[child] == NULL) { // new word node/subtree
      // node.edges[child] = new Trie();
      node->edges[child] = (Trie*)malloc(sizeof(Trie));
      init(node->edges[child]);
    }
    addWord(node->edges[child], word.substr(1));
  }
}

int main() {
  // Trie root = new Trie();
  Trie* root = (Trie*)malloc(sizeof(Trie));
  init(root);

  LL n;

  cin >> n;
  while(n > 0) {
    string word;
    cin >> word;

    addWord(root, word);
    n--;
  }

  
}
