#include <map>
#include <vector>
using namespace std;

// ID start from 0
struct GetID {
	map<string, int> ids;
	int nid = {0};
	void clear() { ids.clear(); nid=0;}
	int size() const { return nid; }
	int get(string&& x) {
		auto ret = ids.emplace(forward<string>(x), nid);
		nid += ret.second;
		return ret.first->second;
	}
};

// ID start from 0
struct GetID2 {
	map<string, int> ids;
	vector<string> values;
	void clear() { ids.clear(); values.clear(); }
	int size() const { return values.size(); }

	int get(string&& x) {
		int newID = values.size();
		auto ret = ids.emplace(forward<string>(x), newID);
		if (ret.second)
			values.push_back(ret.first->first);

		return ret.first.second;
	}

	string& getStr(int id) {
		return values[id];
	}
};