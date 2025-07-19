struct Bitset{
	using ull = unsigned long long;
	vector<ull> b;
	int n;
	Bitset(int x=0){
		n = x;
		b.resize((n+63)/64,0);
	}
	
	int get(int x){
		return (b[x>>6]>>(x&63))&1;
	}
	
	void set(int x,int y){
		b[x>>6] |= 1ULL<<(x&63);
		if(!y)b[x>>6] ^= 1ULL<<(x&63);
	}
 
	Bitset &operator^=(const Bitset &another){
		for(int i = 0; i < b.size(); i++){
			b[i] ^= another.b[i];
		}
		return (*this);
	}
	
	Bitset operator^(const Bitset &another)const{
		return (Bitset(*this)^=another);
	}
	
    int highbit(){
        for(int i = int(b.size()) - 1; i >= 0; i--){
            if (b[i]){
                return (i << 6) + __lg(b[i]);
            }
        }
        return -1;
    }
 
};