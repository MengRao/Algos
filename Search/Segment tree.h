/**
* Segment tree with lazy propagation. Building tree takes O(n) time, range query and range update takes O(logn).
* It's a general template implementation that supports various operations on node combination(min, max, add, multiply...)
* and various update fashion. You have to customize combine() and add() function appropriately.
*/


template<typename T, typename AD>
struct ST{
  vector<T> st;
  vector<AD> lazy;
  int n;

  static T combine(T a, T b) {
    return a + b;
  }

  void add(int i, int sz, AD change) {
    // update st[i]
    if(change==1) st[i] = sz;
    else if(change==2) st[i] = 0;
    else st[i] = sz - st[i];

    if(sz > 1) { // update lazy[i]
      if (change == 1 || change == 2)
        lazy[i] = change;
      else {
        lazy[i] = 3 - lazy[i];
      }
    }
  }

  void init(int _n) { // init all to default value
    n = _n;
    int sz = 1;
    while(sz < n) sz <<= 1;
    st.assign(sz << 1, T());
    lazy.assign(sz, AD());
  }

  void init(T* a, int _n) {
    init(_n);
    _build(1, 0, n-1, a);
  }

  void _build(int i, int l, int r, T* a) {
    if(l == r) {
      st[i] = a[l];
      return;
    }
    int m = l + r >> 1;
    _build(i << 1, l, m, a);
    _build(i << 1 | 1, m+1, r, a);
    st[i] = combine(st[i << 1], st[i << 1 | 1]);
  }

  void _push(int i, int l, int m, int r) { // l != r
    if(!lazy[i]) return;
    add(i << 1, m - l + 1, lazy[i]);
    add(i << 1 | 1, r - m, lazy[i]);
    lazy[i] = T();
  }

  T query(int a, int b) {
    return _query(1, 0, n-1, a, b);
  }

  T _query(int i, int l, int r, int a, int b) {
    if(b < l || a > r) return T();
    if(l >=a && r <= b) return st[i];
    int m = l + r >> 1;
    _push(i, l, m, r);
    return combine(_query(i << 1, l, m, a, b), _query(i << 1 | 1, m+1, r, a, b));
  }

  void update(int a, int b, AD change) {
    _update(1, 0, n-1, a, b, change);
  }

  void _update(int i, int l, int r, int a, int b, AD change) {
    if(l >= a && r <= b) {
      add(i, r - l + 1, change);
      return;
    }
    int m = l + r >> 1;
    _push(i, l, m, r);
    if(a <= m) _update(i << 1, l, m, a, b, change);
    if(b > m) _update(i << 1 | 1, m+1, r, a, b, change);
    st[i] = combine(st[i << 1], st[i << 1 | 1]);
  }

};
