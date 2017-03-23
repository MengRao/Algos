
const int N = 1000;

// undirected graph
vector<int> g[N];
int n;

// vertex_connectivity runs in O(V^(1/2) * E^2).
// on graph where vertexes have capacity 1, Dinic's runs in O(V^(1/2) * E)
// it can be shown that when the number of processed vertexes k exceeds current result c', we've got the final result c(i.e. c' = c),
// that is, we need to process at most c+1 vertexes, because c' >= c and k > c' => k > c
// , so we have processed at least one vertex out of the minimum cut set, then we're done.
// and it's easy to show c <= 2E/V, because c <= min degree of vertex, and sum of degree of all vertexes is 2E,
// so avg degree is 2E/V >= min degree, so c <= 2E/V.
// thus we have to run max flow at most (2E/V + 1) * (V-1) = O(E) times, 
int vertex_connectivity() {
  MaxFlow mf(n*2);
  rep(i,n) {
    mf.add(i*2,i*2+1,1,-1); // vertex capacity 1
    for(auto e:g[i]) mf.add(i*2+1,e*2,1);
  }
  int ans = n-1;
  rep(i,n) {
    bool cand[N];
    rep(j,n)cand[j]=1;
    cand[i]=0;
    for(auto e:g[i])cand[e]=0;
    rep(j,n) if(cand[j]) {
      rep(k,mf.m) mf.cap[k] = !(k&1); // clear flow
      Min(ans, mf.maxFlow(i,j));
    }
    if(i>=ans)break;
  }
  return ans;
}

// edge_connectivity runs in O(VE * min(V^(2/3), E^(1/2)))
// on graph where edges have capacity 1, Dinic's runs in O(E * min(V^(2/3), E^(1/2)))
// we have to run max flow O(V) times
int edge_connectivity(){
  MaxFlow mf(n);
  rep(i,n){
    for(auto e:g[i])if(e<i)mf.add(i,e,1,1);
  }
  int ans = n-1;
  FOR(i,1,n-1){
    rep(k,mf.m) mf.cap[k] = 1; // clear flow
    Min(ans,mf.maxFlow(0,i);
  }
  return ans;
}
