
struct KMP {
  string t, p;
  vector<int> b;

  void prep() {
    int m = p.size();
    b.resize(m + 1);
    int i = 0, j = -1;
    b[0] = -1;
    while (i < m) {
      while (j >= 0 && p[i] != p[j]) j = b[j];
      i++; j++;
      b[i] = j;
    }
  }

  // return max length of suffix of *t* matching prefix of *p*
  int search() {
    prep();
    int i = 0, j = 0;
    while (i < t.size()) {
      while (j >= 0 && t[i] != p[j]) j = b[j];
      i++; j++;
      /*if (j == p.size()) {
      cout << "found at pos " << i - j << endl;
      j = b[j];
      }*/
    }
    return j;
  }
};