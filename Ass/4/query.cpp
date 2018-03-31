#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> adj[2000007];
vector<ll> cum[2000007];
bool visited[2000007];
ll esize = 1;

void build(ll v) {
  ll i, j, sz = adj[v].size(), ssz;
  visited[v] = true;
  cum[v].push_back(1);
  // cum[v].resize(1000007);
  cum[v].resize(esize);

  for(i = 0; i < sz; i++) {
    if(!visited[adj[v][i]]) {
      esize--;
      build(adj[v][i]);

      ssz = cum[adj[v][i]].size();
      for(j = 0; j < ssz; j++) {
        cum[v][j+1] += cum[adj[v][i]][j];
      }
    }
  }
  esize++;
}

int main() {
  ll N, Q, i, u, v, d;

  cin >> N >> Q;

  for(i = 1; i < N; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  esize = N;
  build(1);


  for(i = 1; i <= N; i++) {
    cout << i << " : ";
    for(ll j = 0; j < cum[i].size() && cum[i][j] != 0; j++) {
      cout << cum[i][j] << " ";
    }
    cout << "\n";
  }


  for(i = 0; i < Q; i++) {
    cin >> v >> d;
    if(d > 1000000)
      cout << "0\n";
    else
      cout << cum[v][d] << "\n";
  }

  return 0;
}
