namespace ewsd { //二维数点
    int nn = 0, mxid = 0;
    struct Q {
        int down, up, x, w, id;
        Q(int _x, int _down, int _up, int _w, int _id):x(_x),down(_down),up(_up),w(_w),id(_id){};
        bool operator < (const Q& rhs) {
            return this->x < rhs.x;
        }
    };
    vector<Q> qq;
    vector<int> ans;
    struct node {
        int x, y, w;
        node(int _x, int _y, int _w):x(_x),y(_y),w(_w){};
        bool operator < (const node& rhs) {
            return this->x < rhs.x;
        }
    };
    vector<node> nds;
    template<typename T>
    struct Fenwick{
        int n;
        std::vector<T> tr;

        Fenwick(int n) : n(n), tr(n + 1, 0){}

        int lowbit(int x){
            return x & -x;
        }

        void modify(int x, T c){
            for(int i = x; i <= n; i += lowbit(i)) tr[i] += c;
        }

        void modify(int l, int r, T c){
            modify(l, c);
            if (r + 1 <= n) modify(r + 1, -c);
        }

        T query(int x){
            T res = T();
            for(int i = x; i; i -= lowbit(i)) res += tr[i];
            return res;
        }

        T query(int l, int r) {
            return query(r) - query(l - 1);
        }

        int find_first(T sum){
            int ans = 0; T val = 0;
            for(int i = __lg(n); i >= 0; i--){
                if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] < sum){
                    ans |= 1 << i;
                    val += tr[ans];
                }
            }
            return ans + 1;
        }

        int find_last(T sum){
            int ans = 0; T val = 0;
            for(int i = __lg(n); i >= 0; i--){
                if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] <= sum){
                    ans |= 1 << i;
                    val += tr[ans];
                }
            }
            return ans;
        }
        int find_kth(int k) {
            int ans = 0,cnt = 0;
            for (int i = 1 << __lg(n);i >= 0;i--)  //这里的20适当的取值，与MAX_VAL有关，一般取lg(MAX_VAL)
            {
                ans += (1 << i);
                if (ans >= n || cnt + tr[ans] >= k)
                    ans -= (1 << i);
                else
                    cnt += tr[ans];
            }
            return ans + 1;
        }//注意k不能太大

    };
    void addquery(int l, int r, int down, int up, int id) {
        qq.emplace_back(l - 1, down, up, -1, id);
        qq.emplace_back(r, down, up, 1, id);
        mxid = max(mxid, id);
        nn = max(nn, up);
    }
    void addnode(int x, int y, int w) {
        nds.emplace_back(x, y, w);
        nn = max(nn, y);
    }
    void gao() {
        sort(all(nds));
        sort(all(qq));
        ans = vector<int>(mxid + 1);
        Fenwick<int> fw(nn + 1);
        int j = 0;
        for(int i = 0; i < sz(qq); i++) {
            while(j < sz(nds) && nds[j].x <= qq[i].x) {
                fw.modify(nds[j].y, nds[j].w);           
                ++j;
            }
            ans[qq[i].id] += qq[i].w * fw.query(qq[i].down, qq[i].up);
        }
    }
}
template<class T>
struct disc{
    vector<T>d;
    inline void insert(T k){d.push_back(k);}
    inline void init(){
        sort(d.begin(),d.end());
        d.erase(unique(d.begin(),d.end()),d.end());
    }
    inline int size(){return d.size();}
    inline int query(T k){
        return lower_bound(d.begin(),d.end(),k)-d.begin()+1;
    }
    inline void clear(){vector<T>().swap(d);}
};//用来离散化第二维