#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef long long LL;
const LL MAX = 26;
LL timer;

string all[300000];

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
void addWord(Trie* root, LL stindex, LL subindex, LL stlen, LL prty, LL len) {
  if(stlen == 0) {
    root->word = true;
    // cout << "UPDATED WORD\nnode " << root << " : priority = " << root->priority << ". length = " << root->length << ". word = " << root->word << "\n";
    return;
  }
  char fchar = all[stindex][subindex];
  LL child = transform(fchar);

  // cout << "Adding " << fchar << " to " << root << ". edge[" << child << "] = " << root->edges[child] << "\n";

  if(root->edges[child] == NULL) { // new branch. Modify priority and length
    // cout << "New node being created as NULL.\n";
    root->edges[child] = (Trie*)(malloc(sizeof(Trie)));
    init(root->edges[child], prty, len);
    // cout << "New ";
  }
  // cout << "node " << root->edges[child] << " : priority = " << root->edges[child]->priority << ". length = " << root->edges[child]->length << ". word = " << root->edges[child]->word << "\n";
  addWord(root->edges[child], stindex, (subindex+1), (stlen-1), prty, len);
}

void searchWord(Trie * root, LL stindex, LL subindex, LL stlen, LL level, LL pc, bool step1) {
  LL child = 0;
  char fchar = 'a';

  // cout << "key: " << key << ". level: " << level << ". pc: " << pc << ". node:" << root << "\n";

  if(stlen > 0) {
    fchar = all[stindex][subindex];
    child = transform(fchar);
  }


  if(stlen == 0) { // in case the element is entirely within the system
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
  // cout << "root priority: " << root->priority << ". child (fchar) priority: " << ((root->edges[child] == NULL)?(-1):(root->edges[child]->priority)) << "\n";
  if(root->edges[child] == NULL) { // if the edge does not exist
    timer += stlen;
    // cout << "Timer after mismatch: " << timer << "\n";
    return;
  }
  if(step1 && stlen > 0) {
    timer += 1;
    // cout << "Timer after step1 from completion: " << timer << "\n";
    pc += 1;

    searchWord(root->edges[child], stindex, (subindex+1), (stlen-1), level+1, pc, ((level==0)?false:((root->edges[child]->priority) != (root->priority))) );
    return;
  }
  searchWord(root->edges[child], stindex, (subindex+1), (stlen-1), level+1, pc, ((root->edges[child]->priority) != (root->priority)));
}

int main() {
  LL M=0, N=0, i=0;
  string temp="";

  Trie* root = (Trie*)(malloc(sizeof(Trie)));
  init(root, -1, -1); // the root will be -1, -1 priority and length

  cin >> M >> N;
  for(i = 0; i < M; i++) {
    cin >> all[i];
    LL templen = all[i].length();
    addWord(root, i, 0, templen, (M-i), temp.length());
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
    cin >> all[i];
    timer = 0;
    LL templen = all[i].length();
    searchWord(root, i, 0, templen, 0, 0, true);
    cout << timer << '\n';
    // cout << searchWord() << '\n';
  }
}
