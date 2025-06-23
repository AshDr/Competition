struct BiTrieNode {
  array<int, 2> son;
  int cnt;

  BiTrieNode() : son({-1, -1}), cnt(0) {}
};

template <int MAXBITS>
struct BiTrie {
  vector<BiTrieNode> tree;

  BiTrie() { tree = {BiTrieNode{}}; }

  void reserve(int n) { tree.reserve(n); }

  void insert(long long x) {
    int cur = 0;
    tree[cur].cnt++;
    for (int i = MAXBITS - 1; i >= 0; i--) {
      int o = x >> i & 1;
      if (tree[cur].son[o] == -1) tree[cur].son[o] = new_node();
      cur = tree[cur].son[o];
      tree[cur].cnt++;
    }
  }

  void erase(long long x) {
    int cur = 0;
    tree[cur].cnt--;
    for (int i = MAXBITS - 1; i >= 0; i--) {
      int o = x >> i & 1;
      if (tree[cur].son[o] == -1) tree[cur].son[o] = new_node();
      cur = tree[cur].son[o];
      tree[cur].cnt--;
    }
  }

  long long max_xor(long long x) {
    long long res = 0;
    int cur = 0;
    if (tree[cur].cnt == 0) return 0;
    for (int i = MAXBITS - 1; i >= 0; i--) {
      int o = x >> i & 1;
      if (tree[cur].son[o ^ 1] != -1 && tree[tree[cur].son[o ^ 1]].cnt > 0) {
        res |= 1LL << i;
        cur = tree[cur].son[o ^ 1];
      } else
        cur = tree[cur].son[o];
    }
    return res;
  }

  int new_node() {
    tree.push_back(BiTrieNode());
    return tree.size() - 1;
  }
};