vector<int> get_fail(string s) { // get border(pi[i]表示从i结尾的前缀子串的border长度)
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}

template <class T>
std::vector<int> z_algorithm(const std::vector<T> &s) { // z[i]表示以i开始的后缀与s的lcp
  int n = int(s.size());
  if (n == 0) return {};
  vector<int> z(n);
  z[0] = 0;
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r && z[i - l] < r - i + 1) {
      z[i] = z[i - l];
    } else {
      z[i] = max(0, r - i + 1);
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    }
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  z[0] = n;
  return z;
}
std::vector<int> z_algorithm(const std::string &s) {
  int n = int(s.size());
  std::vector<int> s2(n);
  for (int i = 0; i < n; i++) {
    s2[i] = s[i];
  }
  return z_algorithm(s2);
}
std::vector<int> z_match(const std::string &s, const std::string &t) {  // find the lcp of all suffix of s with t
  int n = int(s.size()), m = int(t.size());
  if (s.size() == 0) return {};
  if (t.size() == 0) return vector<int>(n, 0);
  vector<int> z = z_algorithm(t);
  vector<int> ans(n, 0);
  while (ans[0] < n && s[ans[0]] == t[ans[0]]) ans[0]++;
  for (int i = 1, j = 0; i < n; i++) {
    ans[i] = (j + ans[j] <= i ? 0 : min(j + ans[j] - i, z[i - j]));
    while (ans[i] < m && i + ans[i] < n && s[i + ans[i]] == t[ans[i]]) ++ans[i];
    if (j + ans[j] < i + ans[i]) j = i;
  }
  return ans;
}