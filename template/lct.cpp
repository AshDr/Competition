// https://codeforces.com/contest/603/submission/65794887
struct LinkCutTree {
  struct Node {
    Node *child[2], *parent, *max;
    int sum, val, weight, id, rev;
    Node(int val, int weight, int id)
        : child{nullptr, nullptr}, parent(nullptr), max(this), sum(val), val(val), weight(weight), id(id), rev(false) {}
  };
  bool isRoot(Node *p) { return p->parent == nullptr || p->parent->child[0] != p && p->parent->child[1] != p; }
  int side(Node *p) { return p->parent->child[1] == p; }
  int sum(Node *p) { return p == nullptr ? 0 : p->sum; }
  Node *max(Node *p) { return p == nullptr ? nullptr : p->max; }
  Node *max(Node *p, Node *q) {
    if (p == nullptr) return q;
    if (q == nullptr) return p;
    return p->weight > q->weight ? p : q;
  }
  void reverse(Node *p) {
    if (p == nullptr) return;
    swap(p->child[0], p->child[1]);
    p->rev ^= 1;
  }
  void push(Node *p) {
    if (p->rev == 0) return;
    p->rev = 0;
    reverse(p->child[0]);
    reverse(p->child[1]);
  }
  void pull(Node *p) {
    p->sum = sum(p->child[0]) + sum(p->child[1]) + p->val;
    p->max = max(max(max(p->child[0]), max(p->child[1])), p);
  }
  void connect(Node *p, Node *q, int side) {
    q->child[side] = p;
    if (p != nullptr) p->parent = q;
  }
  void rotate(Node *p) {
    auto q = p->parent;
    int dir = side(p) ^ 1;
    connect(p->child[dir], q, dir ^ 1);
    if (!isRoot(q))
      connect(p, q->parent, side(q));
    else
      p->parent = q->parent;
    connect(q, p, dir);
    pull(q);
  }
  void splay(Node *p) {
    vector<Node *> stk;
    for (auto i = p; !isRoot(i); i = i->parent) stk.push_back(i->parent);
    while (!stk.empty()) {
      push(stk.back());
      stk.pop_back();
    }
    push(p);
    while (!isRoot(p)) {
      auto q = p->parent;
      if (!isRoot(q)) rotate(side(p) == side(q) ? q : p);
      rotate(p);
    }
    pull(p);
  }
  void access(Node *p) {
    for (Node *i = p, *j = nullptr; i != nullptr; j = i, i = i->parent) {
      splay(i);
      i->val -= sum(j);
      i->val += sum(i->child[1]);
      i->child[1] = j;
      pull(i);
    }
    splay(p);
  }
  void makeRoot(Node *p) {
    access(p);
    reverse(p);
  }
  void link(Node *p, Node *q) {
    makeRoot(p);
    access(q);
    p->parent = q;
    q->val += sum(p);
  }
  void cut(Node *p, Node *q) {
    makeRoot(p);
    access(q);
    p->parent = q->child[0] = nullptr;
  }
  Node *pathMax(Node *p, Node *q) {
    makeRoot(p);
    access(q);
    return max(q);
  }
  int size(Node *p) {
    makeRoot(p);
    return sum(p);
  }
  bool connected(Node *p, Node *q) {
    access(p);
    access(q);
    return p->parent != nullptr;
  }
};
/*

struct LinkCutTree{
    using Info = int;
 
    struct Node{
        int s[2] = {}, p = 0;
        Info v = Info(), sum = Info();
        // Tag tag = Tag();
        bool rev = false;
 
        void reverse(){
            swap(s[0], s[1]);
            rev ^= 1;
        }
 
    }tr[maxn];
    int stk[maxn];
 
    bool is_root(int x){
        return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
    }
 
    // void apply(Node &x, Tag f){
 
    // }
 
    void pushdown(int x){
        if (tr[x].rev){
            tr[tr[x].s[0]].reverse();
            tr[tr[x].s[1]].reverse();
            tr[x].rev = 0;
        }
        // if (tr[x].s[0]) apply(tr[tr[x].s[0]], tr[x].tag);
        // if (tr[x].s[1]) apply(tr[tr[x].s[1]], tr[x].tag);
        // tr[x].tag = Tag();
    }
 
    void pushup(int x){
        tr[x].sum = tr[tr[x].s[0]].sum + tr[x].v + tr[tr[x].s[1]].sum;
    }
 
    void rotate(int x){
        int y = tr[x].p, z = tr[y].p;
        int k = tr[y].s[1] == x;
        if (!is_root(y)) tr[z].s[tr[z].s[1] == y] = x;
        tr[x].p = z;
        tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
        tr[x].s[k ^ 1] = y, tr[y].p = x;
        pushup(y), pushup(x);
    }
 
    void splay(int x){
        int top = 0, r = x;
        stk[++top] = x;
        while(!is_root(r)) stk[++top] = r = tr[r].p;
        while(top) pushdown(stk[top--]);
        while(!is_root(x)){
            int y = tr[x].p, z = tr[y].p;
            if (!is_root(y)){
                if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
 
    void access(int x){
        int z = x;
        for(int y = 0; x; y = x, x = tr[x].p){
            splay(x);
            tr[x].s[1] = y, pushup(x);
        }
        splay(z);
    }
 
    void make_root(int x){
        access(x);
        tr[x].reverse();
    }
 
    int find_root(int x){
      access(x);
      while(tr[x].s[0]) x = tr[x].s[0];
      splay(x);
      return x;
  }
 
    bool is_same(int x, int y){
        make_root(x);
        return find_root(y) == x;
    }
 
    void split(int x, int y){
        make_root(x);
        access(y);
    }
 
    void link(int x, int y){
        make_root(x);
        tr[x].p = y;
    }
 
    void cut(int x, int y){
        make_root(x);
        access(y);
        splay(x);
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
 
    Info query(int x, int y){
        split(x, y);
        return tr[y].sum;
    }
    
    void modify(int x, const Info &info){
        splay(x);
        tr[x].v = info;
        pushup(x);
    }
 
    // void modify(int x, int y, const Tag &tag){
    //     split(x, y);
    //     apply(tr[y], tag);
    // }
 
}LCT;
*/