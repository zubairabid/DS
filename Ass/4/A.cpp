// Segment trees

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll MOD = 1000000007;

struct Mtx {
  ll e11, e12, e21, e22;

  void insert(ll a, ll b, ll c, ll d) {
    this->e11 = a;
    this->e12 = b;
    this->e21 = c;
    this->e22 = d;
  }
};

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

  void modify(ll pos, T val) { // Assume 1 indexing for this problem
    pos = eNum + pos - 1;
    for(st[pos] = val; pos > 1; pos = pos / 2)
      if((pos ^ 1) > pos) mult(st[pos / 2], st[pos], st[pos + 1]);
      else mult(st[pos / 2], st[pos - 1], st[pos]);
  }

  T query(ll r1, ll r2) { // Assume 1 indexing for this problem, [) format
    T resl = (T)malloc(sizeof(T));
    T resr = (T)malloc(sizeof(T));
    resl.insert(1, 0, 0, 1);
    resr.insert(1, 0, 0, 1);
    for(r1 = r1 + eNum - 1, r2 = r2 + eNum - 1; r1 < r2; r1 = r1/2, r2 = r2/2) {
      if(r1 % 2 == 1) { T temp = (T)malloc(sizeof(Mtx)); mult(temp, resl, st[r1++]); resl = temp; }
      if(r2 % 2 == 1) { T temp = (T)malloc(sizeof(Mtx)); mult(temp, st[--r2], resr); resr = temp; }
    }
    T temp = (T)malloc(sizeof(T));
    mult(temp, resl, resr);
    return temp;
  }

private:
  vector<T> st;
  ll eNum;

  void build(ll b_end) {
    if(b_end == 0) return;
    if(st[b_end] == NULL) st[b_end] = (T)malloc(sizeof(Mtx));
    mult(st[b_end], st[b_end * 2], st[b_end * 2 + 1]);
    build(b_end - 1);
  }

  T mult(T r, T a, T b) {
    r->e11 = ((a->e11 * b->e11) % MOD + (a->e12 * b->e21) % MOD) % MOD;
    r->e12 = ((a->e11 * b->e12) % MOD + (a->e12 * b->e22) % MOD) % MOD;
    r->e21 = ((a->e21 * b->e11) % MOD + (a->e22 * b->e21) % MOD) % MOD;
    r->e22 = ((a->e21 * b->e12) % MOD + (a->e22 * b->e22) % MOD) % MOD;
    return r;
  }
};

int main() {
  ll N, i, a, b, c, d, q, t, s;

  cin >> N;
  vector<Mtx*> inp;
  inp.resize(N);
  for(i = 0; i < N; i++) {
    cin >> a >> b >> c >> d;
    inp[i] = (Mtx*)malloc(sizeof(Mtx));
    inp[i].insert(a, b, c, d);
  }
  SegTree<Mtx*> stree = SegTree<Mtx*>(N);
  stree.insert(inp);
  cin >> q;
  for(i = 0; i < q; i++) {
    Mtx* elem = (Mtx*)malloc(sizeof(Mtx));
    cin >> t >> s >> a;
    if(t == 1) {
      elem = stree.query(s, a+1);
      cout << elem->e11 << " " << elem->e12 << " " << elem->e21 << " " << elem->e22 << "\n";
    }
    else {
      cin >> b >> c >> d;
      elem->e11 = a;
      elem->e12 = b;
      elem->e21 = c;
      elem->e22 = d;
      stree.modify(s, elem);
    }
  }

  return 0;
}
