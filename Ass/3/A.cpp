#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef long long LL;
const LL ELEM = 5;
LL OVERFLOW = 0;

struct Trie {
  bool matched;
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
  node->matched = false;
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
    child = transform(fchar); // transforms character into indexable

    if(node->edges[child] == NULL) { // new word node/subtree
      node->edges[child] = (Trie*)malloc(sizeof(Trie));
      init(node->edges[child]);
    }

    addWord(node->edges[child], word.substr(1));
  }
}

LL searchTrie(Trie* root, string key, bool clear) { // looks inside the trie for number of matches
  char fchar;
  LL child, i, accu = 0;

  if(key.length() == 0 && !clear) {
    if(root->words > 0 && root->matched) {/*cout << "Matched before\n" ; OVERFLOW++;*/ return 0;}
    if(root->words > 0) {root->matched = true;}
    return root->words;
  }
  else if(key.length() == 0 && clear) {
    root->matched = false;
    return 0;
  }

  fchar = key[0];
  child = transform(fchar);

  key = key.substr(1);

  // for every character, there are 3 possibilities:
  // 1. The character exists in the children nodes: if length of reduced key is 0, return word count of node
  // 2. The character does not exist in the children nodes: return 0 here.
  // 3. The character is a ?: 1. Run again on same node; 2. Run iteratively on all possible children

  if(fchar == '?') {
    // run all tests
    accu += searchTrie(root, key, clear); // same
    for(i = 0; i < ELEM; i++) {
      if(root->edges[i] != NULL) {
        accu += searchTrie(root->edges[i], key, clear);
      }
    }
    return accu;
  }
  else if (root->edges[child] != NULL){
    return searchTrie(root->edges[child], key, clear);
  }
  else if(root->edges[child] == NULL) {
    return 0;
  }
}

int main() {
  // Trie root = new Trie();
  Trie* root = (Trie*)malloc(sizeof(Trie));
  init(root);

  string word;
  LL n, wrong, i;

  cin >> n;
  for(i = 0; i < n; i++) {
    cin >> word;

    addWord(root, word);
  }

  cin >> wrong;
  for(i = 0; i < wrong; i++) {
    cin >> word;
    cout << (searchTrie(root, word, false)) << '\n';
    searchTrie(root, word, true);
    OVERFLOW = 0;
  }

}
