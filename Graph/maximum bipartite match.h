// maximum bipartite match, time complexity: O(E*min(M,N))
//


#include <vector>
using namespace std;


#define MAXN 1000
#define MAXM 1000

vector<int> edge[MAXN];
int matchR[MAXM];
int Rvisited[MAXM], cookie;

bool dfs(int i)
{
	for(auto el:edge[i])
	{
		if (Rvisited[el] == cookie)
			continue;
		Rvisited[el] = cookie;
		if (matchR[el] < 0 || dfs(matchR[el]))
		{
			matchR[el] = i;
			return true;
		}
	}
	return false;
}

int maximum_bipartite_match(int n)
{
	memset(matchR, -1, sizeof(matchR));
	int res = 0;
	for (int i = 0; i < n;i++)
	{
		cookie++;
		if(dfs(i))
			res++;
	}

	return res;
}

