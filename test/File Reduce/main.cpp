#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void dfs(vector<int>& vec, const vector<vector<int>>& ch, int i) {
  vec.push_back(i);
  for (int e : ch[i]) dfs(vec, ch, e);
}

int X;

bool add(vector<int>&& data, vector<vector<int>>& ans) {
  if (ans.back().size() >= X) {
    ans.push_back(move(data));
  }
  else ans.back().insert(ans.back().end(), data.begin(), data.end());

  return ans.back().size() >= X;
}


int main(int argc, char* argv[]) {
  ios::sync_with_stdio(false); cin.tie(0);

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <X>" << endl;
    return 1;
  }
  X = stoi(argv[1]);
  if (X <= 0) {
    cout << "X should be positive" << endl;
    return 1;
  }
  map<int, int> ids;
  vector<string> lines;
  vector<int> pids;

  string line;
  while (getline(cin, line)) {
    int id, pid;
    auto pos = line.rfind(',');
    pid = stoi(line.substr(pos + 1));
    auto pos2 = line.rfind(',', pos - 1);
    id = stoi(line.substr(pos2 + 1, pos - pos2 - 1));
    ids[id] = lines.size();
    if (line[0] != 'P') pid = 0;
    lines.push_back(move(line));
    pids.push_back(pid);
  }

  int n = lines.size();
  if (n < X) {
    cout << "X is less than the num of records: " << n << endl;
    return 1;
  }
  vector<vector<int>> ch(n);
  for (int i = 0; i < n; i++) if (pids[i]) {
    int pid = ids[pids[i]];
    ch[pid].push_back(i);
  }
  vector<vector<int>> data, ans(1);
  for (int i = 0; i < n; i++) if (pids[i] == 0) {
    data.push_back(vector<int>());
    dfs(data.back(), ch, i);
  }

  int m = data.size();
  sort(data.begin(), data.end(),
    [](const vector<int>& a, const vector<int>& b) -> bool
  {
    return a.size() > b.size();
  });

  // http://www.menet.umn.edu/~zhangs/Reports/1999_CFLZ.pdf

  int xi = m, xj, yi = m, yj, zi = m, zj;
  int X1 = (X + 1) / 2;
  int X2 = (X + 2) / 3;
  for (int i = 0; i < m; i++) {
    int sz = data[i].size();
    if (sz >= X) add(move(data[i]), ans);
    else { // sz < X
      if (xi == m) xi = i;
      if (sz < X1) {
        if (yi == m) yi = i;
        if (sz < X2) {
          if (zi == m) zi = i;
        }
      }
    }
  }
  xj = yi;
  yj = zi;
  zj = m;

  while (1) {
    if ((xi == xj&&yi == yj) || zi == zj) break;
    int sumx = 0, sumy = 0;
    if (xi != xj) sumx = data[xi].size();
    if (yi != yj) {
      sumy += data[yi].size();
      if (yi + 1 != yj) sumy += data[yi + 1].size();
    }
    if (sumx >= sumy) {
      add(move(data[xi++]), ans);
    }
    else {
      add(move(data[yi++]), ans);
      if (yi != yj) add(move(data[yi++]), ans);
    }

    while (zi != zj && !add(move(data[--zj]), ans))
      ;
  }
  while (zi != zj) add(move(data[zi++]), ans);
  while (yi != yj) add(move(data[yi++]), ans);
  while (xi != xj) add(move(data[xi++]), ans);

  if (ans.back().size() < X) {
    ans.front().insert(ans.front().end(), ans.back().begin(), ans.back().end());
    ans.pop_back();
  }

  for (int i = 0; i < ans.size(); i++) {
    string filename = "output_" + to_string(i + 1) + ".txt";
    ofstream fs(filename);
    for (auto id : ans[i]) {
      fs << lines[id] << endl;
    }
  }

  return 0;
}