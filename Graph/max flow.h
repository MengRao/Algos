// An implementation of Dinic's algorithm
#include <vector>
using namespace std;


template <typename T>
struct MaxFlow {
  static const T eps = (T) 1e-9;

  vector<int> last, used, d, q, to, prev;
  vector<T> cap;
  int n;

  // _n: number of vertexes
  // m: number of edges
  void init(int _n, int m = 0) {
    n = _n;
    last.assign(n, -1);
    q.resize(n);
    cap.clear();
    to.clear();
    prev.clear();
    if (m>0) {
      cap.reserve(m * 2);
      to.reserve(m * 2);
      prev.reserve(m * 2);
    }
  }

  // c2: capacity on reverse edge y->x,
  // if edge y->x should never be used(e.g: to source or from sink or for vertex capacity),
  // then set c2 to -1 to speed up algo by removing the reverse edge from the graph
  void add(int x, int y, T c, T c2 = 0) {
    prev.push_back(last[x]);
    last[x] = cap.size();
    cap.push_back(c);
    to.push_back(y);

    prev.push_back(last[y]);
    if (c2 >= 0) last[y] = cap.size();
    else c2 = 0; // make it easier to clear flow
    cap.push_back(c2);
    to.push_back(x);
  }

  bool bfs(int s, int t) {
    d.assign(n, -1);
    int qi = 0, qj = 1;
    q[0] = s;
    d[s] = 0;
    while (qi < qj) {
      int cur = q[qi++];
      int dis = d[cur] + 1;
      for (int i = last[cur]; i >= 0; i = prev[i]) if (d[to[i]] == -1 && cap[i] > eps) {
        d[to[i]] = dis;
        if (to[i] == t) return 1;
        q[qj++] = to[i];
      }
    }
    return 0;
  }

  T dfs(int v, int t, T maxf) {
    if (v == t) return maxf;
    T f = 0;
    for (int& i = used[v]; i >= 0; i = prev[i]) if (d[to[i]] > d[v] && cap[i] > eps) {
      T ret = dfs(to[i], t, min(maxf - f, cap[i]));
      cap[i] -= ret;
      cap[i ^ 1] += ret;
      if ((f += ret) == maxf) break;
    }
    return f;
  }

  T maxFlow(int s, int t) {
    T ans = 0;
    while (bfs(s, t)) {
      used = last;
      ans += dfs(s, t, numeric_limits<T>::max());
    }
    return ans;
  }

};
MaxFlow<int> mf;
