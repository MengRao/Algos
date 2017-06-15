#define LAZY 1
#define HAS_SIZE 1
#define HAS_SUM 0 // HAS_SUM depends on HAS_SIZE

struct node {
  int prior, key;
  node *l = 0;
  node *r = 0;
#if LAZY
  int lazy = 0;
#endif
#if HAS_SIZE
  int sz = 1;
#if HAS_SUM
  int sum;
#endif
#endif
  
  node(int k)
    : prior(rand())
    , key(k) 
#if HAS_SUM
    , sum(k)
#endif
    {}

#if LAZY
  void add(int ad) {
    lazy += ad;
    key += ad;
#if HAS_SUM
    sum += sz * ad;
#endif
  }
#endif

  void push(){
#if LAZY
    if(!lazy) return;
    if(l) l->add(lazy);
    if(r) r->add(lazy);
    lazy = 0;
#endif
  }

  void update(){
#if HAS_SIZE
    sz = 1;
#if HAS_SUM
    sum = key;
#endif
    if(l) {
      sz += l->sz;
#if HAS_SUM
      sum += l->sum;
#endif
    }
    if(r) {
      sz += r->sz;
#if HAS_SUM
      sum += r->sum;
#endif
    }
#endif
  }
};

typedef node* pnode;

void merge(pnode& p, pnode l, pnode r) {
  if(!l) p = r;
  else if(!r) p = l;
  else {
    if(l->prior > r->prior){
      p = l;
      l->push();
      merge(l->r, l->r, r);
    }
    else {
      p = r;
      r->push();
      merge(r->l, l, r->l);
    }
    p->update();
  }
}

void split(pnode p, pnode& l, pnode& r, int k) { // splits into < k and >= k
  if(!p){
    l = r = 0;
    return;
  }
  p->push();
  if(k <= p->key){
    r = p;
    split(p->l, l, p->l, k);
  } else {
    l = p;
    split(p->r, p->r, r, k);
  }
  p->update();
}

#if HAS_SIZE
void splitn(pnode p, pnode& l, pnode& r, int n) { // splits into [0,n-1] and [n,?]
  if(!p){
    l = r = 0;
    return;
  }
  p->push();
  int lsz = (p->l) ? p->l->sz : 0;
  if(lsz >= n){
    r = p;
    splitn(p->l, l, p->l, n);
  } else {
    l = p;
    splitn(p->r, p->r, r, n-lsz-1);
  }
  p->update();
}
#endif

void insert(pnode& p, pnode n) {
  if(!p) {
    p = n;
    return;
  }
  if(n->prior > p->prior){
    split(p, n->l, n->r, n->key);
    p = n;
  } else {
    p->push();
    if(n->key < p->key) {
      insert(p->l, n);
    } else {
      insert(p->r, n);
    }
  }
  p->update();
}

void erase(pnode& p, int k) {
  if(!p) return;
  p->push();
  if(p->key == k){
    merge(p, p->l, p->r);
  } else {
    if(k < p->key) erase(p->l, k);
    else erase(p->r, k);
    p->update();
  }
}
