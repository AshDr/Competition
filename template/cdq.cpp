void cdq(int l, int r) {
    if(l == r) return;
    int mid = l + r >> 1;
    cdq(l,mid);
    sort(a+l,a+r+1,[&](node x, node y) {
        // if(x.x == y.x && x.y == y.y) return x.op < y.op;
        // else if(x.x == y.x) return x.y < y.y;
        // return x.x < y.x;
    });
    for(int i = l; i <= r; i++) {
        if(a[i].op == 1 && a[i].info1 <= mid) {
        }
        else if(a[i].op == 2 && a[i].info1 > mid) {
            // cerr << l << " " << r << " " << a[i].info1 << " "<< t << "\n";  
        }
    }
    for(int i = l; i <= r; i++) {
        if(a[i].op == 1 && a[i].info1 <= mid) {
        }
    }
    for(int i = l; i <= r; i++) a[i] = mem[i];
    cdq(mid+1,r);
}