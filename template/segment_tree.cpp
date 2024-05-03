//one base, [l, r]
template<class Info>
struct SegmentTree{
    int n;
    vector<Info> info;
    vector<pair<int, Info> > ops;
 
    SegmentTree() {}
 
    SegmentTree(int n, Info _init = Info()){
        init(vector<Info>(n, _init));
    }
 
    SegmentTree(const vector<Info> &_init){
        init(_init);
    }
 
    void init(const vector<Info> &_init){
        n = (int)_init.size();
        info.assign((n << 2) + 1, Info());
        function<void(int, int, int)> build = [&](int p, int l, int r){
            if (l == r){
                info[p] = _init[l - 1];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }
 
    void pull(int p){
        info[p] = info[2 * p] + info[2 * p + 1];
    }
 
    void modify(int p, int l, int r, int x, const Info &v){
        ops.push_back({p, info[p]});
        if (l == r){
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x <= m){
            modify(2 * p, l, m, x, v);
        } 
        else{
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
 
    void modify(int p, const Info &v){
        modify(1, 1, n, p, v);
    }
 
    Info query(int p, int l, int r, int x, int y){
        if (l > y || r < x){
            return Info();
        }
        if (l >= x && r <= y){
            return info[p];
        }
        int m = (l + r) / 2;
        return query(2 * p, l, m, x, y) + query(2 * p + 1, m + 1, r, x, y);
    }
 
    Info query(int l, int r){
        return query(1, 1, n, l, r);
    }
 
    int find_first(int p, int l, int r, int L, int R, const function<bool(const Info&)> &f, Info &pre){
        if (l > R || r < L){
            return r + 1;
        }
        if (l >= L && r <= R){
            if (!f(pre + info[p])){
                pre = pre + info[p];
                return r + 1;
            }
            if (l == r) return r;
            int m = (l + r) / 2;
            int res;
            if (f(pre + info[2 * p])){
                res = find_first(2 * p, l, m, L, R, f, pre);
            }
            else{
                pre = pre + info[2 * p];
                res = find_first(2 * p + 1, m + 1, r, L, R, f, pre);
            }
            return res;
        }
        int m = (l + r) / 2;
        int res = m + 1;
        if (L <= m){
            res = find_first(2 * p, l, m, L, R, f, pre);
        }
        if (R > m && res == m + 1){
            res = find_first(2 * p + 1, m + 1, r, L, R, f, pre);
        }
        return res;
    }
 
    int find_first(int l, int r, const function<bool(const Info&)> &f){
        Info pre = Info();
        return find_first(1, 1, n, l, r, f, pre);
    }
 
    int find_last(int p, int l, int r, int L, int R, const function<bool(const Info&)> &f, Info &suf){
        if (l > R || r < L){
            return l - 1;
        }
        if (l >= L && r <= R){
            if (!f(info[p] + suf)){
                suf = info[p] + suf;
                return l - 1;
            }
            if (l == r) return r;
            int m = (l + r) / 2;
            int res;
            if (f(info[2 * p + 1] + suf)){
                res = find_last(2 * p + 1, m + 1, r, L, R, f, suf);
            }
            else{
                suf = info[2 * p + 1] + suf;
                res = find_last(2 * p, l, m, L, R, f, suf);
            }
            return res;
        }
        int m = (l + r) / 2;
        int res = m;
        if (R > m){
            res = find_last(2 * p + 1, m + 1, r, L, R, f, suf);
        }
        if (L <= m && res == m){
            res = find_last(2 * p, l, m, L, R, f, suf);
        }
        return res;        
    }
 
    int find_last(int l, int r, const function<bool(const Info&)> &f){
        Info suf = Info();
        return find_last(1, 1, n, l, r, f, suf);
    }
 
    int ver(){
        return (int)ops.size();
    }
 
    void undo(int k){
        while(ops.size() > k){
            auto [a, b] = ops.back();
            ops.pop_back();
            info[a] = b;
        }
    }
 
};
struct Info {
    //define info, may be need contructor
};
Info operator+(const Info &a, const Info &b) {
    Info c;
    //merge info
    
    return c;
}


/*
//[0, n)
template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {//[ )
        return rangeQuery(1, 0, n, l, r);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};
*/