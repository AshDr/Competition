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