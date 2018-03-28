#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll EDMAX = 100007;

vector <ll> adj[EDMAX];
ll vispath[EDMAX];
bool visited[EDMAX];

ll dfs(ll source, ll dest) {
  visited[source] = true;

  if(source == dest)
    return 1;

  ll pathsum = 0;

  ll siz = adj[source].size();
  for(ll i = 0; i < siz; i++) {
    ll element = adj[source][i];
    if(!visited[element])
      pathsum = (pathsum + dfs(element, dest)) % MOD;
    else
      pathsum = (pathsum + vispath[element]) % MOD;
  }

  vispath[source] = pathsum;
  return pathsum;
}

int main() {
  ll vert, edge, i, source, dest, a, b;
  cin >> vert >> edge;
  cin >> source >> dest;
  vispath[dest] = 1;
  for(i = 1; i <= edge; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
  }

  cout << dfs(source, dest) << '\n';
}
