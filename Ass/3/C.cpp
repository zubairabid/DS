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
  addWord(root->edges[child], word.substr(1), prty, len);
}

/*
  1st character is always entered manually.
  We update the count of steps at every priority change, word end, and new form
*/
LL searchWord(Trie* root, string key, LL level, LL pc) {
  char fchar;
  LL child = 0;

  if(key.length() > 0) {
    char fchar = key[0];
    LL child = transform(fchar);

    cout << "Looking for character " << fchar << " in key " << key << ", child is " << child << "\n";
    cout << (root->edges[child] != NULL) << '\n';
  }
  LL count = 0;

  if(level == 0) { // if we're just starting
    if(root->edges[child] == NULL) {
      pc = 1;
      count += 1;
      cout << "Just started. pc = " << pc << ". count = " << count << ". Calling next\n";
      count += searchWord(root, key.substr(1), level + 1, pc);
      return count;
    }
    else {
      cout << "Since it exists not i need not bother\n";
      return key.length();
    }
  }
  if(key.length() == 0) { // end of the key word
    cout << "Key ended. Adding to count minimum of " << (level - pc) << " and " << -(1+root->length - level) << ".\n";
    cout << level << " " << root->length << '\n';
    count += minimize((level - pc), -(1 + (root->length - level))); // minimum of indi steps vs tab completion
    return count;
  }
  if(root->word == true) { // priority change after
    cout << "Priority change after this node. Adding to count minimum of " << (level - pc) << " and " << -(1+root->length - level) << ".\n";
    count += minimize((level - pc), -(1 + (root->length - level))); // minimum of indi steps vs tab completion
    pc = level;
    cout << "New pc = " << level << "\n";
  }
  if(root->edges[child] != NULL) { // Manually add everything
    cout << "Rest of key does not exist in trie. It shall be added character by character, so " << key.length() << " characters of " << key << '\n';
    count += (key.length());
    return count;
  }
  cout << "Calling on the next set\n";
  count += searchWord(root, key.substr(1), level + 1, pc);
  return count;
}

int main() {
  LL M, N, i;
  string temp;

  Trie* root = (Trie*)(malloc(sizeof(Trie)));
  init(root, -1, -1); // the root will be -1, -1 priority and length

  cin >> M >> N;
  for(i = 0; i < M; i++) {
    cin >> temp;
    addWord(root, temp, (M-i), temp.length());
  }

  for(i = 0; i < MAX; i++) {
    cout << root->edges[i] << " ";
  }
  cout << '\n';
  for(i = 0; i < MAX; i++) {
    cout << (root->edges[i]!=NULL) << " ";
  }
  cout << '\n';

  for(i = 0; i < N; i++) {
    cin >> temp;
    cout << searchWord(root, temp, 0, 0) << '\n';
  }
}
