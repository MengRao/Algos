#define FOR(i,s,e) for(ll i=s;i<=(ll)(e);++i)

template<int MOD>
struct ModInt {
  static const int Mod = MOD;
  unsigned x;
  ModInt() : x(0) { }
  ModInt(signed sig) : x(sig) {  }
  ModInt(signed long long sig) : x(sig)  { }
  int get() const { return (int)x; }
  ModInt power(unsigned p) { ModInt res = 1, a = *this; while (p) { if (p & 1) res *= a; a *= a; p >>= 1; } return res; }

  ModInt &operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
  ModInt &operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
  ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }
  ModInt &operator/=(ModInt that) { return (*this) *= that.power(MOD - 2); }

  ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
  ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
  ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
  ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
};
typedef ModInt<1000000007> mint;

const int N = 100;

// S(n,k): Stirling numbers of the second kind
// number of ways to partition n labelled objects into k nonempty *unlabelled* subsets
mint S2[N+1][N+1];

// k! * S(n,k)
// number of ways to partition n labelled objects into k nonempty *labelled* subsets
mint S2k[N+1][N+1];

void init(){
  S2[0][0] = 1;
  FOR(n,1,N) FOR(k,1,n) S2[n][k] = S2[n-1][k-1] + S2[n-1][k]*k;
  
  S2k[0][0] = 1;
  FOR(n,1,N) FOR(k,1,n) S2k[n][k] = (S2k[n-1][k-1] + S2k[n-1][k])*k;
}
