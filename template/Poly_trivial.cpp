namespace NTT {
typedef long long ll;
typedef vector<ll> Poly;
const int mod = 998244353, G = 3, Gi = 332748118;
const int MM = 4e6;  // TODO
int bit, tot;
int rev[MM];
ll fac[MM], invf[MM], invv[MM];
ll qmi(ll a, ll b, ll p) {
  ll res = 1;
  while (b) {
    if (b & 1) res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}
int init = []() {
  fac[0] = 1;
  for (int i = 1; i < MM; i++) fac[i] = fac[i - 1] * i % mod;
  invf[MM - 1] = qmi(fac[MM - 1], mod - 2, mod);
  invf[0] = invf[1] = 1;
  for (int i = MM - 2; i >= 2; i--) invf[i] = invf[i + 1] * (i + 1) % mod;
  invv[0] = invv[1] = 1;
  for (int i = 2; i < MM; i++) invv[i] = invv[mod % i] * (mod - mod / i) % mod;
  return 0;
}();
ll binom(int x, int y) {
  if (y > x) return 0;
  return fac[x] * invf[x - y] % mod * invf[y] % mod;
}
// int init_inv=[](){
// inv[0]=inv[1]=1;
// for(int i=2;i<M;i++)
//     inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
// return 0;
// }();
void NTT(Poly &a, int inv) {
  for (int i = 0; i < tot; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);

  for (int mid = 1; mid < tot; mid *= 2) {
    ll w1 = qmi(inv == 1 ? G : Gi, (mod - 1) / (2 * mid), mod);
    for (int i = 0; i < tot; i += mid * 2) {
      ll wk = 1;
      for (int j = 0; j < mid; j++, wk = wk * w1 % mod) {
        ll x = a[i + j];
        ll y = wk * a[i + j + mid] % mod;
        a[i + j] = (x + y) % mod;
        a[i + j + mid] = (x - y + mod) % mod;
      }
    }
  }

  if (inv == -1)  // 就不用后面除了
  {
    ll intot = qmi(tot, mod - 2, mod);
    for (int i = 0; i < tot; i++) {
      a[i] = a[i] * intot % mod;
    }
  }
}
Poly mul(Poly a, Poly b)  // deg是系数的数量，所以有0~deg-1次项
{
  int deg = (int)a.size() + b.size() - 1;
  bit = 0;
  while ((1 << bit) < deg) bit++;  // 至少要系数的数量
  tot = 1 << bit;                  // 系数项为0~tot-1
  for (int i = 0; i < tot; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

  Poly c(tot);
  a.resize(tot), b.resize(tot);
  NTT(a, 1), NTT(b, 1);
  for (int i = 0; i < tot; i++) c[i] = a[i] * b[i] % mod;
  NTT(c, -1);
  c.resize(deg);
  return c;
}
Poly mul(Poly a, Poly b, int deg)  // deg是系数的数量，所以有0~deg-1次项
{
  Poly c = mul(a, b);
  c.resize(deg);
  return c;
}
Poly operator*(Poly a, Poly b) { return mul(a, b); }
Poly operator*(Poly a, int t) {
  Poly res;
  for (int i = 0; i < a.size(); i++) res.push_back(1ll * a[i] * t % mod);
  return res;
}
Poly operator*(Poly a, ll t) {
  Poly res;
  for (int i = 0; i < a.size(); i++) res.push_back(a[i] * t % mod);
  return res;
}
Poly operator+(Poly a, Poly b) {
  Poly res(a);
  res.resize(max(a.size(), b.size()));
  for (int i = 0; i < b.size(); i++) res[i] = (res[i] + b[i]) % mod;
  return res;
}
Poly operator-(Poly a, Poly b) {
  Poly res(a);
  res.resize(max(a.size(), b.size()));
  for (int i = 0; i < b.size(); i++) res[i] = (res[i] - b[i] + mod) % mod;
  return res;
}
Poly Inv(Poly &f, int deg)  // 多项式f对于x^deg的逆元(注意rev[]等数组要开到2*deg的空间级别,f[]要开deg级别)
{
  if (deg == 1) return Poly(1, qmi(f[0], mod - 2, mod));

  Poly B = Inv(f, (deg + 1) >> 1);  // 上一个逆元
  Poly A(f.begin(), f.begin() + deg);

  bit = 0;
  while ((1 << bit) < (deg << 1)) bit++;  // 至少要系数的数量
  tot = 1 << bit;                         // 系数项为0~tot-1
  for (int i = 0; i < tot; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

  A.resize(tot), B.resize(tot);
  NTT(A, 1), NTT(B, 1);
  for (int i = 0; i < tot; i++) A[i] = B[i] * (2 - A[i] * B[i] % mod + mod) % mod;
  NTT(A, -1);
  A.resize(deg);
  return A;
}
Poly cdq_ntt(int l, int r, vector<Poly> &f) {
  if (l == r) return f[l];
  int mid = l + r >> 1;
  return mul(cdq_ntt(l, mid, f), cdq_ntt(mid + 1, r, f));
}
namespace Cipolla {
int W;
struct cp {
  ll x, y;
  cp(ll x = 0, ll y = 0) : x(x), y(y) {}
  cp operator+(const cp _) const { return {(x + _.x) % mod, (y + _.y) % mod}; }
  cp operator*(const cp _) const {
    return {(x * _.x % mod + y * _.y % mod * W % mod) % mod, (x * _.y + y * _.x) % mod};
  }
};
cp qmi(cp a, int b) {
  cp res = 1;
  while (b) {
    if (b & 1) res = res * a;

    a = a * a;
    b >>= 1;
  }
  return res;
}
int cipolla(int n) {
  if (qmi(n, (mod - 1) >> 1).x != 1) {
    return -1;
  }
  int a = rand() % mod;
  while (!a || qmi((1ll * a * a - n + mod) % mod, (mod - 1) >> 1).x == 1) {
    a = rand() % mod;
  }
  W = (1ll * a * a - n + mod) % mod;

  int x = qmi(cp(a, 1), (mod + 1) >> 1).x;
  if (x > mod - x) x = mod - x;
  return x;
}
}  // namespace Cipolla
Poly Sqrt(Poly &A, int deg) {
  if (deg == 1) {
    return {Cipolla::cipolla(A[0])};  // A[0]=1修改这里即可
  }

  Poly f0 = Sqrt(A, (deg + 1) >> 1);
  f0.resize(deg);
  Poly inf0 = Inv(f0, deg);
  Poly temp(A.begin(), A.begin() + deg);
  temp = mul(inf0, temp);
  temp.resize(deg);
  for (int i = 0; i < deg; i++) f0[i] = (f0[i] + temp[i]) * invv[2] % mod;

  return f0;
}
Poly Deriv(Poly f)  // 求导
{
  for (int i = 0; i < f.size(); i++) f[i] = f[i + 1] * (i + 1) % mod;
  f.pop_back();
  return f;
}
Poly Integ(Poly f)  // 积分
{
  f.push_back(0);
  for (int i = f.size() - 1; i >= 1; i--) f[i] = f[i - 1] * invv[i] % mod;
  f[0] = 0;
  return f;
}
Poly Ln(Poly f, int deg)  // f[0]=1
{
  f = mul(Deriv(f), Inv(f, deg));  // 2*n-1
  f.resize(deg - 1);
  return Integ(f);
}
Poly Exp(Poly &A, int deg)  // A[0]=0，记得至少开deg大小
{
  if (deg == 1) return {1};
  Poly f0 = Exp(A, (deg + 1) >> 1);
  Poly temp = f0;
  temp.resize(deg);
  temp = Ln(temp, deg);
  for (int i = 0; i < deg; i++) temp[i] = (A[i] - temp[i] + mod) % mod;
  temp[0] = (temp[0] + 1) % mod;
  temp = mul(f0, temp);
  temp.resize(deg);
  return temp;
}
Poly qmi_ntt(Poly A, int k, int deg = -1)  // A(x)^k且A[0]=1
{
  if (deg == -1) deg = (A.size() - 1) * k + 1;
  A.resize(deg);
  A = Ln(A, deg);
  A = A * k;
  A = Exp(A, deg);
  return A;
}  // k mod p is right
Poly qmi_ntt(Poly A, string s, int deg = -1)  // A(x)^k
{
  ll k = 0;   // mod (p)
  ll kk = 0;  // mod (p-1),即phi(p)
  bool ty = false;
  for (int i = 0; i < s.size(); i++) {
    k = (1ll * k * 10 + (s[i] - '0'));
    if (k >= mod) k %= mod, ty = true;
    kk = (1ll * kk * 10 + (s[i] - '0')) % (mod - 1);
  }
  if (deg == -1) deg = (A.size() - 1) * k + 1;
  A.resize(deg);
  int n = A.size();
  int t = 0;
  while (t < n && !A[t]) t++;

  if (t == n || ty && t >= 1) {
    return Poly(n, 0);
  }
  ll temp = qmi(A[t], mod - 2, mod);
  Poly B;
  for (int i = t; i < A.size(); i++) B.push_back(A[i] * temp % mod);

  B = Ln(B, B.size());
  B = B * k;
  B = Exp(B, B.size());
  B.resize(n);
  Poly res(n);
  temp = qmi(A[t], kk, mod);
  for (ll i = 1ll * t * k; i < n; i++) res[i] = B[i - 1ll * t * k] * temp % mod;
  return res;
}
// 多项式快速幂加强版
// 每一项都除以不为零的那一项 先降次 后升次
Poly psqmi_ntt(Poly A, int k) {
  Poly res(1, 1);
  while (k) {
    if (k & 1) res = res * A;
    A = A * A;
    k >>= 1;
  }
  return res;
}
}  // namespace NTT
using namespace NTT;
// init Poly with size = deg(num of args)
Poly f, g;