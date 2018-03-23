#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 122345;

vector<int> adj[maxN];
vector<int> trans[maxN];
bool visited[maxN];
bool visited2[maxN];
int cost[maxN];
stack <int> stk;

vector <int> scc[maxN];

int dfs(int node) { // returns last node in the dfs
  visited[node] = true;

  int siz = adj[node].size();
  for(int i = 0; i < siz; i++) {
    int element = adj[node][i];
    if(!visited[element])
      dfs(element);
  }

  printf("Pushing %d to the stack\n", node);
  stk.push(node);
}

int dfs2(int node, int temp) { // returns last node in the dfs
  visited2[node] = true;

  int siz = trans[node].size();
  for(int i = 0; i < siz; i++) {
    int element = trans[node][i];
    if(!visited2[element])
      dfs2(element, temp);
  }
  printf("Adding %d to scc[%d]\n", node, temp);
  scc[temp].push_back(node);
}

int main() {
  int vert, edge, i, source, dest;
  scanf("%d", &vert);
  scanf("%d", &edge);

  for(int i = 1; i <= edge; i++) {
    scanf("%d %d", &source, &dest);
    adj[source].push_back(dest);
    printf("Added %d to adj[%d]\n",dest, source);
    // generating the transpose
    trans[dest].push_back(source);
    printf("Added %d to adj[%d]\n",source, dest);
  }

  for(int i = 1; i <= vert; i++) {
    printf("For vertex %d, adj_list is: \n", i);
    for(int j = 0; j < adj[i].size(); j++) {
      printf("%d ", adj[i][j]);
    }
    printf("\n");
  }

  for(int i = 1; i <= vert; i++)
    if(!visited[i])
      dfs(i);

  for(int i = 1; i <= vert; i++)
    if(!visited2[stk.top()]) {
      printf("Running a DFS on vertex %d\n", stk.top());
      dfs2(stk.top(), i);
      stk.pop();
      for(int j = 0; j < scc[i].size(); j++) {
        printf("%d ", scc[i][j]);
      }
      printf("\n");
    }


}
