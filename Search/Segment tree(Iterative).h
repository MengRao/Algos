/*
An optimized lazy propagation(support non-commutative update) segment tree implementation using only iteration.
It has the same time complexity as its recursive counterpart(check "Segment tree.h"):
building tree in O(n), range query and range update in O(log n).
But it has a much lower constant factor so it's faster than the recursive version, you can test yourself.
In addition, it's more compact in space usage: only N*3 is required including lazy update array, compared with N*8 for recursive version.
Lastly, the user interface is improved in this version.
So this version can completely replace the recursive one, hurray!

Usage:
1) Change implementation of struct STUpdate and STNode, keeping interface the same.
2) Set N(max possible segment size) and n(segment size in current test case) appropriately.
3) Initialize st[n...2n-1] with initial values.
4) Call build_tree(), and clear_update() if needed(or just memset(lazy, 0, sizeof(STUpdate)*n) if suitable for clearing updates)
5) Call query_tree() and update_tree() as requested

*/


struct STUpdate
{
  // default constructed STUpdate must be converted to false
  STUpdate()
    : change(0)
  {
  }

  STUpdate(char ch)
    : change(ch)
  {
  }
  // if has pending update
  operator bool()
  {
    return change != 0;
  }

  void add(const STUpdate& update) {
    if (update.change == 1 || update.change == 2)
      change = update.change;
    else {
      change = 3 - change;
    }
  }
  char change; // 0: no change, 1: set to 1, 2: set to 0, 3: toggle
};

struct STNode
{
  // default node indicates an empty result
  STNode()
    : v(0)
  {
  }

  void combine(const STNode& a) {
    v += a.v;
  }

  void applyUpdate(int rangesize, const STUpdate& update) {
    if (update.change == 1)
      v = rangesize;
    else if (update.change == 2)
      v = 0;
    else
      v = rangesize - v;
  }

  int v;
};


const int N = 1024000;
STNode st[N * 2];
STUpdate lazy[N];

int n;
int height;

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


/**
* Build the tree
*/
void build_tree() {
  height = hsb_loc(n) + 1;
  for (int i = n - 1; i > 0; i--) {
    st[i] = st[i << 1];
    st[i].combine(st[i << 1 | 1]);
  }

}

void clear_update() {
  for (int i = 1; i < n; i++) {
    lazy[i] = STUpdate();
  }

}

void push(int p) {
  for (int s = height, k = 1 << (height - 1); s > 1; --s, k >>= 1) {
    int i = p >> s;
    if (lazy[i]) {
      lazy[i << 1].add(lazy[i]);
      st[i << 1].applyUpdate(k, lazy[i]);
      lazy[i << 1 | 1].add(lazy[i]);
      st[i << 1 | 1].applyUpdate(k, lazy[i]);
      lazy[i] = STUpdate();
    }
  }
  int i = p >> 1;
  if (lazy[i]) {
    st[i << 1].applyUpdate(1, lazy[i]);
    st[i << 1 | 1].applyUpdate(1, lazy[i]);
    lazy[i] = STUpdate();
  }
}

/**
* Query tree, 0 <= l <= r < n
*/
STNode query_tree(int l, int r) {
  l += n;
  r += n;
  push(l);
  push(r);
  STNode ret;
  for (; l <= r; l >>= 1, r >>= 1) {
    if (l & 1) {
      ret.combine(st[l++]);
    }
    if (!(r & 1)) {
      ret.combine(st[r--]);
    }
  }
  return ret;
}

/**
* Update tree, 0 <= l <= r < n
*/
void update_tree(int l, int r, const STUpdate& update) {
  l += n;
  r += n;
  push(l);
  push(r);
  int l0 = l, r0 = r;
  if (l & 1) {
    st[l++].applyUpdate(1, update);
  }
  if (!(r & 1)) {
    st[r--].applyUpdate(1, update);
  }
  l >>= 1;
  r >>= 1;
  for (int k = 2; l <= r; l >>= 1, r >>= 1, k <<= 1) {
    if (l & 1) {
      st[l].applyUpdate(k, update);
      lazy[l++].add(update);
    }
    if (!(r & 1)) {
      st[r].applyUpdate(k, update);
      lazy[r--].add(update);
    }
  }
  while (!(l0 & 1))
    l0 >>= 1;
  while (l0 > 1) {
    l0 >>= 1;
    st[l0] = st[l0 << 1];
    st[l0].combine(st[l0 << 1 | 1]);
  }

  while (r0 & 1)
    r0 >>= 1;
  while (r0 > 1) {
    r0 >>= 1;
    st[r0] = st[r0 << 1];
    st[r0].combine(st[r0 << 1 | 1]);
  }
}