template <typename Info, typename Tag>
struct DynamicLazySegmentTree {
  using ll = long long;
  struct Node;
  using Ptr = Node *;

  struct Node {
    Ptr l, r;
    ll L, R;
    Info info;
    Tag laz;
    Node() : l(nullptr), r(nullptr), info(Info()), laz(Tag()) {}
    Node(ll _L, ll _R) : l(nullptr), r(nullptr),L(_L),R(_R), info(Info()), laz(Tag()) {
    }
  };

  Ptr root;
  ll Rmax;
  DynamicLazySegmentTree(ll n = 0) {
    Rmax = 2;
    while (Rmax < n) Rmax *= 2;
    root = my_new(1, Rmax);
  }

  // get a[x]
  Info get_val(ll x) {
    ll L = 1, R = Rmax;
    Ptr t = root;
    while (L < R) {
      push(t);
      ll Mid = (L + R) / 2;
      if (x <= Mid) {
        if (!t->l) return Info();
        t = t->l, R = Mid;
      } else {
        if (!t->r) return Info();
        t = t->r, L = Mid+1;
      }
    }
    return t->info;
  }
  // a[i] <- x
  void set_val(ll i, const Info &x) { _set_val(root, 1, Rmax, i, x); }
  // apply x to a[l], a[l+1], ..., a[r-1]
  void apply(ll l, ll r, const Tag &x) { _apply(root, 1, Rmax, l, r, x); }
  // get sum(a[l], a[l+1], ..., a[r-1])
  Info fold(ll l, ll r) { return _fold(root, 1, Rmax, l, r); }
  // merge two seg tree
  void merge(DynamicLazySegmentTree &rhs) { root = _merge(root, rhs.root); }

 private:
  DynamicLazySegmentTree(Ptr _root, ll _Rmax) : root(_root), Rmax(_Rmax) {}

  Ptr my_new(ll L, ll R) {
    return new Node(L, R);
  }
  Ptr my_new() { return new Node{}; } // if mem limited, use this
  void my_del(Ptr p) { delete p; }
  
  void apply(Ptr p, const Tag& x) {
    assert(p != nullptr && x != Tag());
    p->laz.apply(x);
    p->info.apply(p->L, p->R, x); // todo: may change here
  }

  void push(Ptr t) {
    assert(t != nullptr);
    if (t->laz == Tag()) return;
    ll L=t->L, R=t->R;
    ll Mid= (L + R) / 2;
    if (!t->l) t->l = my_new(L, Mid);
    if (!t->r) t->r = my_new(Mid+1, R);
    apply(t->l, t->laz);
    apply(t->r, t->laz);
    t->laz = Tag();
  }

  void pull(Ptr t) {
    assert(t->laz == Tag());
    t->info = (t->l ? t->l->info : Info()) + (t->r ? t->r->info : Info());
  }

  void _set_val(Ptr t, ll L, ll R, ll i, const Info &x) {
    assert(L <= i && i <= R && t);
    if (L == R) {
      t->info = x;
      return;
    }
    ll Mid = (L + R) / 2;
    push(t);
    if (i <= Mid) {
      if (!t->l) t->l = my_new(L, Mid);
      _set_val(t->l, L, Mid, i, x);
    } else {
      if (!t->r) t->r = my_new(Mid+1, R);
      _set_val(t->r, Mid+1, R, i, x);
    }
    pull(t);
  }

  void _apply(Ptr t, ll L, ll R, ll a, ll b, const Tag &x) {
    assert(a <= b && a <= R && L <= b && t);
    if (a <= L and b >= R) {
      apply(t, x);
      if (L == R) t->laz = Tag();
      return;
    }
    ll Mid = (L + R) / 2;
    push(t);
    if (a <= Mid) {
      if (!t->l) t->l = my_new(L, Mid);
      _apply(t->l, L, Mid, a, b, x);
    }
    if (Mid < b) {
      if (!t->r) t->r = my_new(Mid+1, R);
      _apply(t->r, Mid+1, R, a, b, x);
    }
    pull(t);
    return;
  }

  Info _fold(Ptr t, ll L, ll R, ll a, ll b) {
    assert(a <= b && a <= R && L <= b && t);
    if (a <= L && b >= R) return t->info;
    ll Mid = (L + R) / 2;
    push(t);
    Info v = Info();
    if (a <= Mid && t->l) v = _fold(t->l, L, Mid, a, b) + v;
    if (Mid < b && t->r) v = v +_fold(t->r, Mid+1, R, a, b);
    return v;
  }

  Ptr _merge(Ptr t1, Ptr t2) {
    if (!t1 or !t2) return t1 ? t1 : t2;
    assert(t1->laz == Tag() && t2->laz == Tag());
    t1->l = merge(t1->l, t2->l);
    t1->r = merge(t1->r, t2->r);
    pull(t1), my_del(t2);
    return t1;
  }

  /*
  // [L, x), [x, R) で split
  pair<Ptr, Ptr> _split(Ptr t1, ll L, ll R, ll x) {
    if (!t1) return {nullptr, nullptr};
    assert(t1->laz == ei());
    Ptr t2 = my_new();
    ll M = (L + R) / 2;
  }
  */
};

namespace DynamicSegmentTreeImpl {
  // if not lazy, then no need to define Tag
  struct Tag {
    // Define the tag structure here
    void apply(const Tag &t) {
      // Apply the tag to the current tag
    }
    bool operator==(const Tag &other) const {
      return true;
    }
    bool operator!=(const Tag &other) const {
      return false;
    }
  };
  struct Info {

    friend Info operator+(const Info &lhs, const Info& rhs){ // impl

    }
    void apply(ll L, ll R, const Tag &t) {
      // Apply the tag to the info with the given range
      
    }
    void apply(const Tag &t) {
      // Apply the tag to the info
    }
  };

template <typename Info>
using DynamicSegmentTree = DynamicLazySegmentTree<Info,Tag>;
}  // namespace DynamicSegmentTreeImpl
using DynamicSegmentTreeImpl::DynamicSegmentTree;
using DynamicSegmentTreeImpl::Tag;
using DynamicSegmentTreeImpl::Info;