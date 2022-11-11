struct bigint{
  static const int BASE = 10;//进制
  vector<int> s;
  int len; 
  bigint(LL num = 0){*this = num;}
  bigint operator = (LL num) {
    s.clear();
    len = 0;
    do{
      s.emplace_back(num % BASE);
      num /= BASE;
      len++;
    }while(num > 0);
    return *this;
  }
  bigint operator = (const string&  str) {
    s.clear();
    int l = str.length();
    for(int i = l - 1; i >= 0; i--) {
      s[i] = str[i] - '0';
    }
    return *this;
  }
  bigint operator + (const bigint& x) {
    bigint res;
    int t = max(len,x.len);
    res.len = t;
    res.s = vector<int>(t,0);
    int carry = 0,sum = 0;
    int i;
    for(i = 0 ; i < min(x.len,len); i++) {
      sum = x.s[i] + s[i] + carry;
      res.s[i] = sum % BASE;
      carry = (sum >= BASE);
    }
    if(i < len) {
      for(int j = i; j < len; j++) {
        res.s[j] = s[j];
      }
    }
    else if(i < x.len) {
      for(int j = i; j < x.len; j++) {
        res.s[j] = x.s[j];
      }
    }
    if(carry) res.s.emplace_back(carry);
    res.len = res.s.size();
    return res;
  }
  friend ostream& operator << (ostream& out,const bigint& x) {
    for(int i = x.len - 1; i >= 0; i--) {
      out<<x.s[i];
    }
    return out;
  } 
};