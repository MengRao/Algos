// AVL tree with insertion, deletion, searching and finding kth element time in O(lgn)
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
	if (y->balancedFactor <= 0)
		x->balancedFactor -= y->balancedFactor;
	y->balancedFactor++;
	if (x->balancedFactor > 0)
		y->balancedFactor += x->balancedFactor;
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
	if (y->balancedFactor > 0)
		x->balancedFactor -= y->balancedFactor;
	y->balancedFactor--;
	if (x->balancedFactor <= 0)
		y->balancedFactor += x->balancedFactor;
}


void balanceAfterInsert(AVLNode *n, AVLNode **proot)
{
	// N is the child of P whose height increases by 1.
	AVLNode *p = n->p;

	while (p) 
	{ // Possibly up to the root
		AVLNode **pp = proot;
		if (p->p)
		{
			if (p == p->p->left)
				pp = &p->p->left;
			else
				pp = &p->p->right;
		}
	   if (n == p->left) {
		   p->balancedFactor++;
		   if (p->balancedFactor == 2) { // The left column in the picture
		   // Temporary balance_factor(P) == 2 ==> rebalancing is required.
			   if (n->balancedFactor == -1) { // Left Right Case
				  leftRotate(&p->left); // Reduce to Left Left Case
			   }
		   // Left Left Case
		   rightRotate(pp);
		   break; // Leave the loop
		 }
		 if (p->balancedFactor == 0) {
		   break; // Leave the loop
		 }
		 // p->balancedFactor == 1, continue to p
	   } else { // N == right_child(P), the child whose height increases by 1.
		   p->balancedFactor--;
		 if (p->balancedFactor == -2) { // The right column in the picture
		   // Temporary balance_factor(P) == -2 ==> rebalancing is required.
		   if (n->balancedFactor == 1) { // Right Left Case
			   rightRotate(&p->right); // Reduce to Right Right Case
		   }
		   // Right Right Case
		   leftRotate(pp);
		   break; // Leave the loop
		 }
		 if (p->balancedFactor == 0) {
		   break; // Leave the loop
		 }
		 // p->balancedFactor == -1, continue to p
	   }
	   n = p;
	   p = n->p;
 }  // Possibly up to the root
}

void AVLinsert(int num, AVLNode **proot)
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
	balanceAfterInsert(*pcur, proot); // after balance, elements of equal value can be scattered in both left and right sides
}

void balanceAfterDel(AVLNode *p, AVLNode **pn, AVLNode **proot)
{
	// PN is the child of P whose height increases by 1.

	while (p) 
	{ // Possibly up to the root
		AVLNode **pp = proot;
		if (p->p)
		{
			if (p == p->p->left)
				pp = &p->p->left;
			else
				pp = &p->p->right;
		}
	   if (pn == &p->right) {
		    p->balancedFactor++;
			if (p->balancedFactor == 2) 
			{ // The left column in the picture
				// Temporary balance_factor(P) == 2 ==> rebalancing is required.
				int b = p->left->balancedFactor;
				if (b == -1) { // Left Right Case
					leftRotate(&p->left); // Reduce to Left Left Case
				}
				// Left Left Case
				rightRotate(pp);
				if (b == 0)
					break; // Height does not change: Leave the loop
				p = p->p;
			 }
			 else if (p->balancedFactor == 1) {
			   break; // Leave the loop
			 }
			 // p->balancedFactor == 0, continue to p

	   } else { // N == left_child(P), the child whose height decrease by 1.
		   p->balancedFactor--;
			 if (p->balancedFactor == -2) { // The right column in the picture
			   // Temporary balance_factor(P) == -2 ==> rebalancing is required.
				int b = p->right->balancedFactor;
				if (b == 1) { // Right Left Case
					rightRotate(&p->right); // Reduce to Right Right Case
				}
			   // Right Right Case
			   leftRotate(pp);
			   if (b == 0)
				   break; // Leave the loop
			   p = p->p;
			 }
			 else if (p->balancedFactor == -1) {
			   break; // Leave the loop
			 }
			 // p->balancedFactor == 0, continue to p
	   }
	   pn = pp;
	   p = p->p;
	 }  // Possibly up to the root
}

// return true: found and deleted; false: not found
bool AVLdelete(int num, AVLNode **proot)
{
	AVLNode **pcur = proot;
	AVLNode *cur;
	while (*pcur)
	{
		cur = *pcur;
		if (num == cur->v)
			break;
		if (num < cur->v)
		{
			pcur = &cur->left;
		}
		else
		{
			pcur = &cur->right;
		}
	}
	if (!*pcur)
		return false;
	cur = *pcur;
	if (cur->left && cur->right)
	{
		if (cur->balancedFactor == 1)
		{
			pcur = &cur->left;
			while ((*pcur)->right)
				pcur = &(*pcur)->right;
		}
		else
		{
			pcur = &cur->right;
			while ((*pcur)->left)
				pcur = &(*pcur)->left;
		}
		cur->v = (*pcur)->v;
		cur = *pcur;
	}
	AVLNode *child = cur->left;
	if (!child)
		child = cur->right;
	*pcur = child;
	AVLNode *p = cur->p;
	if (child)
		child->p = p;
	while (p)
	{
		p->size--;
		p = p->p;
	}
	balanceAfterDel(cur->p, pcur, proot);
	delete cur;
	return true;
}

// find the kth value where 0 <= k < n
int AVLfindK(AVLNode *node, int k)
{
	int leftn = 0;
	if (node->left)
		leftn = node->left->size;
	if (leftn == k)
		return node->v;
	if (k < leftn)
		return AVLfindK(node->left, k);
	else
		return AVLfindK(node->right, k-leftn-1);
}