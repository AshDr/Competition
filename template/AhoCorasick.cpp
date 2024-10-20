struct AhoCorasick {
  static constexpr int ALPHABET = 26;  // change here
  static constexpr int ROOT = 'a';     // change here
  struct Node {
    int len;
    int link;
    int val;
    std::array<int, ALPHABET> next;
    Node() : len{0}, link{0}, val{0}, next{} {}
  };

  std::vector<Node> t;

  AhoCorasick() { init(); }

  void init() { t.assign(1, Node()); }

  int newNode() {
    t.emplace_back();
    return t.size() - 1;
  }

  int add(const std::string &a) {
    int p = 0;
    for (auto c : a) {
      int x = c - ROOT;
      if (t[p].next[x] == 0) {
        t[p].next[x] = newNode();
        t[t[p].next[x]].len = t[p].len + 1;
      }
      p = t[p].next[x];
    }
    t[p].val++;
    return p;
  }

  void work() {
    std::queue<int> q;
    for (int i = 0; i < ALPHABET; i++)
      if (t[0].next[i]) q.push(t[0].next[i]);
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (int i = 0; i < ALPHABET; i++) {
        if (t[x].next[i] == 0) {
          t[x].next[i] = t[t[x].link].next[i];  // 相当于路径压缩
        } else {
          t[t[x].next[i]].link = t[t[x].link].next[i];
          q.push(t[x].next[i]);
        }
      }
      t[x].val += t[t[x].link].val;  // 这个state的所有合法后缀(fail链上的字符串个数)
    }
  }

  int next(int p, int x) { return t[p].next[x]; }

  int link(int p) { return t[p].link; }

  int len(int p) { return t[p].len; }

  int val(int p) { return t[p].val; }

  int size() { return t.size(); }
};