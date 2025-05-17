template <char MIN_CHAR = 'a', int ALPHABET = 26> struct Trie {
  struct trie_node {
    array<int, ALPHABET> child;
    int words_here = 0, starting_with = 0;

    trie_node() { memset(&child[0], 0, ALPHABET * sizeof(int)); }
  };

  static const int ROOT = 1;
  // when del all str, query may go back to 0, and never go out
  vector<trie_node> nodes = {trie_node(), trie_node()};

  Trie(int total_length = -1) {
    if (total_length >= 0)
      nodes.reserve(total_length + 2);
  }

  int get_or_create_child(int node, int c) {
    if (nodes[node].child[c] == 0) {
      nodes[node].child[c] = int(nodes.size());
      nodes.emplace_back();
    }

    return nodes[node].child[c];
  }

  int update(const string &word, int delta) {
    int node = ROOT;
    for (char ch : word) {
      nodes[node].starting_with += delta;
      node = get_or_create_child(node, ch - MIN_CHAR);
    }
    nodes[node].starting_with += delta;
    return node;
  }

  int add(const string &word) {
    int node = update(word, +1);
    nodes[node].words_here++;
    return node;
  }

  int erase(const string &word) {
    int node = update(word, -1);
    nodes[node].words_here--;
    return node;
  }

  int find(const string &str) const {
    int node = ROOT;
    for (char ch : str) {
      node = nodes[node].child[ch - MIN_CHAR];
      if (node == 0)
        break;
    }
    return node;
  }

  // Given a string, how many words in the trie are prefixes of the string?
  int count_prefixes(const string &str, bool include_full) const {
    int node = ROOT, count = 0;
    for (char ch : str) {
      count += nodes[node].words_here;
      node = nodes[node].child[ch - MIN_CHAR];
      if (node == 0)
        break;
    }
    if (include_full && node > 0)
      count += nodes[node].words_here;
    return count;
  }

  // Given a string, how many words in the trie start with the given string?
  int count_starting_with(const string &str, bool include_full) const {
    int node = find(str);
    if (node == 0)
      return 0;
    return nodes[node].starting_with -
           (include_full ? 0 : nodes[node].words_here);
  }
  int query_xor(const string &str) const {
    int cur = ROOT;
    int ans = 0;
    for (char ch : str) {
      int f = ch - MIN_CHAR;
      ans <<= 1;
      if (nodes[cur].child[f ^ 1] &&
          nodes[nodes[cur].child[f ^ 1]].starting_with > 0) {
        cur = nodes[cur].child[f ^ 1];
        ans |= 1;
      } else {
        cur = nodes[cur].child[f];
      }
    }
    return ans;
  }
};