// Get LCP(longest common prefix) array given string T of length n and its suffix array which was already built, LCP[0] is undefined
// time complexity: log(n)
//
// Lemma: For any i ∈ [0..n), LCP[SAI[i + 1]] ≥ LCP[SAI[i]] − 1. SAI for suffix array inverse.
// Proof. Let Tj be the lexicographic predecessor of Ti, i.e., Tj < Ti and there are no other suffixes between them in the lexicographical order.
//
// Then LCP[SAI[i]] = lcp(Ti, Tj) = l. If l = 0, the claim is trivially true.
//
// If l > 0, then for some symbol c, Ti = cTi+1 and Tj = cTj+1. Thus Tj+1 < Ti+1 and lcp(Ti+1, Tj+1) = l − 1.
//
// Let Tk be the immediate lexicographical predecessor of Ti+1. Then either k = j + 1 or Tj+1 < Tk < Ti+1. In either case,
// LCP[[SAI[i + 1]] = lcp(Ti+1, Tk) ≥ lcp(Ti+1, Tj+1) = l − 1 .


void getLCP(const unsigned char* T, const int *SA, int *LCP, int n)
{
	int *SAI = new int[n]; // suffix array inverse
	for (int i = 0; i < n; i++)
		SAI[SA[i]] = i;

	int l = 0;
	for (int i = 0; i < n; i++)
	{
		int k = SAI[i];
		if (k == 0)
			continue;
		int j = SA[k-1];
		while (T[i+l] == T[j+l])
			l++;
		LCP[k] = l;
		if (l > 0)
			l--;
	}
	delete SAI;
}