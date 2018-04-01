#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> adj[1000007];
bool visited[1000007];
ll ranges[1000007][2];
ll flat[2000014];
ll c = 1;

template <typename T>
class SegTree {
public:
  SegTree(ll tSize) {
    this->eNum = tSize;
    st.resize(2*tSize);
  }

  void insert(vector<T> data) {
    copy_backward(data.begin(), data.end(), st.end());
    for(ll i = eNum*2-1; i >= eNum; i--)
      cout << " st[" << i << "][" << 0 << "]: " << st[i][0] << "\n";
    build(eNum-1);
  }

  ll query(ll l, ll r, ll x) { // Assume 1 indexing for this problem, [) format
    ll res = 0;
    for(l = l + eNum - 1, r = r + eNum - 1; l < r; l = l/2, r = r/2) {
      if(l % 2 == 1) {
        cout << "Looking inside st[" << l << "] : " << (upper_bound(st[l].begin(), st[l].end(), x) - lower_bound(st[l].begin(), st[l].end(), x)) << " found\n";
        res += (upper_bound(st[l].begin(), st[l].end(), x) - lower_bound(st[l].begin(), st[l].end(), x));
        l++;
      }
      if(r % 2 == 1) {
        r--;
        cout << "Looking inside st[" << r << "] : " << (upper_bound(st[r].begin(), st[r].end(), x) - lower_bound(st[r].begin(), st[r].end(), x)) << " found\n";
        res += (upper_bound(st[r].begin(), st[r].end(), x) - lower_bound(st[r].begin(), st[r].end(), x));
      }
    }
    return res;
  }

private:
  vector<T> st;
  ll eNum;

  void build(ll b_end) {
    if(b_end == 0) return;
    ll i, j = 0, k = 0;
    for(i = 0; i < st[b_end*2].size() + st[b_end*2 + 1].size(); i++) {
      if(k >= st[b_end*2+1].size() || (j < st[b_end*2].size() && st[b_end*2][j] <= st[b_end*2+1][k])) st[b_end].push_back(st[b_end*2][j++]);
      else st[b_end].push_back(st[b_end*2+1][k++]);

      cout << " st[" << b_end << "][" << i << "]: " << st[b_end][i] << "; ";
    }
    cout << "\n";
    build(b_end - 1);
  }

};

void flatten(ll v, ll level) {
  cout << "Flattening at vertex " << v << "\n";
  visited[v] = true;
  ranges[v][0] = c;
  cout << "Range starter of " << v << " is " << c <<  "\n";
  cout << "flat[" << c << " ] is = " << level << "\n";
  ll i, sz = adj[v].size();
  flat[c++] = level;
  for(i = 0; i < sz; i++) {
    if(!visited[adj[v][i]])
      flatten(adj[v][i], level+1);
  }
  ranges[v][1] = c;
  cout << "Range ender of " << v << " is " << c << "\n";
  cout << "flat[" << c << " ] is = " << level << "\n";
  flat[c++] = level;
}

int main() {
  ll N, Q, i, u, v, d;
  cin >> N >> Q;

  for(i = 0; i < N-1; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  flatten(1, 0);

  vector<vector<ll>> inp;
  inp.resize(2*N);
  for(i = 1; i <= 2*N; i++) {
    cout << "to inp[" << (i-1) << "] pushing " << flat[i] << "\n";
    inp[i-1].push_back(flat[i]);
  }

  SegTree<vector<ll>> stree = SegTree<vector<ll>>(2*N);
  stree.insert(inp);
  cout << "done building segtree\n";

  for(i = 0; i < Q; i++) {
    cin >> v >> d;
    cout << "For vertex " << v << ", querying within range " << ranges[v][0] << " and " << ranges[v][1]+1 << "\n";
    cout << stree.query(ranges[v][0], ranges[v][1]+1, flat[ranges[v][0]]+d)/2 << "\n";
  }

}
