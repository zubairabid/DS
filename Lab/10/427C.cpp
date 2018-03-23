#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long int maxN = 122345;
const long long int modder = 1000000007;

vector<long long int> adj[maxN];
vector<long long int> trans[maxN];
bool visited[maxN];
bool visited2[maxN];
long long int cost[maxN];
stack <long long int> stk;

vector <long long int> scc[maxN];
long long int mins[maxN];
long long int ct[maxN];

long long int dfs(long long int node) { // returns last node in the dfs
  visited[node] = true;

  long long int siz = adj[node].size();
  for(long long int i = 0; i < siz; i++) {
    long long int element = adj[node][i];
    if(!visited[element])
      dfs(element);
  }

  stk.push(node);
}

long long int dfs2(long long int node, long long int temp) { // returns last node in the dfs
  visited2[node] = true;

  long long int siz = trans[node].size();
  for(long long int i = 0; i < siz; i++) {
    long long int element = trans[node][i];
    if(!visited2[element])
      dfs2(element, temp);
  }

  if(cost[node] < mins[temp]) {
    mins[temp] = cost[node];
    ct[temp] = 1;
  }
  else if(cost[node] == mins[temp]) {
    ct[temp]++;
  }
  
  scc[temp].push_back(node);
}

int main() {
  long long int vert, edge, i, source, dest;
  scanf("%lld", &vert);

  for(long long int i = 1; i <= vert; i++) {
    scanf("%lld", &cost[i]);
  }

  scanf("%lld", &edge);

  for(long long int i = 1; i <= edge; i++) {
    scanf("%lld %lld", &source, &dest);
    adj[source].push_back(dest);
    trans[dest].push_back(source);
  }
  for(long long int i = 1; i <= vert; i++)
    if(!visited[i])
      dfs(i);

  long long int tempiter = 0, sum = 0, prod = 1;
  for(long long int i = 1; i <= vert; i++) {
    if(!visited2[stk.top()]) {
      mins[i] = 1e12;
      dfs2(stk.top(), i);
      tempiter = i;
    }
    stk.pop();
  }
  for(long long int i = 1; i <= tempiter; i++) {
    sum += mins[i];
    if(ct[i] != 0)
      prod = (prod * ct[i])%modder;
  }
  printf("%lld %lld\n", sum, prod);
}
