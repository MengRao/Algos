template<class T> T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }

//ax + by = gcd(a, b)
template<class T>
T gcd_ext(T a, T b, T& x, T& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  T g = gcd_ext(b, a % b, y, x);
  y -= (a / b) * x;
  return g;
}
