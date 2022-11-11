function<void(int,int)> dfs = [&](int p, int s) {
    if(p == n) {
        if(!s) {
            ++ans;
        }
        return;
    }
    dfs(p + 1,s - a[p]);
    dfs(p + 1,s);
    dfs(p + 1,s + a[p]);
};
