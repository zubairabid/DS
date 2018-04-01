#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool stop = false;
vector<ll> adj[100007];
vector<ll> tspose[100007];
ll visited[100007];
ll indegree[100007];
ll comp[100007];
set<ll> ans;
set<ll> todo;
vector<ll> bc;

void dfs(ll v, ll cyc) {
  visited[v] = cyc;
  ans.insert(v);
  ll i, sz = tspose[v].size();
  for(i = 0; i < sz; i++) {
    // check for cycles
    if(!stop && visited[ tspose[v][i] ] == cyc) {
      cout << "GO HOME RAJAS\n";
      stop = true;
      return;
    }

    if(!stop && visited[ tspose[v][i] ] == 0) {
      dfs(tspose[v][i], cyc);
    }
  }
  visited[v] = -1;
}

void topo(ll v) {
  ll i, sz = adj[v].size();
  for(i = 0; i < sz; i++) {
    indegree[adj[v][i]]--;
    if(indegree[adj[v][i]] == 0) {
      todo.insert(adj[v][i]);
    }
  }
  if(ans.find(v) != ans.end())
    bc.push_back(v);// cout << v << " ";
}

int main() {
  ll n, m, k, i, u, v, temp = 1;
  cin >> n >> m >> k;

  for(i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    tspose[v].push_back(u);
    indegree[v]++;
  }

  for(i = 0; i < k; i++) {
    cin >> comp[i];
  }

  for(i = 0; i < k && !stop; i++) {
    if(visited[comp[i]] == 0)
      dfs(comp[i], temp);
  }

  if(!stop) {
    for(i = 1; i <= n; i++) {
      if(indegree[ i ] == 0) {
        todo.insert(i);
      }
    }

    set<ll>::iterator it = todo.begin();
    cout << ans.size() << "\n";
    while(!todo.empty()) {
      temp = *it;
      todo.erase(it);
      topo(temp);
      it = todo.begin();
    }
    ll sz = bc.size();
    for(i = 0; i < sz; i++)
      /*if(visited[bc[i]]==-1) */cout << bc[i] << " ";
    cout << "\n";
  }

  return 0;
}
