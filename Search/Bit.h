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

#ifdef WIN32
int lsb_loc(int n) {
  unsigned long index;
  _BitScanForward(&index, n);
  return index;
}

int lsb_loc(long long n) {
  unsigned long index;
  _BitScanForward64(&index, n);
  return index;
}
#else
int lsb_loc(int n) {
  return __builtin_ctz(n);
}

int lsb_loc(long long n) {
  return __builtin_ctzll(n);
}
#endif


#ifdef WIN32
int popcnt(int n) {
  return __popcnt(n);
}

int popcnt(long long n) {
  return __popcnt64(n);
}
#else
int popcnt(int n) {
  return __builtin_popcount(n);
}

int popcnt(long long n) {
  return __builtin_popcountll(n);
}
#endif
