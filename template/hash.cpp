const int MODS[] = {998244353, 1000000007, 1000000009};
const int numofmods = sizeof(MODS) / sizeof(MODS[0]);
ll base = myRand(MODS[0]) + 1;
struct HashValue {
  std::vector<ll> hashes;
  HashValue() { hashes.resize(numofmods); }
  HashValue(ll x) {
    hashes.resize(numofmods);
    for (int i = 0; i < numofmods; i++) {
      hashes[i] = x % MODS[i];
    }
  }
  HashValue(std::initializer_list<ll> list) {
    hashes.resize(numofmods);
    int i = 0;
    for (ll x : list) {
      hashes[i++] = x % MODS[i];
    }
  }
  bool operator==(const HashValue &rhs) const {
    for (int i = 0; i < numofmods; i++) {
      if (hashes[i] != rhs.hashes[i]) {
        return false;
      }
    }
    return true;
  }
  bool operator!=(const HashValue &rhs) const { return !(*this == rhs); }
  HashValue operator+(const HashValue &rhs) const {
    HashValue res;
    for (int i = 0; i < numofmods; i++) {
      res.hashes[i] = (hashes[i] + rhs.hashes[i]) % MODS[i];
    }
    return res;
  }
  HashValue operator-(const HashValue &rhs) const {
    HashValue res;
    for (int i = 0; i < numofmods; i++) {
      res.hashes[i] = (hashes[i] - rhs.hashes[i] + MODS[i]) % MODS[i];
    }
    return res;
  }
  HashValue operator*(const HashValue &rhs) const {
    HashValue res;
    for (int i = 0; i < numofmods; i++) {
      res.hashes[i] = (hashes[i] * rhs.hashes[i]) % MODS[i];
    }
    return res;
  }
  HashValue operator*(ll x) const {
    HashValue res;
    for (int i = 0; i < numofmods; i++) {
      res.hashes[i] = (hashes[i] * x) % MODS[i];
    }
    return res;
  }
  bool operator<(const HashValue &rhs) const { return hashes < rhs.hashes; }
  friend ostream &operator<<(ostream &os, const HashValue &rhs) {
    os << "{";
    for (int i = 0; i < numofmods; i++) {
      os << rhs.hashes[i];
      if (i + 1 < numofmods) {
        os << ", ";
      }
    }
    os << "}";
    return os;
  }
};

struct HashString {
  vector<HashValue> pw, inv, h, revh;
  int n;
  // string start from index 1
  HashString(string s) {
    n = s.size() - 1;
    init(n);
    for (int i = 1; i <= n; i++) {
      h[i] = h[i - 1] + HashValue(s[i]) * pw[i];
      revh[i] = revh[i - 1] + HashValue(s[n - i + 1]) * pw[i];
    }
  }
  void init(int n) {
    pw.resize(n + 1);
    inv.resize(n + 1);
    h.resize(n + 1);
    revh.resize(n + 1);
    pw[0] = inv[0] = HashValue(1);
    pw[1] = HashValue(base);  // base
    for (int i = 0; i < numofmods; i++) {
      inv[1].hashes[i] = qpow(pw[1].hashes[i], MODS[i] - 2, MODS[i]);
    }
    for (int i = 2; i <= n; i++) {
      pw[i] = pw[i - 1] * pw[1];
      inv[i] = inv[i - 1] * inv[1];
    }
  }
  HashValue get(int l, int r) { return (h[r] - h[l - 1]) * inv[l - 1]; }  // l->r的hash值
  HashValue getRev(int l, int r) {
    if (l < r) swap(l, r);
    l = n + 1 - l;
    r = n + 1 - r;
    return (revh[r] - revh[l - 1]) * inv[l - 1];
  }  // r->l的hash值
};
/*
h[i]=h[i-1]+pw[i]*s[i];
h2[i]=h2[i-1]+pw[i]*s[n+1-i];
*/
hsh get(int l, int r) { return (h[r] - h[l - 1]) * inv[l - 1]; }
hsh get2(int l, int r) {
  swap(l, r);
  l = n + 1 - l;
  r = n + 1 - r;
  return (h2[r] - h2[l - 1]) * inv[l - 1];
}
// ll wt(){
//    return M2*w1+w2;
// }