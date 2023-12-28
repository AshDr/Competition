template <class T> std::vector<int> z_algorithm(const std::vector<T>& s) {
    int n = int (s.size());
    if(n == 0) return {};
    vector<int> z(n);
    z[0] = 0;
    for(int i = 1, j = 0; i < n; i++) {
        z[i] = ((j + z[j] <= i) ? 0 : min(j + z[j] - i, z[i - j]));
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if(j + z[j] < i + z[i]) j = i;
    }
    z[0] = n;
    return z;
}
std::vector<int> z_algorithm(const std::string& s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return z_algorithm(s2);
}
std::vector<int> z_match(const std::string& s, const std::string& t) {//find the lcp of all suffix of s with t 
    int n = int(s.size()),m = int(t.size());
    if(s.size() == 0) return {};
    if(t.size() == 0) return vector<int>(n, 0);
    vector<int> z = z_algorithm(t);
    vector<int> ans(n, 0);
    while(ans[0] < n && s[ans[0]] == t[ans[0]]) ans[0]++;
    for(int i = 1, j = 0; i < n; i++) {
        ans[i] = (j + ans[j] <= i ? 0 : min(j + ans[j] - i, z[i - j]));
        while(ans[i] < m  && i + ans[i] < n && s[i + ans[i]] == t[ans[i]]) ++ans[i];
        if(j + ans[j] < i + ans[i]) j = i;
    }
    return ans;
}