struct TwoSat {
	int n;
	vector<vi> gr;

	TwoSat(int _n = 0) : n(_n), gr(2*n) {}

	int add_var() { // (optional)
		gr.emplace_back();
		gr.emplace_back();
		return n++;
	}

	void add_clause(int aind, bool aval, int bind, bool bval) {
		int a = 2*aind + aval, b = 2*bind + bval;
		gr[a^1].push_back(b);
		gr[b^1].push_back(a);
	}
	void set_value(int index, bool value) { // (optional)
		add_clause(index, value, index, value);
	}

	void at_most_one(const vi& li, bool val=1) { // (optional)
		if (sz(li) <= 1) return;
		int cur = li[0];
		FOR(i,2,sz(li)-1) {
			int next = add_var();
			add_clause(cur, !val, li[i], !val);
			add_clause(cur, !val, next, val);
			add_clause(li[i], !val, next, val);
			cur = next;
		}
		add_clause(cur, !val, li[1], !val);
	}

	vi id, val, comp, z; int time = 0;
	int dfs(int i) {
		int low = id[i] = ++time, x; z.push_back(i);
		fore(e, gr[i]) if (!comp[e])
			low = min(low, id[e] ? id[e] : dfs(e));
		if (low == id[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if (val[x>>1] == -1)
				val[x>>1] = x&1;
		} while (x != i);
		return id[i] = low;
	}

	bool solve() {
		val.assign(n, -1);
		id.assign(2*n, 0); comp = id;
		rep(i,2*n) if (!comp[i]) dfs(i);
		rep(i,n) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};
