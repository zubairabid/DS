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

  if(control[vertex] == ctrl) {
    dp[vertex]++;
  }
  else if(dp[vertex] != 0) {
    dp[vertex]--;
  }

  if(dp[vertex] > maxi)
    maxi = dp[vertex];

  ll d = dp[vertex], temp;


  ll i, sz = adj[vertex].size();
  for(i = 0; i < sz; i++) {

    if(!visited[ adj[vertex][i] ]) {
      dp[ adj[vertex][i] ] = dp[vertex];
      temp = dfs(adj[vertex][i], ctrl);
      if(temp > d) {
        d = temp;
        if(dp[vertex] == 0 && d == 1)
          dp[vertex] = d;
        else if(dp[vertex] == 0 && ctrl != control[vertex])
          dp[vertex] = d-1;
        else
          dp[vertex] = d;
      }
    }

  }
  cout << "dp[" << vertex << "] = " << dp[vertex] << " for ctrl = " << ctrl << "\n";
  return dp[vertex];
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
