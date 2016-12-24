#include <map>
#include <vector>
using namespace std;

// ID start from 0
template<typename T> struct GetID {
	map<T, int> ids;
	vector<T> values;
	void clear() { ids.clear(); }
	int size() const { return values.size(); }
	int get(const T &x) {
		int newID = values.size();
		auto ret = ids.insert(make_pair(x, newID));
		if (!ret.second)
			return ret.first->second;

		values.push_back(x);
		return newID;
	}
};