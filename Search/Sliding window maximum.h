
const int N = 1000;

int a[N], n, k;
int q[N], qi, qj;

// get consecutive range max of size k in array a of size n, in O(n) time
// results are saved in-place from a[0] to a[n-k]
void go()
{
  qi = 0;
  qj = -1;
  for (int i = 0; i < k - 1; i++) {
    while (qj >= qi && q[qj] < a[i])
      qj--;
    q[++qj] = a[i];
  }
  for (int i = k - 1; i < n; i++) {
    while (qj >= qi && q[qj] < a[i])
      qj--;
    q[++qj] = a[i];
    // now q[qi] is max for range from a[i - k + 1] to a[i], it can be saved elsewhere rather than in-place
    if (a[i - k + 1] == q[qi])
      qi++;
    else
      a[i - k + 1] = q[qi];
  }
}