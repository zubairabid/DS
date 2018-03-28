// Segment trees

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll MOD = 1000000007;

struct Mtx {
  ll e11;
  ll e12;
  ll e21;
  ll e22;
};

template <typename T>
class SegTree {
public:
  SegTree(ll tSize) {
    this->eNum = tSize;
    cout << "Initialised eNum to tSize = " << tSize << "\n";
    st.resize(2*tSize);
    cout << "Resized st to twice tSize\n";
  }

  void insert(vector<T> data) {
    cout << "about to insert data to the last eNum elements of STree\n";
    copy_backward(data.begin(), data.end(), st.end());
    cout << "Building the segment products backwards:\n";
    build(eNum-1);
  }

  void modify(ll pos, T val) { // Assume 1 indexing for this problem
    pos = eNum + pos - 1;
    for(st[pos] = val; pos > 1; pos = pos / 2)
      mult(st[pos / 2], st[pos], st[pos + 1]);
  }

  T query(ll r1, ll r2) { // Assume 1 indexing for this problem, [) format
    T resl = (T)malloc(sizeof(Mtx));
    T resr = (T)malloc(sizeof(Mtx));
    resl->e11 = resr->e11 = resl->e22 = resr->e22 = 1;
    resl->e12 = resl->e21 = resr->e12 = resr->e21 = 0;
    for(r1 = r1 + eNum - 1, r2 = r2 + eNum - 1; r1 < r2; r1 = r1/2, r2 = r2/2) {
      if(r1 % 2 == 1) { T temp = (T)malloc(sizeof(Mtx)); mult(temp, resl, st[r1++]); resl = temp; }
      if(r2 % 2 == 1) { T temp = (T)malloc(sizeof(Mtx)); mult(temp, st[--r2], resr); resr = temp; }
      cout << "r1 : " << r1 << "; r2 : " << r2 << "\n";
    }
    T temp = (T)malloc(sizeof(Mtx));
    mult(temp, resl, resr);
    return temp;
  }

  void pprint() {
    typename vector<T>::iterator i;
    cout << "Segtree is: \n";
    for(i = st.begin() + 1; i != st.end(); i++) cout << *i << " : " << (*i)->e11 << " " << (*i)->e12 << " " << (*i)->e21 << " " << (*i)->e22 << "\n";
    cout << "\n";
  }

private:
  vector<T> st;
  ll eNum;

  void build(ll b_end) {
    if(b_end == 0) return;
    if(st[b_end] == NULL) st[b_end] = (T)malloc(sizeof(Mtx));
    cout << "calling multiply\n";
    mult(st[b_end], st[b_end * 2], st[b_end * 2 + 1]);
    build(b_end - 1);
  }

  T mult(T r, T a, T b) {
    cout << "Multiplying " << a << " ( "<< a->e11 << " " << a->e12 << " " << a->e21 << " " << a->e22 << " ) and " << b << " ( " << b->e11 << " " << b->e12 << " " << b->e21 << " " << b->e22 << " )\n";
    r->e11 = ((a->e11 * b->e11) % MOD + (a->e12 * b->e21) % MOD) % MOD;
    r->e12 = ((a->e11 * b->e12) % MOD + (a->e12 * b->e22) % MOD) % MOD;
    r->e21 = ((a->e21 * b->e11) % MOD + (a->e22 * b->e21) % MOD) % MOD;
    r->e22 = ((a->e21 * b->e12) % MOD + (a->e22 * b->e22) % MOD) % MOD;
    cout << "Result: " << r << " ( " << r->e11 << " " << r->e12 << " " << r->e21 << " " << r->e22 <<" )\n";
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
    inp[i]->e11 = a;
    inp[i]->e12 = b;
    inp[i]->e21 = c;
    inp[i]->e22 = d;
  }
  SegTree<Mtx*> stree = SegTree<Mtx*>(N);
  cout << "created segtree instance, about to insert\n";
  stree.insert(inp);
  cout << "insertion done\n";
  stree.pprint();
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
      stree.pprint();
    }
  }

  return 0;
}
