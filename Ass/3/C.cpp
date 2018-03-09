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
  LL i;
  for(i = 0; i < MAX; i++) {
    node->edges[i] = NULL;
  }
}

// normal addition to dictionary trie, storing priority and length as well
void addWord(Trie* root, string word, LL prty, LL len) {
  if(word.length() == 0) {
    root->word = true;
    // cout << "UPDATED WORD\nnode " << root << " : priority = " << root->priority << ". length = " << root->length << ". word = " << root->word << "\n";
    return;
  }
  char fchar = word[0];
  LL child = transform(fchar);

  // cout << "Adding " << fchar << " to " << root << ". edge[" << child << "] = " << root->edges[child] << "\n";

  if(root->edges[child] == NULL) { // new branch. Modify priority and length
    // cout << "New node being created as NULL.\n";
    root->edges[child] = (Trie*)(malloc(sizeof(Trie)));
    init(root->edges[child], prty, len);
    // cout << "New ";
  }
  // cout << "node " << root->edges[child] << " : priority = " << root->edges[child]->priority << ". length = " << root->edges[child]->length << ". word = " << root->edges[child]->word << "\n";
  addWord(root->edges[child], word.substr(1), prty, len);
}

void searchWord(Trie * root, string key, LL level, LL pc, bool step1) {
  LL child;
  char fchar;

  // cout << "key: " << key << ". level: " << level << ". pc: " << pc << ". node:" << root << "\n";

  if(key.length() > 0) {
    fchar = key[0];
    child = transform(fchar);
  }

  if(step1) {
    if(root->edges[child] == NULL) {
      timer += key.length();
      // cout << "Timer after mismatch in step step: " << timer << "\n";
      return;
    }
    timer += 1;
    // cout << "Timer after step1 from completion: " << timer << "\n";
    pc += 1;
    searchWord(root->edges[child], key.substr(1), level+1, pc, false);
    return;
  }

  if(key.length() == 0) { // in case the element is entirely within the system
    timer += minimize(level - pc, 1 + root->length - level);
    // cout << "Timer after key exhausts: " << timer << "\n";
    return;
  }
  // cout << "root->word: " << root->word << "\n";
  if(/*root->word*/(root->edges[child] == NULL) || ((root->edges[child]->priority) != (root->priority))) { // there will be a priority shift
    timer += minimize(level - pc, 1 + root->length - level);
    // cout << "Timer after priority shift: " << timer << "\n";
    pc = level;
  }

  // cout << "fchar: " << fchar << ". child: " << child << ". edges[child]: " << root->edges[child] << "\n";
  // cout << "fchar priority: " << root->priority << ". child priority: " << root->edges[child]->priority << "\n";
  if(root->edges[child] == NULL) { // if the edge does not exist
    timer += key.length();
    // cout << "Timer after mismatch: " << timer << "\n";
    return;
  }
  searchWord(root->edges[child], key.substr(1), level+1, pc, ((root->edges[child]->priority) != (root->priority)));
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

  // TRIE TESTS. POSITIVE RESULT.
  // for(i = 0; i < MAX; i++) {
  //   cout << (root->edges[i]) << '\t';
  // }
  // cout << '\n';
  //
  // for(i = 0; i < MAX; i++) {
  //   if(root->edges[i] != NULL) cout << (root->edges[i]->priority) << ' '; else cout << ' ';
  // }
  // cout << '\n';
  //
  // for(i = 0; i < MAX; i++) {
  //   if(root->edges[i] != NULL) cout << (root->edges[i]->length) << ' '; else cout << ' ';
  // }
  // cout << '\n';
  //
  // for(i = 0; i < MAX; i++) {
  //   if(root->edges[i] != NULL) cout << (root->edges[i]->word) << ' '; else cout << ' ';
  // }
  // cout << '\n';
  //
  // for(i = 0; i < MAX; i++) {
  //   cout << (root->edges[0]->edges[i]) << ' ';
  // }
  // cout << '\n';
  //
  // for(i = 0; i < MAX; i++) {
  //   if(root->edges[0]->edges[i] != NULL) cout << (root->edges[0]->edges[i]->priority) << ' '; else cout << ' ';
  // }
  // cout << '\n';
  //
  // for(i = 0; i < MAX; i++) {
  //   if(root->edges[0]->edges[i] != NULL) cout << (root->edges[0]->edges[i]->length) << ' '; else cout << ' ';
  // }
  // cout << '\n';



  for(i = 0; i < N; i++) {
    cin >> temp;
    timer = 0;
    searchWord(root, temp, 0, 0, true);
    cout << timer << '\n';
    // cout << searchWord() << '\n';
  }
}
