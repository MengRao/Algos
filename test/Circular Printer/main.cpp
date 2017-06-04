#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <vector>
#include <string>

using namespace std;
string str;
int char_cnt, thr_cnt, times;
int cur_thr(0), cur_ch(0);
mutex mtx;
vector<condition_variable> cvs;

void func(int id) {
  int cnt = times;
  unique_lock<mutex> lk(mtx);
  while (cnt--) {
    cvs[id].wait(lk, [id] {return cur_thr == id; });
    cout << "Thread" << id + 1 << ": ";
    for (int i = 0; i < char_cnt; i++, cur_ch = (cur_ch + 1) % str.size()) {
      cout << str[cur_ch];
    }
    cout << endl;
    cur_thr = (cur_thr + 1) % thr_cnt;
    cvs[cur_thr].notify_one();
  }

}


int main(int argc, char* argv[]) {
  ios::sync_with_stdio(false); cin.tie(0);

  if (argc != 5) {
    cout << "Usage: " << argv[0] << " <str> <char_cnt> <thr_cnt> <times>" << endl;
    return 1;
  }
  str = argv[1];
  char_cnt = stoi(argv[2]);
  thr_cnt = stoi(argv[3]);
  times = stoi(argv[4]);

  vector<thread> threads;
  vector<condition_variable> tmp_cvs(thr_cnt);
  cvs.swap(tmp_cvs);
  for (int i = 0; i < thr_cnt; i++) {
    threads.push_back(thread(func, i));
  }

  for (int i = 0; i < thr_cnt; i++) {
    threads[i].join();
  }

  return 0;

}