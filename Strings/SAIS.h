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

struct SAIS {
  enum { STYPE, LTYPE };
  vector<int> S, sa, lcp, rank, t, B_old, B;
  int N, A_SIZE;
  RMQ<int> rmq;

  SAIS() {}
  SAIS(const string &str, int A_SIZE_ = 128) : A_SIZE(A_SIZE_) {
    N = str.size() + 1;
    S = vector<int>(N);
    for (int i = 0; i<N; i++) S[i] = str[i];
    buildSA();
    buildLCP();
  }
  SAIS(vector<int>&& S_, int A_SIZE_) : S(S_), A_SIZE(A_SIZE_) {
    buildSA();
  }

  inline bool is_lms(int i) {
    return i>0 && t[i] == STYPE && t[i - 1] == LTYPE;
  }

  void induced_sort(const vector<int>& S1) {
    B = B_old;
    for (int i = S1.size(); i--;) {
      int j = S1[i];
      sa[--B[S[j]]] = j;
    }
    B = B_old;
    for (int i = 0; i<N; i++) {
      int j = sa[i] - 1;
      if (j >= 0 && S[j] >= S[j + 1]) sa[B[S[j] - 1]++] = j;
    }
    B = B_old;
    for (int i = N; i--; ) {
      int j = sa[i] - 1;
      if (j >= 0 && S[j] <= S[j + 1]) sa[--B[S[j]]] = j;
    }
  }

  void buildSA() {
    N = S.size();
    sa.assign(N, -1);
    if (N == 1) {
      sa[0] = 0;
      return;
    }
    t.assign(N, STYPE);
    for (int i = N - 1; i--;)
      if (S[i] > S[i + 1] || (S[i] == S[i + 1] && t[i + 1] == LTYPE))
        t[i] = LTYPE;

    B_old = vector<int>(A_SIZE);
    for (int i = 0; i<N; i++) B_old[S[i]]++;
    for (int i = 0; i<A_SIZE - 1; i++) B_old[i + 1] += B_old[i];

    vector<int> P1;
    for (int i = 0; i < N; i++) if (is_lms(i)) P1.push_back(i);

    induced_sort(P1);

    int N1 = 0;
    for (int i = 0; i<N; i++) if (is_lms(sa[i])) sa[N1++] = sa[i];

    fill(sa.begin() + N1, sa.end(), -1);
    int name = 0, prev = -1;
    for (int i = 0; i<N1; i++) {
      int cur = sa[i];
      bool diff = (prev == -1) || S[cur] != S[prev];
      for (int j = 1; !diff; j++) {
        if (is_lms(cur + j) && is_lms(prev + j)) break;
        if (is_lms(cur + j) || is_lms(prev + j) || S[cur + j] != S[prev + j])
          diff = true;
      }
      if (diff) name++;
      sa[N1 + cur / 2] = name - 1;
      prev = cur;
    }
    vector<int> S1, sa1;
    for (int i = N1; i<N; i++) if (sa[i] >= 0) S1.push_back(sa[i]);

    if (name == N1) {
      sa1.resize(N1);
      for (int i = 0; i < N1; i++) sa1[S1[i]] = i;
    }
    else sa1 = SAIS(move(S1), name).sa;

    for (int i = 0; i<N1; i++) sa1[i] = P1[sa1[i]];
    fill(sa.begin(), sa.end(), -1);
    induced_sort(sa1);
  }

  void buildLCP() {
    rank.resize(N);
    lcp.resize(N - 1);
    for (int i = 0; i<N; i++) rank[sa[i]] = i;
    int h = 0;
    for (int i = 0; i<N - 1; i++) {
      int j = sa[rank[i] - 1];
      if (h>0) h--;
      for (; j + h<N && i + h<N && S[j + h] == S[i + h]; h++);
      lcp[rank[i] - 1] = h;
    }
  }
  
  void buildRMQ() {
    rmq = RMQ<int>(lcp.begin(), lcp.end());
  }

  int get_lcp(int x, int y) {
    if (x == y) return N - 1 - x;
    x = rank[x];
    y = rank[y];
    if (x > y) swap(x, y);
    return rmq.rmq(x, y);
  }

};