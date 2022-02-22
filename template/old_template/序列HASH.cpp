il ll hash1(vector<ll>f)
{
	ll h=0;
	for(int i=0;i<n;++i)h=(h*1333331+f[i])%998244353;
	ret h;
}
il ll hash2(vector<ll>f)
{
	ll h=0;
	for(int i=0;i<n;++i)h=(h*1333331+f[i])%1000000007;
	ret h;
}
il ll hash0(vector<ll>f){ret hash1(f)*1000000007+hash2(f);}