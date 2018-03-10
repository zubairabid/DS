#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef long long LL;
const LL MAX = 26;
LL timer;

struct Trie {
  LL priority; // stores the max priority of all the possible words
  LL length; // stores the length of the word depicted by priority
  bool word; // signifies if the node contains a word end or not
  Trie* edges[MAX];
};

LL minimize(LL a, LL b) {
  return a<b?a:b;
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
  LL i = 0;
  for(i = 0; i < MAX; i++) {
    node->edges[i] = NULL;
  }
}

// normal addition to dictionary trie, storing priority and length as well
void addWord(Trie* root, string &word, LL prty, LL len) {
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
  string trump = word.substr(1);
  addWord(root->edges[child], trump, prty, len);
}

void searchWord(Trie * root, string &key, LL level, LL pc, bool step1) {
  LL child = 0;
  char fchar = 'a';

  if(key.length() > 0) {
    fchar = key[0];
    child = transform(fchar);
  }


  if(key.length() == 0) { // in case the element is entirely within the system
    timer += minimize(level - pc, 1 + root->length - level);
    return;
  }
  if((root->edges[child] == NULL) || ((root->edges[child]->priority) != (root->priority))) { // there will be a priority shift
    timer += minimize(level - pc, 1 + root->length - level);
    pc = level;
  }

  if(root->edges[child] == NULL) { // if the edge does not exist
    timer += key.length();
    return;
  }
  if(step1 && key.length() > 0) {
    timer += 1;
    pc += 1;
    string trump = key.substr(1);
    searchWord(root->edges[child], trump, level+1, pc, ((level==0)?false:((root->edges[child]->priority) != (root->priority))) );
    return;
  }
  string trump = key.substr(1);
  searchWord(root->edges[child], trump, level+1, pc, ((root->edges[child]->priority) != (root->priority)));
}

int main() {
  LL M=0, N=0, i=0;
  string temp="";

  Trie* root = (Trie*)(malloc(sizeof(Trie)));
  init(root, -1, -1); // the root will be -1, -1 priority and length

  cin >> M >> N;
  for(i = 0; i < M; i++) {
    cin >> temp;
    addWord(root, temp, (M-i), temp.length());
  }

  for(i = 0; i < N; i++) {
    cin >> temp;
    timer = 0;
    searchWord(root, temp, 0, 0, true);
    cout << timer << '\n';
    // cout << searchWord() << '\n';
  }
}
