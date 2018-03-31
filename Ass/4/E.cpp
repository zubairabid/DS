#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll maxi;
vector<ll> adj[100007];
ll control[100007];
ll dp[100007];
bool visited[100007];

ll dfs(ll vertex, ll ctrl) {
  visited[vertex] = true;
  ll i, sz = adj[vertex].size(), sum = ((ctrl == control[vertex])?1:-1);

  for(i = 0; i < sz; i++) {
    if(!visited[ adj[vertex][i] ])
      sum += dfs(adj[vertex][i], ctrl);
  }
  if(sum > maxi)
    maxi = sum;

  return sum < 0? 0: sum;
}

int main() {
  ll N, i, u, v, temp;

  cin >> N;

  for(i = 1; i <= N; i++) {
    cin >> control[i];
  }

  for(i = 1; i < N; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, 0);
  temp = maxi;

  for(i = 1; i <= N; i++) {
    visited[i] = false;
    dp[i] = 0;
  }
  dfs(1, 1);

  cout << max(temp, maxi) << "\n";

}
