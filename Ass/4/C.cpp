#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool stop = false;
vector<ll> adj[100007];
vector<ll> ng[100007];
vector<ll> tspose[100007];
ll visited[100007];
ll indegree[100007];
ll comp[100007];
vector<ll> ans;
set<ll> todo;

void dfs(ll v, ll cyc) {
  visited[v] = cyc;
  ll i, sz = tspose[v].size();
  for(i = 0; i < sz; i++) {
    ng[ tspose[v][i] ].push_back(v);
    indegree[v]++;
    // check for cycles
    if(visited[ tspose[v][i] ] == cyc) {
      cout << "GO HOME RAJAS\n";
      stop = true;
      return;
    }

    if(!stop && visited[ tspose[v][i] ] == 0)
      dfs(tspose[v][i], cyc);
  }
  visited[v] = -1;
}

void topo(ll v) {
  ll i, sz = ng[v].size();
  for(i = 0; i < sz; i++) {
    indegree[ng[v][i]]--;
    if(indegree[ng[v][i]] == 0) {
      todo.insert(ng[v][i]);
    }
  }
  ans.push_back(v);
}

int main() {
  ll n, m, k, i, u, v, temp = 1;
  cin >> n >> m >> k;

  for(i = 0; i < m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    tspose[v].push_back(u);
  }

  for(i = 0; i < k; i++) {
    cin >> comp[i];
  }

  for(i = 0; i < k && !stop; i++) {
    if(visited[comp[i]] == 0)
      dfs(comp[i], temp++);
  }

  if(!stop) {
    for(i = 1; i <= n; i++) {
      if(indegree[ i ] == 0 && visited[ i ] != 0) {
        todo.insert(i);
      }
    }

    set<ll>::iterator it = todo.begin();

    while(todo.size() > 0) {
      temp = *it;
      todo.erase(it);
      topo(temp);
      it = todo.begin();
    }


    cout << ans.size() << "\n";
    temp = ans.size();
    for(i = 0; i < temp; i++) {
      cout << ans[i] << " ";
    }
    cout << "\n";
  }

  return 0;
}
