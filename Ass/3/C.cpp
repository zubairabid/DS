#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef long long LL;
const LL MAX = 26;
LL timer;

string all[5000000];
string fall[5000000];

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
  char fchar = fall[stindex][subindex];
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

void searchWord(Trie * root, LL stindex, LL subindex, LL stlen, LL level, LL pc, bool step1, LL len, LL prio) {

  if(level+1 == len) {
    timer += minimize(level - pc, 1 + root->length - level);
    searchWord(root, stindex, (subindex+1), (stlen-1), level + 1, pc, false, len, prio);
  }

  if(root->edges[transform(all[stindex][level])] == NULL) {
    timer += minimize(level - pc, 1 + root->length - level) + len - level;
    searchWord(root, stindex, (subindex+1), (stlen-1), level + 1, pc, false, len, prio);
  }

  if((root->edges[transform(all[stindex][level])])->priority != prio) {
    timer += minimize(level - pc, 1 + root->length - level) + 1;
    pc += 1;
    prio = (root->edges[transform(all[stindex][level])])->priority;
  }
  searchWord(root->edges[transform(all[stindex][level])], stindex, subindex, (stlen - 1), (level + 1), pc, false, len, prio);
}

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  // cout.tie(NULL);

  LL M=0, N=0, i=0;

  for(i = 0; i < 300000; i++) {
    all[i] = string();
    fall[i] = string();
  }

  Trie* root = (Trie*)(malloc(sizeof(Trie)));
  init(root, -1, -1); // the root will be -1, -1 priority and length

  cin >> M >> N;
  for(i = 0; i < M; i++) {
    cin >> fall[i];
    LL templen = (LL)(fall[i].length());
    addWord(root, i, 0, templen, (M-i), templen);
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
    LL templen = (LL)(all[i].length());

    if(root->edges[transform(all[i][0])]) {
      timer = templen;
    }
    else {
      timer = 1;
      LL pc = 1;

      searchWord(root->edges[transform(all[i][0])], i, 0, templen, 0, 0, true, templen, root->priority);
    }
    cout << timer << '\n';
    // cout << searchWord() << '\n';
  }
}
