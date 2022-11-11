function<LL(LL,LL,LL)>euler_pow = [&](LL a, LL b, LL mod){
    if(b == 1 || mod == 1) return a % mod;
    if(b == 0) return 1ll;
    return qpow(a, euler_pow(a, b - 1, getphi(mod)) + getphi(mod), mod);
};