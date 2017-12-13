struct SQRT {
  typedef int T;
  typedef int RES;
  static constexpr RES defaultRES = 0; // make sure combine(defaultRES, x) == x
  static inline RES combine(RES a, RES b){
    return a + b;
  }

  struct BLK{
    int n;
    T* a;

    void init(int n_, T* a_){ // whether values in a_ are set depends on how SQRT.init() was called
      n = n_;
      a = a_;
    }

    // called before partial update and query
    void push(){
      // rep(i, n){
      //   auto& x = a[i];
      // }
    }

    // called after paritial update
    void pull(){
      // rep(i, n){
      //   auto& x = a[i];
      // }
    }

    void update(T& x, const T& ad){

    }

    void update(const T& ad){
      
    }

    RES query(T& x){

    }

    RES query(){

    }
  };

  //above should be customized
  int B;
  T* a;
  unique_ptr<T[]> _a;
  unique_ptr<BLK[]> blk;
  
  void init(int n, T* a_ = 0){
    B = sqrt(n);
    int NB = (n + B - 1) / B;
    if(a_) a = a_;
    else{
      _a.reset(new T[n]);
      a = _a.get();
    }
    blk.reset(new BLK[NB]);
    rep(i,NB)blk[i].init(min(B,n-i*B+1), &a[i*B]);
  }

  void update(int l, int r, const T& ad) {
    int bl = l / B, br = r / B;
    l %= B, r %= B;
    auto& b1 = blk[bl];
    if (bl == br) {
      b1.push();
      FOR(i, l, r) b1.update(b1.a[i], ad);
      b1.pull();
    }
    else {
      b1.push();
      FOR(i, l, B - 1) b1.update(b1.a[i], ad);
      b1.pull();
      FOR(b, bl + 1, br - 1) blk[b].update(ad);
      auto& b2 = blk[br];
      b2.push();
      FOR(i, 0, r) b2.update(b2.a[i], ad);
      b2.pull();
    }
  }

  RES query(int l, int r) {
    int bl = l / B, br = r / B;
    l %= B, r %= B;
    RES ans = defaultRES;
    auto& b1 = blk[bl];
    if (bl == br) {
      b1.push();
      FOR(i, l, r) ans = combine(ans, b1.query(b1.a[i]));
    }
    else {
      b1.push();
      FOR(i, l, B - 1) ans = combine(ans, b1.query(b1.a[i]));
      FOR(b, bl + 1, br - 1) ans = combine(ans, blk[b].query());
      auto& b2 = blk[br];
      b2.push();
      FOR(i, 0, r) ans = combine(ans, b2.query(b2.a[i]));
    }
    return ans;
  }
};
