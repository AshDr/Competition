template<class T>
struct Disc{
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
};