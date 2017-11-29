typedef ModInt<1000000007> mint; // refer to ModInt.h

struct Combo {
    vector<mint> fac, invf;
    
    Combo(int N): fac(N+1), invf(N+1) {
      fac[0] = 1;
      FOR(i,1,N) fac[i] = fac[i-1] * i;
      invf[N] = (mint)1 / fac[N];
      FORR(i,N,1)invf[i-1] = invf[i] * i;
    }
    // 0 < i <= N
    mint inv(int i){
      return fac[i-1] * invf[i];
    }
    // 0 <= k <= n <= N
    mint comb(int n, int k) {
      return fac[n] * invf[k] * invf[n-k];
    }
};
Combo C(1000000);
