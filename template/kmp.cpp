auto kmp = [&](string s) {
  int len = sz(s);
  vector<int> nxt(len);
  for(int i = 1,j = 0; i < len; i++) {
    while(j && s[i] != s[j]) j = nxt[j - 1];
    if(s[i] == s[j]) ++j;
    nxt[i] = j; //border len 
  }
  return nxt;
};//try to get border array