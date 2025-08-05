// min_range  左右开区间，区间内数都>=a[i]
auto get_range = [&](vector<int> &a)->vector<pair<int,int>>{
  vector<int> stk;
  int n=sz(a)-1; // [1~n]
  vector<pair<int,int>> rg(n+1);
  for (int i = 1; i <= n; i++) {
    while (!stk.empty() && a[stk.back()] > a[i]) {
      rg[stk.back()].second = i;
      stk.pop_back();
    }
    stk.push_back(i);
  }
  while (!stk.empty()) {
    rg[stk.back()].second = n + 1;
    stk.pop_back();
  }
  for (int i = n; i >= 1; i--) {
    while (!stk.empty() && a[stk.back()] > a[i]) {
      rg[stk.back()].first = i;
      stk.pop_back();
    }
    stk.push_back(i);
  }
  while (!stk.empty()) {
    rg[stk.back()].first = 0;
    stk.pop_back();
  }
  return rg;
};