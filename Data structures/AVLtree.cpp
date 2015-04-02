#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int a[100000];

class AVLNode
{
public:
	 AVLNode(int value, AVLNode *parent)
		: v(value)
		, p(parent)
		, left(NULL)
		, right(NULL)
		, size(1)
		, balancedFactor(0)
	{
	}

	 ~AVLNode()
	 {
		 if (left)
			 delete left;
		 if (right)
			 delete right;
	 }
		
	int v;
	AVLNode *p;
	AVLNode *left;
	AVLNode *right;
	int size;
	int balancedFactor;
};

void leftRotate(AVLNode **px)
{
	AVLNode *x = *px;
	AVLNode *y = x->right;
	x->right = y->left;
	if (y->left)
		y->left->p = x;
	y->p = x->p;
	*px = y;
	y->left = x;
	x->p = y;
	y->size = x->size;
	x->size -= 1 + (y->right? y->right->size : 0);
	x->balancedFactor++;
	y->balancedFactor++;
}

void rightRotate(AVLNode **px)
{
	AVLNode *x = *px;
	AVLNode *y = x->left;
	x->left = y->right;
	if (y->right)
		y->right->p = x;
	y->p = x->p;
	*px = y;
	y->right = x;
	x->p = y;
	y->size = x->size;
	x->size -= 1 + (y->left? y->left->size : 0);
	x->balancedFactor--;
	y->balancedFactor--;
}

void balance(AVLNode *n, AVLNode **proot)
{
	// N is the child of P whose height increases by 1.
	AVLNode *p = n->p;

	while (p) { // Possibly up to the root
	AVLNode **pp = proot;
	if (p->p)
	{
		if (p == p->p->left)
			pp = &p->p->left;
		else
			pp = &p->p->right;
	}
   if (n == p->left) {
	   if (p->balancedFactor == 1) { // The left column in the picture
       // Temporary balance_factor(P) == 2 ==> rebalancing is required.
		   if (n->balancedFactor == -1) { // Left Right Case
			  leftRotate(&p->left); // Reduce to Left Left Case
		   }
       // Left Left Case
	   rightRotate(pp);
       break; // Leave the loop
     }
     if (p->balancedFactor == -1) {
       p->balancedFactor = 0; // Ns height increase is absorbed at P.
       break; // Leave the loop
     }
     p->balancedFactor = 1; // Height increases at P
   } else { // N == right_child(P), the child whose height increases by 1.
     if (p->balancedFactor == -1) { // The right column in the picture
       // Temporary balance_factor(P) == -2 ==> rebalancing is required.
       if (n->balancedFactor == 1) { // Right Left Case
		   rightRotate(&p->right); // Reduce to Right Right Case
       }
       // Right Right Case
       leftRotate(pp);
       break; // Leave the loop
     }
     if (p->balancedFactor == 1) {
       p->balancedFactor = 0; // Ns height increase is absorbed at P.
       break; // Leave the loop
     }
     p->balancedFactor = -1; // Height increases at P
   }
   n = p;
   p = n->p;
 }  // Possibly up to the root
}

void insert(int num, AVLNode **proot)
{
	AVLNode **pcur = proot;
	AVLNode *p = NULL;
	while (*pcur)
	{
		AVLNode *cur = *pcur;
		cur->size++;
		p = *pcur;

		if (num < cur->v)
		{
			pcur = &cur->left;
		}
		else
		{
			pcur = &cur->right;
		}
	}
	*pcur = new AVLNode(num, p);
	balance(*pcur, proot); // after balance, elements of equal value can be scattered in both left and right sides
}

int main(void) {
	int num;
	int t, n;
	cin >> t;
	while (t--)
	{
		cin >> n;
		
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		AVLNode *root = NULL;
		long long res = 0;
		for (int i = n-1; i >=0; i--) {
			num = a[i];
			insert(num, &root);
		}
		delete root;
		cout << res << endl;
		
	}
	
	
	return 0;
}