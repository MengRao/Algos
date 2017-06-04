#include <iostream>
#include <utility>
#include <cassert>
#include <map>


using namespace std;
typedef unsigned long long ull;
typedef unsigned int uint;

template<uint N>
struct RingBuf {
  ull buf[N];
  uint i = 0;
  uint j = 0;

  bool push(uint val) {
    bool ret = empty();
    buf[j] = val;
    j = (j + 1) % N;
    assert(!empty());
    return ret;
  }

  uint front() { return buf[i]; }

  void pop() {
    i = (i + 1) % N;
  }

  bool empty() { return i == j; }
};

template<uint N, ull inf>
struct Heap {
  pair<ull,uint> buf[N+1];
  uint last = 0;

  Heap() { 
    buf[0].first = 0;
    for (uint i = 1; i <= N; i++) buf[i].first = inf;
  }

  void push(pair<ull, uint> p) {
    assert(last < N);
    buf[++last] = p;
    uint cur = last;

    while (buf[cur>>1] > buf[cur]) {
      swap(buf[cur>>1], buf[cur]);
      cur >>= 1;
    }
  }

  pair<ull, uint> top() {
    return buf[1];
  }

  void pop() {
    buf[1] = buf[last];
    buf[last--].first = inf;
    uint cur = 1;
    while ((cur << 1) <= last) {
      uint best = cur;
      if (buf[cur << 1] < buf[best]) best = cur << 1;
      if (buf[(cur << 1) + 1] < buf[best]) best = (cur << 1) + 1;
      if (best == cur) break;
      swap(buf[cur], buf[best]);
      cur = best;
    }
  }

  bool full() { return last == N; }

};

template<typename T>
struct GetID {
  map<T, uint> ids;
  void clear() { ids.clear(); }
  int size() const { return (int)ids.size(); }

  template<typename Type>
  uint get(Type&& x) { return ids.emplace(forward<T>(x), size()).first->second; }
};

template <uint N>
struct Sort {
  static const ull inf = 1e18;
  
  RingBuf<1024> buf[N];
  Heap<N,inf> heap;
  GetID<uint> ids;
  ull last = 0;

  bool recv(uint exch, ull val) {
    exch = ids.get(exch);
    assert(exch < N);
    assert(val < inf);
    if (val == 0) val = inf;
    if (val <= last) return 1;
    if (buf[exch].push(val)) {
      heap.push(make_pair(val, exch));
      while (heap.full() || heap.top().first == last + 1) {
        last = heap.top().first;
        if (last == inf) return 0;
        cout << last << endl;
        while (heap.top().first == last) {
          uint exch = heap.top().second;
          heap.pop();
          buf[exch].pop();
          if (!buf[exch].empty()) heap.push(make_pair(buf[exch].front(), exch));
        }
      }
    }
    return 1;
  }
  
};