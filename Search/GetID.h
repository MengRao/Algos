#include <map>
#include <vector>
using namespace std;

// ID start from 0
struct GetID {
  map<string, int> ids;
  void clear() { ids.clear(); }
  int size() const { return (int)ids.size(); }
  int get(string&& x) { return ids.emplace(forward<string>(x), size()).first->second; }
};

// ID start from 0
struct GetID2 {
	map<string, int> ids;
	vector<string> values;
	void clear() { ids.clear(); values.clear(); }
	int size() const { return (int)values.size(); }
	int get(string&& x) {
		auto ret = ids.emplace(forward<string>(x), size());
		if (ret.second)
			values.push_back(ret.first->first);
		return ret.first->second;
	}
	string& getstr(int id) {
		return values[id];
	}
};
