const ll M1 = 998244353;
const ll M2 = 1e9 + 7;
struct hsh{
    ll w1,w2;
    hsh operator * (const int w){
        return {1ll*w1*w%M1,1ll*w2*w%M2};
    }
    hsh operator * (const hsh w){
        return {1ll*w1*w.w1%M1,1ll*w2*w.w2%M2};
    }
    hsh operator + (const hsh w){
        return {(w1+w.w1)%M1,(w2+w.w2)%M2};
    }
    hsh operator - (const hsh w){
        return {(w1+M1-w.w1)%M1,(w2+M2-w.w2)%M2};
    }
    bool operator == (const hsh w){
        return (w1==w.w1)&&(w2==w.w2);
    }
    ll wt(){
        return M2*w1+w2;
    }
    friend ostream operator << (ostream &os, hsh& x) {
    	os << x.w1 << " " << x.w2;
    }
}pw[N+50],inv[N+50],h[N+50],h2[N+50];
int n;
void init(int n) {
	ll b1 = myRand(M1) + 1, b2 = myRand(M2) + 1;
	pw[0] = inv[0] = {1, 1};
	pw[1] = {b1, b2};
	inv[1] = {qpow(b1, M1 - 2, M1), qpow(b2, M2 - 2, M2)};
	for(int i = 2; i <= n; i++) {
		pw[i] = pw[i - 1] * pw[1];
		inv[i] = inv[i - 1] * inv[1];
 	}
}
/*
h[i]=h[i-1]+pw[i]*s[i];
h2[i]=h2[i-1]+pw[i]*s[n+1-i];
*/
hsh get(int l,int r){
    return (h[r]-h[l-1])*inv[l-1];
}
hsh get2(int l,int r){
    swap(l,r);
    l=n+1-l; r=n+1-r;
    return (h2[r]-h2[l-1])*inv[l-1];
}