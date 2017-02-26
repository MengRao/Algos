#include <vector>
#include <stack>
#include <iostream>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)(n);++i)
template<typename T1, typename T2> void Min(T1& a, T2 b) { a = min(a, (T1)b); }

const int N = 100;

vector<ll> g[N];
ll id[N], pid[N], curid;
stack<ll> st;
bool inst[N];

void dfs(ll i) {
  id[i] = pid[i] = ++curid;
  st.push(i);
  inst[i] = 1;
  for (auto e : g[i]) {
    if (!id[e])
      dfs(e);
    if (inst[e]) // i and e are in the same SCC that has yet finalized
      Min(pid[i], pid[e]);
    //else finalized SCC pid[e] has incoming edge i
  }
  if (id[i] == pid[i]) {
    // now finalize SCC using i as pid
    while (1) {
      ll t = st.top();
      st.pop();
      inst[t] = 0;
      // identify same SCC using idx of least id in the SCC as pid for later use
      pid[t] = i;
      if (t == i) break;
    }
  }
}

// for directed graph
void solve() {
  ll n, m;
  cin >> n >> m;
  rep(i, n) {
    g[i].clear();
    id[i] = 0;
  }
  while (m--) {
    ll a, b;
    cin >> a >> b;
    g[a].push_back(b);
  }
  ll nscc = 0;
  rep(i, n) {
    if (!id[i]) dfs(i);
    nscc += (i == pid[i]);
  }
  
}