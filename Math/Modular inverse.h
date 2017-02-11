

// Extended Euclidean Algorithm to compute gcd(a,b) and x, y such that ax + by = gcd(a,b)
int GCDext(int a, int b, int &x, int &y) {
    int g = a;
    x = 1;
    y = 0;
    if (b != 0) {
        g = GCDext(b, a % b, y, x);
        y -= (a / b) * x;
    }
    return g;
}

// Get modular inverse of a mod m using Extended Euclidean Algorithm if a and m are coprime, otherwise no modular inverse exists
int invMod(int a, int m) {
    int x, y;
    if (GCDext(a, m, x, y) != 1)
        return 0; // no inverse exists
	return (x + m) % m;
}


int power(long long a, int p, int m)
{
	long long res = 1;
	while(p)
	{
    if (p & 1)
      res = res * a % m;
    a = a * a % m;
		p >>= 1;
	}
	return (int)res;
}

// Using Euler's theorem
int invMod2(int a, int m)
{
	return power(a, m-2, m);
}