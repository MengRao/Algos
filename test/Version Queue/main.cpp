
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
typedef unsigned int uint;

class VersionQueue {
  vector<uint> buf, version;
  uint i;

public:
  VersionQueue() : i(0), version(1, 0) {}

  void enqueue(uint v) {
    buf.push_back(v);
    version.push_back(i);
  }

  uint dequeue() {
    assert(i < buf.size());
    uint ret = buf[i++];
    version.push_back(i);
    return ret;
  }

  void print(uint ver) {
    assert(ver < version.size());
    uint i = version[ver];
    uint j = ver - i;
    while (i < j) {
      cout << buf[i++] << ' ';
    }
    cout << endl;
  }
};

int main(void) {
  ios::sync_with_stdio(false);

  VersionQueue q;
  int n;
  cin >> n;
  while (n--) {
    char ch;
    uint v;
    cin >> ch;
    if (ch == 'e') {
      cin >> v;
      q.enqueue(v);
    }
    else if (ch == 'd') {
      q.dequeue();
    }
    else { //ch == 'p'
      cin >> v;
      q.print(v);
    }
  }
}