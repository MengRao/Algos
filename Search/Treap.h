#define LAZY 0
#define HAS_SIZE 0
#define KT int

struct node {
  int prior;
  KT key;
  node *l = 0;
  node *r = 0;
#if LAZY
  KT lazy = 0;
#endif
#if HAS_SIZE
  int sz = 1;
#endif
  //KT sum;
  
  node(KT k)
    : prior(rand())
    , key(k) 
    {}

#if LAZY
  void add(KT ad) {
    lazy += ad;
    key += ad;
    //sum += sz * ad;
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
#endif
    //sum = key;
    if(l) {
#if HAS_SIZE
      sz += l->sz;
#endif
      //sum += l->sum;
    }
    if(r) {
#if HAS_SIZE
      sz += r->sz;
#endif
      //sum += r->sum;
    }

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

void split(pnode p, pnode& l, pnode& r, KT k) { // splits into < k and >= k
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

void erase(pnode& p, KT k) {
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
