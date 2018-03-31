#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> adj[100007];
bool visited[100007];
ll indegree[100007];
ll etime[100007];
ll req[100007];
vector<ll> sorted;

void mdfs(ll v) {
  visited[v] = true;
  sorted.push_back(v);
  ll i, sz = adj[v].size();

  for(i = 0; i < sz; i++) {
    indegree[adj[v][i]]--;
    if(!visited[adj[v][i]] && indegree[adj[v][i]] == 0)
      mdfs(adj[v][i]);
  }
}

int main() {

  ll n, m, k, i, u, v;

  cin >> n >> m >> k;

  for(i = 1; i <= m; i++) {
    cin >> u >> v;
    // adj[u].insert(lower_bound(adj[u].begin(), adj[u].end(), v), v);
    adj[u].push_back(v);
    indegree[v]++;
  }

  for(i = 1; i <= k; i++) {
    cin >> req[i];
  }

  for(i = 1; i <= n; i++) {
    if(indegree[i] == 0 && !visited[i])
      mdfs(i);
  }

  for(i = 0; i < sorted.size(); i++) {
    cout << sorted[i] << " ";
  }
  cout << "\n";

  return 0;
}
