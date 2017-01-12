struct mat
{
	int m, n;
	vector< vector<long long> > arr;

	mat()
		: m(0)
		, n(0)
	{
	}

	void init(int m_, int n_)
	{
		m = m_;
		n = n_;
		arr.resize(m);
		for (auto &r:arr)
		{
			r.resize(n, 0);
		}
	}
	
};

mat multiplyMat(const mat& a, const mat& b, int m)
{
	mat sol;
	sol.init(a.m, b.n);
	for (int i = 0; i < a.m; i++)
		for (int j = 0; j < b.n; j++)
			for (int k = 0; k < a.n; k++)
				sol.arr[i][j] = (sol.arr[i][j] + a.arr[i][k] * b.arr[k][j]) % m;
	return sol;
}

// mat a should be square
mat matpower(mat a, int p, int m)
{
	mat ret;
	ret.init(a.m, a.m);
	rep(i, a.m)
		ret.arr[i][i] = 1;
	while(p)
	{
		if (p%2)
			ret = multiplyMat(ret, a, m);
		a = multiplyMat(a, a, m);
		p /= 2;
	}
	return ret;
}