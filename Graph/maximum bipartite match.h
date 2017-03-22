// maximum bipartite match, time complexity: O(E*min(M,N))
//


#include <vector>
using namespace std;


const int N = 100;
const int M = 100;

vector<int> g[N];
int matchR[M], Rvisited[M], cookie;

bool dfs(int i)
{
	for(auto el:g[i])
	{
		if (Rvisited[el] == cookie)
			continue;
		Rvisited[el] = cookie;
		if (matchR[el] < 0 || dfs(matchR[el]))
		{
			matchR[el] = i;
			return 1;
		}
	}
	return 0;
}

int maximum_bipartite_match(int n)
{
	memset(matchR, -1, sizeof(matchR));
	int res = 0;
	for (int i = 0; i < n;i++)
	{
		cookie++;
    res += dfs(i);
	}

	return res;
}

