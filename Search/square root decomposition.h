

template<int SZ>
struct SQRT {
  static constexpr int sqrt(int n, int i = 1) {
    return n == i ? n : (i * i < n ? sqrt(n, i + 1) : i);
  }
  static constexpr int B = sqrt(SZ);
  static constexpr int NB = (SZ + B - 1) / B;
  typedef int T;
  struct BLK {
    array<T, B> a;

    BLK() {
      rep(i, B) a[i] = 0;
    }
  };
  vector<BLK> blk;

  SQRT():blk(NB) {}
  

  void push(BLK& b) {
    fore(x, b.a) {

    }
  }

  void pull(BLK& b) {
    fore(x, b.a) {

    }
  }

  void update(T& x, const T& ad) {

  }

  void update(BLK& b, const T& ad) {
    
  }

  typedef ll RES;
  static constexpr RES defaultRES = 0;
  RES combine(RES a, RES b) {

  }

  RES query(T& x) {

  }

  RES query(BLK& b) {

  }

  //above should be customized
  void update(int l, int r, const T& ad) {
    int bl = l / B, br = r / B;
    l %= B, r %= B;
    if (bl == br) {
      auto& b = blk[bl];
      push(b);
      FOR(i, l, r)update(b.a[i], ad);
      pull(b);
    }
    else {
      push(blk[bl]);
      push(blk[br]);
      FOR(i, l, B - 1) update(blk[bl].a[i], ad);
      FOR(i, 0, r) update(blk[br].a[i], ad);
      pull(blk[bl]);
      pull(blk[br]);
      FOR(b, bl + 1, br - 1)update(blk[b], ad);
    }
  }

  RES query(int l, int r) {
    int bl = l / B, br = r / B;
    l %= B, r %= B;
    RES ans = defaultRES;
    if (bl == br) {
      auto& b = blk[bl];
      push(b);
      FOR(i, l, r)ans = combine(ans, query(b.a[i]));
    }
    else {
      push(blk[bl]);
      push(blk[br]);
      FOR(i, l, B - 1) ans = combine(ans, query(blk[bl].a[i]));
      FOR(i, 0, r) ans = combine(ans, query(blk[br].a[i]));
      FOR(b, bl + 1, br - 1) ans = combine(ans, query(blk[b]));
    }
    return ans;
  }
};