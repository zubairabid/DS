#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

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

  void modify(ll pos, T val) { // Assume 1 indexing and commutative for this problem.
    for(st[pos = eNum + pos - 1] = val; pos > 1; pos = pos / 2)
      st[pos / 2] = st[pos] + st[pos ^ 1];
  }

  T query(ll r1, ll r2) { // Assume 1 indexing for this problem, [) format
    T res = 0;
    for(r1 = r1 + eNum - 1, r2 = r2 + eNum - 1; r1 < r2; r1 = r1/2, r2 = r2/2) {
      if(r1 % 2 == 1) res += st[r1++];
      if(r2 % 2 == 1) res += st[--r2];
    }
    return res;
  }

  void pprint() {
    typename vector<T>::iterator i;
    for(i = st.begin(); i != st.end(); i++) cout << *i << " ";
    cout << "\n";
  }

private:
  vector<T> st;
  ll eNum;

  void build(ll b_end) {
    if(b_end == 0) return;
    st[b_end] = st[b_end * 2] + st[b_end * 2 + 1];
    build(b_end - 1);
  }
};

int main() {
  ll N, i, j;

  cin >> N;
  vector<ll> input;
  input.resize(N);
  for(i = 0; i < N; i++) {
    cin >> input[i];
  }
  SegTree<ll> elem = SegTree<ll>(N);
  elem.insert(input);
  elem.pprint();
  elem.modify(4, 12);
  elem.pprint();
  cout << elem.query(1, 8) << "\n";
  cout << elem.query(1, 7) << "\n";
  cout << elem.query(1, 3) << "\n";
  cout << elem.query(7, 8) << "\n";
  cout << elem.query(2, 4) << "\n";
}
