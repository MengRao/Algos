ll n, a, b;

ll f(ll x) {
  return (a*x%n*x + b) % n;
}

// a cycle start at index mu with length lam
// time complexity is O(mu + lam) * O(f)
void solve() {
  // assume initial value is 0
  ll slow = 0, fast = f(0);
  ll power = 1, lam = 1;
  while (slow != fast) {
    if (power == lam) {
      slow = fast;
      power <<= 1;
      lam = 0;
    }
    fast = f(fast);
    lam++;
  }
  // now we got lam

  ll mu = 0;
  slow = fast = 0;
  rep(i, lam) fast = f(fast);
  while (slow != fast) {
    slow = f(slow);
    fast = f(fast);
    mu++;
  }
  // now we got mu


}