#include <complex>
using namespace std;

// in-place Fast Fourier transform, n must be a power of 2
void fft(complex<double> *a, int n, bool inverse)
{
	int logn = 0;
	for(int i = 1; i < n; i <<= 1)
		logn++;

	for(int i = 0; i < n; i++)
	{
		int j = 0;
		for(int k = 0; k < logn; k++)
			if (i & (1<<k))
				j |= 1<<(logn - 1 - k);
		if (i < j)
			swap(a[i], a[j]);
	}

	for(int len = 2; len <= n; len <<= 1)
	{
		int half = len/2;
		double ang = 2 * M_PI / len * (invert ? -1 : 1);
		complex<double> wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len)
		{
			complex<double> w(1, 0);
			for (int j = i; j < i+half; j++)
			{
				complex<double> t = a[j+half] * w;
				a[j+half] = a[j] - t;
				a[j] = a[j] + t;
				w *= wlen;
			}
		}
	}
	if (invert) 
		for (int i = 0; i < n; ++i) 
			a[i] /= n;

}