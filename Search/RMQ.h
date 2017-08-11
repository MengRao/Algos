#ifdef WIN32
int hsb_loc(int n) {
  unsigned long index;
  _BitScanReverse(&index, n);
  return index;
}
#else
int hsb_loc(int n) {
  return 31 - __builtin_clz(n);
}
#endif

template<class T> struct RMQ {
  int n;
  vector<T> d;

  RMQ() : n(0) {}
  template<class Iter> RMQ(Iter begin, Iter end) : n(0) { build(begin, end); }

  template<class Iter> void build(Iter begin, Iter end) { // random access iterator
    n = end - begin;
    if (n == 0) return;
    int g = hsb_loc(n);
    d.resize(n*(g + 1));
    g *= n;
    rep(i, n) { d[i] = *begin; ++begin; }
    for (int t = 1, b = 0; b < g; t <<= 1, b += n) {
      for (int i = 0, j = t; j <= n - t; i++, j++) {
        d[b + n + i] = min(d[b + i], d[b + j]);
      }
    }
  }

  const T rmq(int l, int r) const { // in range [l..r)
    int g = hsb_loc(r - l), b = n * g;
    r -= 1 << g;
    return min(d[b + l], d[b + r]);
  }

};
