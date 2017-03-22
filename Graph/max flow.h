// An implementation of Dinic's algorithm
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)(n);++i)
#define FOR(i,b,e) for(ll i=b;i<=(ll)(e);++i)
#define FORR(i,b,e) for(ll i=b;i>=(ll)(e);--i)
#define Fill(a,b) memset(a,b,sizeof(a))
#define all(a) a.begin(),a.end()
template<typename T1, typename T2> void Max(T1& a, T2 b) { a = max(a, (T1)b); }
template<typename T1, typename T2> void Min(T1& a, T2 b) { a = min(a, (T1)b); }

struct MaxFlow {
  static const int N = 100; // num of vertices
  static const int M = 1000; // num of edges
  static const int inf = 1e9;

  int last[N], used[N], level[N];
  int q[N], qi, qj;
  int cap[M * 2], to[M * 2], prev[M * 2];
  int n, m, s, t;

  MaxFlow(int _n, int _s, int _t) : n(_n), m(0), s(_s), t(_t) {
    rep(i, n) last[i] = -1;
  }

  // c2: capacity on edge y->x,
  // if edge y->x should never be used(e.g: to source or from sink),
  // then speed up algo by removing it from the graph
  void add(int x, int y, int c, int c2 = 0) {
    cap[m] = c; to[m] = y; prev[m] = last[x]; last[x] = m; m++;
    cap[m] = c2;
    if (x != s && y != t) {
      to[m] = x; prev[m] = last[y]; last[y] = m;
    }
    m++;
  }

  bool bfs() {
    rep(i, n) level[i] = -1;
    qi = qj = 0;
    level[s] = 0;
    q[qj++] = s;
    while (qi < qj) {
      int cur = q[qi++];
      int next_level = level[cur] + 1;
      for (int i = last[cur]; i >= 0; i = prev[i]) if (level[to[i]] == -1 && cap[i]) {
        level[to[i]] = next_level;
        if (to[i] == t) return 1;
        q[qj++] = to[i];
      }
    }
    return 0;
  }

  int dfs(int v, int maxf) {
    if (v == t) return maxf;
    int f = 0;
    for (int i = used[v]; i >= 0; used[v] = i = prev[i]) if (level[to[i]] > level[v] && cap[i]) {
      int ret = dfs(to[i], min(maxf - f, cap[i]));
      cap[i] -= ret;
      cap[i ^ 1] += ret;
      if ((f += ret) == maxf) break;
    }
    return f;
  }

  int maxFlow() {
    int ans = 0;
    while (bfs()) {
      rep(i, n)used[i] = last[i];
      ans += dfs(s, inf);
    }
    return ans;
  }

};