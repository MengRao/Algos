#ifdef WIN32
int hsb_loc(int n) {
  unsigned long index;
  _BitScanReverse(&index, n);
  return index;
}

int hsb_loc(long long n) {
  unsigned long index;
  _BitScanReverse64(&index, n);
  return index;
}
#else
int hsb_loc(int n) {
  return 31 - __builtin_clz(n);
}

int hsb_loc(long long n) {
  return 63 - __builtin_clzll(n);
}
#endif

// get highest set bit of n, undefined if n is 0
int hsb(int n) {
  int loc = hsb_loc(n);
  return 1 << loc;
}

long long hsb(long long n) {
  int loc = hsb_loc(n);
  return 1LL << loc;
}