// maximum bipartite match, time complexity: O(E*min(M,N))
//


#include <vector>
using namespace std;
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define FOR(i,a,b) for(int (i)=(a);(i)<=(b);++(i))
#define ll long long
#define LD long double
#define MP make_pair

#define MAXN 250
#define MAXM 250

vector<int> edge[MAXN];
int Left[MAXN];
int Right[MAXM];
int Rvisited[MAXM];

bool dfs(int i)
{
	for(auto el:edge[i])
	{
		if (Rvisited[el])
			continue;
		Rvisited[el] = 1;
		if (Right[el] < 0 || dfs(Right[el]))
		{
			Left[i] = el;
			Right[el] = i;
			return true;
		}
	}
	return false;
}

bool maximum_bipartite_match()
{
	memset(Left, -1, sizeof(Left));
	memset(Right, -1, sizeof(Right));
	int res = 0;
	int i;
	do
	{
		memset(Rvisited, 0, sizeof(Rvisited));
		for (i = 0; i < n;i++)
		{
			if (Left[i] < 0 && dfs(i))
			{
				res++;
				break;
			}
		}
	} while(i < n);

	return res;
}

