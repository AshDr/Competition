const double PI = acos(-1);
struct Complex {
    double x,y;
    Complex operator + (Complex tmp) {return {x + tmp.x,y + tmp.y};}
    Complex operator * (Complex tmp) {return {x * tmp.x - y * tmp.y,x * tmp.y + y * tmp.x};}
    Complex operator - (Complex tmp) {return {x - tmp.x,y - tmp.y};}
}a[N],b[N],c[N];
int bit,tot,rev[N];
void FFT(Complex a[],int inv) {
    for(int i = 0; i < tot; i++) if(i < rev[i]) swap(a[i],a[rev[i]]);
    for(int mid = 1; mid < tot; mid <<= 1) {
        auto w1 = Complex{cos(PI / mid),inv * sin(PI/mid)};
        for(int i = 0 ; i < tot; i += mid * 2){
            auto wk = Complex{1,0};
            for(int j = 0; j < mid; j++,wk = wk * w1) {
                auto x = a[i + j],y = wk * a[i + j + mid];
                a[i + j] = x + y;a[i + j + mid] = x - y;
            }
        }
    }
    if(inv == -1) for(int i = 0; i < tot;++i) a[i].x /= tot;  // 变成系数表示的时候 c_k = a_k / n 
}
void solve() {  
    cin>>n;
    for(int i = 1; i <= n; i++) {
        cin>>a[i].x;
        c[n - i].x = a[i].x;
        b[i].x = (double)(1.0 / i / i);
    }
    while((1 << bit) <= (n << 1)) ++bit; // 最后来到 x^{n^2} 2n项
    tot = (1 << bit);
    for(int i = 0; i < tot; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    FFT(a,1);FFT(b,1);FFT(c,1);
    for(int i = 0; i < tot; i++) a[i] = a[i] * b[i],c[i] = c[i] * b[i];
    FFT(a,-1);FFT(c,-1);
    for(int i = 1 ; i <= n; i++) cout<<a[i].x - c[n - i].x<<'\n';
}
