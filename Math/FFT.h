struct FFT
{
  const double PI = 3.14159265358979;
  typedef complex<double> C;
  vector<int> rev;
  vector<C> w;
  void init(int logn) {
    int n = 1 << logn;
    rev.resize(n);
    w.resize(n + 1);

    for (int i = 0; i < n; i++) {
      rev[i] = 0;
      for (int j = 0; j < logn; j++)
        rev[i] |= (i >> j & 1) << (logn - 1 - j);
      if (rev[i] < i) rev[i] = i;
    }

    w[1] = C(1, 0);
    for (int p = 0; p < logn - 1; p++) {
      double alpha = PI / (n >> (logn - 1 - p));
      C cur(cos(alpha), sin(alpha));
      for (int j = (1 << p); j < (2 << p); j++) {
        w[2 * j] = w[j];
        w[2 * j + 1] = w[j] * cur;
      }
    }
  }

  void fft(vector<C>& a, bool invert) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
      swap(a[i], a[rev[i]]);
      if (invert) a[i].imag(-1 * a[i].imag());
    }
    for (int len = 1; len < n; len <<= 1)
      for (int i = 0; i < n; i += len << 1)
        for (int j = i, k = i + len; j < i + len; j++, k++) {
          C t = a[k] * w[k - i];
          a[k] = a[j] - t;
          a[j] = a[j] + t;
        }
    if (invert) for (int i = 0; i < n; i++) a[i] /= n;
  }

  vector<int> conv(vector<int> A, vector<int> B)
  {
    int n = A.size() + B.size() - 1;
    int N = 1, logn = 0;
    while (N < n) N <<= 1, logn++;
    init(logn);
    vector<C> a(N), b(N);
    for (int i = 0; i < A.size(); i++) a[i].real(A[i]);
    for (int i = 0; i < B.size(); i++) b[i].real(B[i]);
    fft(a, 0);
    fft(b, 0);
    for (int i = 0; i<N; i++) a[i] *= b[i];
    fft(a, 1);
    vector<int> ret(n);
    for (int i = 0; i < n; i++) ret[i] = (int)(a[i].real() + 0.5);

    return ret;
  }
} fft;