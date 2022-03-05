template <int M>
struct static_mint {
  static_assert(0 < M, "Module must be positive");
  using mint = static_mint;
  int val;
  static_mint(): val() {}
  static_mint(long long x): val(x % M) { if (val < 0) val += M; }
  mint pow(long long n) const {
    mint ans = 1, x( * this);
    while (n) {
      if (n & 1) ans *= x;
      x *= x;
      n /= 2;
    }
    return ans;
  }
  mint inv() const {
    return pow(M - 2);
  }
  friend mint pow(const mint & m, long long n) {
    return m.pow(n);
  }
  friend mint inv(const mint & m) {
    return m.inv();
  }
  mint operator + () const {
    mint m;
    m.val = val;
    return m;
  }
  mint operator - () const {
    mint m;
    m.val = M - val;
    return m;
  }
  mint & operator += (const mint & m) {
    if ((val += m.val) >= M) val -= M;
    return *this;
  }
  mint & operator -= (const mint & m) {
    if ((val -= m.val) < 0) val += M;
    return *this;
  }
  mint & operator *= (const mint & m) {
    val = (long long) val * m.val % M;
    return *this;
  }
  mint & operator /= (const mint & m) {
    val = (long long) val * m.inv().val % M;
    return *this;
  }
  friend mint operator + (const mint & lhs,
    const mint & rhs) {
    return mint(lhs) += rhs;
  }
  friend mint operator - (const mint & lhs,
    const mint & rhs) {
    return mint(lhs) -= rhs;
  }
  friend mint operator * (const mint & lhs,
    const mint & rhs) {
    return mint(lhs) *= rhs;
  }
  friend mint operator / (const mint & lhs,
    const mint & rhs) {
    return mint(lhs) /= rhs;
  }
  friend bool operator == (const mint & lhs,
    const mint & rhs) {
    return lhs.val == rhs.val;
  }
  friend bool operator != (const mint & lhs,
    const mint & rhs) {
    return lhs.val != rhs.val;
  }
  mint & operator++() {
    return *this += 1;
  }
  mint & operator--() {
    return *this -= 1;
  }
  mint operator++(int) {
    mint result( * this);* this += 1;
    return result;
  }
  mint operator--(int) {
    mint result( * this);* this -= 1;
    return result;
  }
  template <typename T> explicit operator T() const {
    return T(val);
  }
  friend std::ostream & operator << (std::ostream & os,
    const mint & m) {
    return os << m.val;
  }
  friend std::istream & operator >> (std::istream & is, mint & m) {
    long long x;
    is >> x;
    m = x;
    return is;
  }
};
using mint = static_mint<998244353>;


// simple mint
LL inv(LL a) {LL u=0,v=1,b=mod;while(a) {LL t=b/a;b-=t*a,u-=t*v;swap(a,b);swap(u,v);}u%=mod;if(u<0)u+=mod;return u;}
struct mint {
    int x;
    mint():x(0) {}
    mint(int x):x(x) {if(x>=MOD||x<-MOD)x%=MOD;if(x<0)x+=MOD;this->x=x;}
    mint(LL x):x() {if(x>=MOD||x<-MOD)x%=MOD;if(x<0)x+=MOD;this->x=x;}
    mint& operator -=(const mint &rhs) {x -= rhs.x; if(x < 0) x += MOD; return *this;}
    mint& operator +=(const mint &rhs) {x += rhs.x; if(x >= MOD) x -= MOD; return *this;}
    mint& operator *=(const mint &rhs) {x = (LL)x * rhs.x % MOD; return *this;}
    mint& operator /=(const mint &rhs) {x = (LL)x * inv(rhs.x) % MOD; return *this;}
    bool operator < (const mint& rhs) {return x < rhs.x;}
    bool operator == (const mint& rhs) {return x == rhs.x;}
    bool operator != (const mint& rhs) {return x != rhs.x;}
    mint operator -() {return mint(x == 0 ? 0 : MOD - x);}
    friend mint operator +(const mint &lhs, const mint &rhs) {mint ret(lhs); return ret += rhs;}
    friend mint operator -(const mint &lhs, const mint &rhs) {mint ret(lhs); return ret -= rhs;}
    friend mint operator *(const mint &lhs, const mint &rhs) {mint ret(lhs); return ret *= rhs;}
    friend mint operator /(const mint &lhs, const mint &rhs) {mint ret(lhs); return ret /= rhs;}
    friend ostream& operator <<(ostream &os, const mint &rhs) {os << rhs.x; return os;}
    friend istream& operator >>(istream &is, mint &rhs) {LL a; is >> a; rhs = a; return is;}
};
mint qpow(mint a,LL b){mint r=1;for(;b;b>>=1){if(b&1)r=r*a;a=a*a;}return r;}