// maximum bipartite match, time complexity: O(E*min(M,N))
//


#include <vector>
using namespace std;


struct MBM {
  vector<vector<int>> g; // size nleft
  vector<int> matchR, Rvisited; // size nright
  int time;

  void init(int nleft, int nright) {
    time = 0;
    g.assign(nleft, vector<int>());
    matchR.assign(nright, -1);
    Rvisited.assign(nright, 0);
  }

  void add(int left, int right) {
    g[left].push_back(right);
  }

  bool dfs(int i)
  {
    for (auto el : g[i])
    {
      if (Rvisited[el] == time)
        continue;
      Rvisited[el] = time;
      if (matchR[el] < 0 || dfs(matchR[el]))
      {
        matchR[el] = i;
        return 1;
      }
    }
    return 0;
  }

  int solve() {
    int res = 0;
    int n = g.size();
    for (int i = 0; i < n; i++) {
      time++;
      res += dfs(i);
    }
    return res;
  }
};
