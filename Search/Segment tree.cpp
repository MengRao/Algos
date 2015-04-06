/**
 * Segment tree with lazy propagation. Building tree takes O(n) time, range query and range update takes O(logn).
 * It's a general template implementation that supports various operations on node combination(min, max, add, multiply...)
 * and various update fashion. You have to customize STNode(storing a query result), STUpdate(storing a pending update)
 * and the first five functions to make it useable.
 * Build tree: build_tree(1, 0, N-1)
 * Update tree: update_tree(1, 0, N-1, i, j, value)
 * Query tree: query_tree(1, 0, N-1, i, j)
 * Actual space required by the tree = 2*2^ceil(log_2(n))
 */
 
#include<iostream>
#include<algorithm>
using namespace std;
 
#include<string.h>
#include<math.h> 
 
struct STNode
{
	// default node indicates an out of range result, can be combined with another result or returned as result
	STNode()
		: v(0)
	{
	}
	int v;
};

struct STUpdate
{
	// default update should be converted to false
	STUpdate()
		: change(0)
	{
	}
	// if has pending update
	operator bool()
	{
		return change != 0;
	}
	int change;
};

// MAXNODE should be a least 2 * 2^ceil(log_2(N)), 4N is ok
#define N 20
#define MAXNODE 4*N
STNode tree[MAXNODE];
STUpdate lazy[MAXNODE];

int arr[N];

void initNode(STNode& node, int i)
{
	node.v = arr[i];
}

void combineNode(STNode& target, STNode left, STNode right)
{
	target.v = max(left.v, right.v);
}

void addUpdate(STUpdate& target, STUpdate update)
{
	target.change += update.change;
}

void applyUpdate(STNode& target, int rangesize, STUpdate update)
{
	target.v += update.change;
}

void clearUpdate(STUpdate& target)
{
	target.change = 0;
}

 
/**
 * Build and init tree
 */
void build_tree(int node, int a, int b) {
  	if(a == b) { // Leaf node
		initNode(tree[node], a);
		return;
	}
	
	build_tree(node*2, a, (a+b)/2); // Init left child
	build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
	
	combineNode(tree[node], tree[node*2], tree[node*2+1]);
}

/**
 * Query tree 
 */
STNode query_tree(int node, int a, int b, int i, int j) {
	
	if(a > j || b < i) return STNode(); // Out of range
 
	if(lazy[node]) { // This node needs to be updated
		applyUpdate(tree[node], b-a+1, lazy[node]);

		if(a != b) {
			addUpdate(lazy[node*2], lazy[node]);
			addUpdate(lazy[node*2+1], lazy[node]);
		}
		
		clearUpdate(lazy[node]);
	}
 
	if(a >= i && b <= j) // Current segment is totally within range [i, j]
		return tree[node];
 
	STNode res;
	STNode q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
	STNode q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child
 
	combineNode(res, q1, q2);
	return res;
}
 
/**
 * update tree
 */
void update_tree(int node, int a, int b, int i, int j, STUpdate update) {
	if(a > j || b < i) // Current segment is not within range [i, j]
		return;

	if(a >= i && b <= j) { // Segment is fully within range
		addUpdate(lazy[node], update);
    	return;
	}

  	if(lazy[node]) { 
		addUpdate(lazy[node*2], lazy[node]);
		addUpdate(lazy[node*2+1], lazy[node]);
		clearUpdate(lazy[node]);
  	}
 
	update_tree(node*2, a, (a+b)/2, i, j, update); // Updating left child
	update_tree(1+node*2, 1+(a+b)/2, b, i, j, update); // Updating right child

	STNode q1 = query_tree(node*2, a, (a+b)/2, a, b); // Query left child for full
	STNode q2 = query_tree(1+node*2, 1+(a+b)/2, b, a, b); // Query right child for full
	combineNode(tree[node], q1, q2);
}
 