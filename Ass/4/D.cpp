#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll MOD = 1000000007;

template <typename T>
class SegTree {
public:
  SegTree(ll tSize) {
    this->eNum = tSize;
    st.resize(2*tSize);
  }

  void insert(vector<T> data) {
    copy_backward(data.begin(), data.end(), st.end());
    build(eNum-1);
  }

  ll query(ll l, ll r, ll x) { // Assume 1 indexing for this problem, [) format
    ll res = 0;
    for(l = l + eNum - 1, r = r + eNum - 1; l < r; l = l/2, r = r/2) {
      if(l % 2 == 1) {
        res += (upper_bound(st[l].begin(), st[l].end(), x) - st[l].begin());
        l++;
      }
      if(r % 2 == 1) {
        r--;
        res += (upper_bound(st[r].begin(), st[r].end(), x) - st[r].begin());
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
    }
    build(b_end - 1);
  }

};

int main() {
  ll N, i, q, temp, l, r, x;
  vector<vector<ll>> inp;

  cin >> N;
  inp.resize(N);

  for(i = 0; i < N; i++) {
    cin >> temp;
    inp[i].push_back(temp);
  }

  SegTree<vector<ll>> stree = SegTree<vector<ll>>(N);
  stree.insert(inp);

  cin >> q;

  for(i = 1; i <= q; i++) {
    cin >> l >> r >> x;
    cout << stree.query(l, r+1, x) << "\n";
  }

  return 0;
}
