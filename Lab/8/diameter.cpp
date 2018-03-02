#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 12234;

vector<int> adj[maxN];
bool visited[maxN];

int max_len = 0;
int shesh = 0;

int dfs(int node, int len) { // returns last node in the dfs
  visited[node] = true;
  len++;

  if(len > max_len) {
    max_len = len;
    shesh = node;
  }

  for(int i = 0; i < adj[node].size(); i++) {
    int element = adj[node][i];
    if(!visited[element]) dfs(element, len);
  }

}

int main() {
  int number, i, node, child;
  scanf("%d", &number);

  for(i = 0; i < number-1; i++) {
    scanf("%d", &node);
    scanf("%d", &child);

    adj[node].push_back(child);
    adj[child].push_back(node);
  }

  for(i = 0; i < maxN; i++) {
    visited[i] = false;
  }

  dfs(0, -1);
  for(i = 0; i < maxN; i++) {
    visited[i] = false;
  }
  dfs(shesh, -1);
  printf("%d\n", max_len);
}
