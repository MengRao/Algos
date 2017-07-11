#include <map>
#include <vector>
using namespace std;

// ID start from 0
struct GetID {
  map<string, int> ids;
  void clear() { ids.clear(); }
  int size() const { return (int)ids.size(); }
  template<typename T>
  int get(T&& x) { return ids.emplace(forward<T>(x), size()).first->second; }
  template<typename T>
  int find(T&& x) {
    auto it = ids.find(forward<T>(x));
    return it == ids.end() ? -1 : it->second;
  }
};

// ID start from 0
struct GetID2 {
	map<string, int> ids;
	vector<string> values;
	void clear() { ids.clear(); values.clear(); }
	int size() const { return (int)values.size(); }
  template<typename T>
	int get(T&& x) {
		auto ret = ids.emplace(forward<T>(x), size());
		if (ret.second)
			values.push_back(ret.first->first);
		return ret.first->second;
	}
	template<typename T>
	  int find(T&& x) {
	    auto it = ids.find(forward<T>(x));
	    return it == ids.end() ? -1 : it->second;
	  }
	string& getstr(int id) {
		return values[id];
	}
};
