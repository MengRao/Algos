#include <vector>
#include <iostream>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)(n);++i)
template<typename T1, typename T2> void Min(T1& a, T2 b) { a = min(a, (T1)b); }

const int N = 100;

vector<ll> g[N];
ll id[N], pid[N], curid;
bool art[N];

void dfs(ll i, ll p) {
  id[i] = pid[i] = ++curid;
  ll rootcnt = 0;
  for (auto e : g[i]) if (e != p) {
    if (!id[e]) {
      dfs(e, i);
      if (p < 0) // root node
        art[i] = ++rootcnt > 1;
      else {
        // if pid[e] > curid, edge (i,e) is a bridge
        if (pid[e] >= id[i])
          art[i] = 1;
        else Min(pid[i], pid[e]);
      }

    }
    else {
      Min(pid[i], id[e]);
    }
  }
}

// for undirected graph
void solve() {
  ll n;
  cin >> n;
  rep(i, n) {
    g[i].clear();
    id[i] = art[i] = 0;
  }
  // add edges
  while (1) {
    ll i, j;
    cin >> i;
    if (!i)break;
    i--;
    while (1) {
      if (cin.get() == '\n')break;
      cin >> j;
      j--;
      g[i].push_back(j);
      g[j].push_back(i);
    }
  }

  ll cnt = 0; // cnt of articulations
  rep(i, n) {
    if (!id[i]) dfs(i, -1);
    cnt += art[i];
  }
  cout << cnt << endl;
}