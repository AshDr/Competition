const LL G = 3;
mint invG = mpow(mint(G), MOD - 2);
int limit = 1;
int rev[N];
void NTT(mint *f, int n, int fl) {
  for (int i = 0; i < limit; i++) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? limit >> 1 : 0);
  for (int i = 0; i < n; ++i)
    if (i < rev[i]) swap(f[i], f[rev[i]]);
  for (int p = 2; p <= n; p <<= 1) {
    int len = (p >> 1);
    mint w = mpow((fl == 0) ? G : invG, (MOD - 1) / p);
    for (int st = 0; st < n; st += p) {
      mint buf = 1, tmp;
      for (int i = st; i < st + len; ++i)
        tmp = buf * f[i + len], f[i + len] = (f[i] - tmp), f[i] = (f[i] + tmp), buf = buf * w;
    }
  }
  if (fl == 1) {
    mint invN = mpow(mint(n), MOD - 2);
    for (int i = 0; i < n; ++i) f[i] = (f[i] * invN);
  }
}