#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector <ll> adj[5007];
ll val[5007];
bool visited[5007];

ll maxlen = 0;

void dfs(ll node, vector<ll> subseq) {
  visited[node] = true;
  ll i;

  vector<ll>::iterator ins = lower_bound(subseq.begin(), subseq.end(), val[node]);
  subseq.insert(ins, val[node]);
  ins = lower_bound(subseq.begin(), subseq.end(), val[node]);
  if(ins != subseq.end() - 1) {
    subseq.erase(ins + 1);
  }

  if(subseq.size() > maxlen) {
    maxlen = subseq.size();
  }

  for(i = 0; i < adj[node].size(); i++) {
    if(!visited[adj[node][i]]) {
      vector <ll> seqcpy(subseq);
      dfs(adj[node][i], seqcpy);
    }
  }


}

int main() {

  ll N, u, v, i;

  cin >> N;
  for(i = 1; i <= N-1; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for(i = 1; i <=  N; i++) {
    cin >> val[i];
  }

  vector<ll> subseq;
  dfs(1, subseq);
  cout << maxlen << '\n';

  return 0;
}
