template<typename T>
struct Matrix {
  vector<vector<T>> a;

  vector<T>& operator[](int x) { return a[x]; }

  const vector<T>& operator[](int x) const { return a[x]; }

  int row() const { return a.size(); }
  int col() const { return a[0].size(); }

  Matrix(int r, int c) {
    a.resize(r);
    for (auto& e : a) e.resize(c, 0);
  }

  Matrix trans() const {
    Matrix ret(col(), row());
    rep(i, row()) rep(j, col()) ret[j][i] = a[i][j];
    return ret;
  }

  Matrix operator*(const Matrix& rhs) { // col() == rhs.row()
    Matrix ret(row(), rhs.col());
    //rep(i,row()) rep(j,rhs.col()) rep(k,col()) ret[i][j] += a[i][k] * rhs[k][j];
    Matrix b = rhs.trans();
    rep(i, row()) rep(j, b.row()) rep(k, col()) ret[i][j] += a[i][k] * b[j][k];
    return ret;
  }

  Matrix &operator*=(const Matrix& rhs) { return *this = *this * rhs; }

  Matrix pow(long long p) { // row() == col()
    Matrix ret(row(), row());
    rep(i, row()) ret[i][i] = 1;
    Matrix t = *this;
    while (p) {
      if (p & 1) ret *= t;
      t *= t;
      p >>= 1;
    }
    return ret;
  }

};
typedef Matrix<int> Mat;