struct node {
    int lmx,rmx,mx;
    int tag;
}tr[N << 2];
#define lt idx<<1
#define rt idx<<1|1
void pull(int idx) {

}
void push(int idx) {
    if(tr[idx].tag == 0) return ;    
}
void build(int idx, int L, int R) {
    if(L == R) {
        return ;
    }
    int mid = (L + R) >> 1;
    build(lt, L, mid);
    build(rt, mid + 1, R);
    pull(idx);
}
void modify(int idx, int L, int R, int pos,int val) {
    if(L == R) {
        return ;
    }
    push(idx);
    int mid = (L + R) >> 1;
    if(pos <= mid) modify(lt, L, mid, pos, val);
    else modify(rt, mid + 1, R, pos, val);
    pull(idx);
}
int query(int idx, int L, int R, int l, int r) {
    if(l <= L && r >= R) {
        return ;
    }
    push(idx);
    int mid = (L + R) >> 1;
    int ans = 0;
    if(l <= mid) ans += query(lt, L, mid, l, r);
    if(r > mid) ans += query(rt, mid + 1, R, l, r);
    return ans;  
}