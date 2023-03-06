int fac[N];
void decantor(int n, int p){
    assert(p<=fac[n]);
    int now=p-1;
    vector<int> res,ans;
    for(int i=1; i<=n; i++) res.push_back(i);
    for(int i=n; i>=1; i--) {
        int l=now/fac[i-1];
        now=now%fac[i-1];
        ans.push_back(res[l]);
        res.erase(res.begin()+l);
    }
    cout<<ans<<"\n";
}