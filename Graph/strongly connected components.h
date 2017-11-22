#include <vector>
#include <stack>
#include <iostream>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)(n);++i)
template<typename T1, typename T2> void Min(T1& a, T2 b) { a = min(a, (T1)b); }

const int N = 100;

vector<int> g[N];
int id[N], pid[N], curid;
stack<int> st;
bool inst[N];

void scc(int i) {
  id[i] = pid[i] = ++curid;
  st.push(i);
  inst[i] = 1;
  for (auto e : g[i]) {
    if (!id[e]) scc(e);
    if (inst[e]) Min(pid[i], pid[e]);
    //else finalized SCC pid[e] has incoming edge i
  }
  if (id[i] == pid[i]) {
    // now finalize SCC using i as pid
    while (1) {
      auto t = st.top(); st.pop();
      inst[t] = 0;
      pid[t] = i;
      if (t == i) break;
    }
  }
}

// for directed graph
void solve() {
  int n, m, x, y;
  cin >> n >> m;
  while (m--) {
    cin >> x >> y;
    g[x].push_back(y);
  }
  int nscc = 0;
  rep(i, n) {
    if (!id[i]) scc(i);
    nscc += (i == pid[i]);
  }
  
}