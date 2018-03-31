#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll MAX_SIZE = 100007;
ll mdiff = 0;
bool visited[100007];
vector<ll> adj[100007];
ll control[100007];
ll cunt[2];

ll diff() {
  return cunt[1] > cunt[0]? cunt[1] - cunt[0] : cunt[0] - cunt[1];
}

void dfs(ll v) {
  visited[v] = true;

  cunt[control[v]]++;

  if(diff() == 0) {
    cunt[control[v]] = 1;
    cunt[control[v] ^ 1] = 0;
  }

  if(diff() > mdiff)
    mdiff = diff();

  ll i, sz = adj[v].size();
  for(i = 0; i < sz; i++) {
    if(!visited[adj[v][i]])
      dfs(adj[v][i]);
  }
}

int main() {
  ll N, i, u, v;

  cin >> N;

  for(i = 1; i <= N; i++) {
    cin >> control[i];
  }

  for(i = 1; i < N; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  // for(i = 1; i <= N; i++) {
  //   if(adj[i].size() == 1) {
  //     dfs(i);
  //     break;
  //   }
  // }
  dfs(1);
  cout << mdiff << "\n";

  return 0;
}
