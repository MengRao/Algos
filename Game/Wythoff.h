// check if {a,b} is in cold position, a player currently in cold position will lose, othersise will win
// a>=0, b>=0
bool wythoff(long long a, long long b)
{
	if(a>b)
		swap(a,b);
	double phi=1.618033988749894848; // the golden ratio
	long long k = a/phi + 1; // as phi is a irrational number, a/phi will always be rounded down by some fraction above 0
	return (long long)(k*phi) == a && (long long)(k*phi*phi) == b;
}