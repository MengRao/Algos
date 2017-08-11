/*
An optimized lazy propagation(support non-commutative update) segment tree implementation using only iteration.
It has the same time complexity as its recursive counterpart(check "Segment tree.h"):
building tree in O(n), range query and range update in O(log n).
But it has a much lower constant factor so it's faster than the recursive version, you can test yourself.
In addition, it's more compact in space usage: only N*3 is required including lazy update array.

Usage:
You have to customize combine() and add() function appropriately.

*/


template<typename T, typename AD>
struct ST {
  vector<T> st;
  vector<AD> lazy;
  int n, h;

  static T combine(T a, T b) {
    return max(a, b);
  }

  void add(int i, int sz, AD change) {
    // update st[i]
    st[i] += change;

    if (sz > 1) { // update lazy[i]
      lazy[i] += change;
    }
  }

  int hsb_loc(int n) {
#ifdef WIN32
    unsigned long index;
    _BitScanReverse(&index, n);
    return index;
#else
    return 31 - __builtin_clz(n);
#endif
  }


  void init(int _n) { // init all to default value
    n = _n;
    h = hsb_loc(n) + 1;
    st.assign(n << 1, T());
    lazy.assign(n, AD());
  }

  void init(T* a, int _n) {
    init(_n);
    for (int i = 0; i < n; i++) {
      st[n + i] = a[i];
    }
    for (int i = n - 1; i > 0; i--) {
      st[i] = combine(st[i << 1], st[i << 1 | 1]);
    }
  }

  void push(int p) {
    for (int s = h; s > 0; --s) {
      int i = p >> s;
      if (lazy[i]) {
        add(i << 1, 1 << (s - 1), lazy[i]);
        add(i << 1 | 1, 1 << (s - 1), lazy[i]);
        lazy[i] = AD();
      }
    }
  }

  T query(int l, int r) {
    l += n;
    r += n;
    push(l);
    push(r);
    T ret = T();
    for (; l <= r; l >>= 1, r >>= 1) {
      if (l & 1) ret = combine(ret, st[l++]);
      if (!(r & 1)) ret = combine(ret, st[r--]);
    }
    return ret;
  }

  void update(int l, int r, AD update) {
    l += n;
    r += n;
    push(l);
    push(r);
    int l0 = l, r0 = r;

    for (int k = 1; l <= r; l >>= 1, r >>= 1, k <<= 1) {
      if (l & 1) add(l++, k, update);
      if (!(r & 1)) add(r--, k, update);
    }
    while (!(l0 & 1)) l0 >>= 1;
    for (int i = l0; i > 1; i >>= 1) {
      st[i >> 1] = combine(st[i], st[i ^ 1]);
    }

    while (r0 & 1) r0 >>= 1;
    for (int i = r0; i > 1; i >>= 1) {
      st[i >> 1] = combine(st[i], st[i ^ 1]);
    }
  }
};