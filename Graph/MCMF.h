struct MCMF {
  static const int inf = 1e9;
  vector<int> last, cap, cost, to, prev;

  void init(int n){
    last.assign(n,-1);
    cap.clear();
    cost.clear();
    to.clear();
    prev.clear();
  }
  
  void add(int x, int y, int cp, int ct) {
    prev.push_back((last[x]));
    last[x] = cap.size();
    cap.push_back(cp);
    cost.push_back(ct);
    to.push_back(y);

    prev.push_back(last[y]);
    last[y] = cap.size();
    cap.push_back(0);
    cost.push_back(-ct);
    to.push_back(x);
  }

  int solve(int s, int t) {
    int n = last.size();
    vector<int> d(n), pa(n), inq(n, 0);
    queue<int> q;
    int ans = 0;
    while(1){
      fill(all(d), inf);
      d[s] = 0;
      q.push(s);
      inq[s] = 1;
      while(!q.empty()) {
        int cur = q.front(); q.pop();
        inq[cur] = 0;
        for (int i = last[cur]; i >= 0; i = prev[i]) if(cap[i] && Min(d[to[i]], d[cur] + cost[i])) {
          pa[to[i]] = i;
          if(Max(inq[to[i]], 1)) q.push(to[i]);
        }
      }

      if(d[t] == inf) break;
      int f = inf;
      int u = t;
      while(u != s) {
        int e = pa[u];
        Min(f, cap[e]);
        u = to[e^1];
      }
      ans += f * d[t];
      u = t;
      while(u != s) {
        int e = pa[u];
        cap[e] -= f;
        cap[e^1] += f;
        u = to[e^1];
      }

    }
    return ans;
  }
};
