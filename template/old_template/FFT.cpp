const double PI = acos(-1);
struct Complex {
  double x, y;
  Complex operator+(Complex tmp) { return {x + tmp.x, y + tmp.y}; }
  Complex operator*(Complex tmp) { return {x * tmp.x - y * tmp.y, x * tmp.y + y * tmp.x}; }
  Complex operator-(Complex tmp) { return {x - tmp.x, y - tmp.y}; }
} mula[N], mulb[N], mulc[N];
int bit, tot, rev[N];
void init() {
  for (int i = 0; i < tot; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
}
void FFT(Complex a[], int inv) {
  for (int i = 0; i < tot; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int mid = 1; mid < tot; mid <<= 1) {
    auto w1 = Complex{cos(PI / mid), inv * sin(PI / mid)};
    for (int i = 0; i < tot; i += mid * 2) {
      auto wk = Complex{1, 0};
      for (int j = 0; j < mid; j++, wk = wk * w1) {
        auto x = a[i + j], y = wk * a[i + j + mid];
        a[i + j] = x + y;
        a[i + j + mid] = x - y;
      }
    }
  }
  if (inv == -1)
    for (int i = 0; i < tot; ++i)
      a[i].x = (int)(a[i].x / tot + 0.5);  // 变成系数表示的时候 c_k = a_k / n，需要的时候在这里mod
}
void Mul(Complex a[], Complex b[], Complex c[], int deg) {
  for (int i = 0; i < tot; i++) {
    mula[i] = a[i];
    mulb[i] = b[i];
  }
  FFT(mula, 1);
  FFT(mulb, 1);
  for (int i = 0; i < tot; i++) mulc[i] = mula[i] * mulb[i];
  FFT(mulc, -1);
  for (int i = 0; i <= deg; i++) c[i] = mulc[i];
}

void MulInt(int a[], int b[], int c[], int deg) {
  for (int i = 0; i < tot; i++) {
    mula[i] = Complex(a[i], 0);
  }
  for (int i = 0; i < tot; i++) {
    mulb[i] = Complex(b[i], 0);
  }
  FFT(mula, 1);
  FFT(mulb, 1);
  for (int i = 0; i < tot; i++) mulc[i] = mula[i] * mulb[i];
  FFT(mulc, -1);
  for (int i = 0; i <= deg; i++) c[i] = mulc[i].x;
}
// 初始化tot和bit，然后再调用一次init,注意不要覆盖全局变量