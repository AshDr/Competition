namespace FhqTreap {

  template <typename T>
  struct Node {
    T key;
    // define info
    Node *left, *right;
    int size, priority;
    Node():left(nullptr),right(nullptr){}
    Node(T key, int pri)
        : key(key), left(nullptr), right(nullptr), size(1), priority(pri) {} // init info
    ~Node() {
      if (left)
        delete left;
      if (right)
        delete right;
    
    }
  };
  template <typename T>
  Node<T> *create(T key) {
    Node<T> *root = new Node(key, random());
    return root;
  }
  template <typename T>
  void pushup(Node<T> *root) {
    if (root) {
      root->size = (root->left ? root->left->size : 0) +
                   (root->right ? root->right->size : 0) + 1;
      // merge info, mayeb not merge root->info
    }
      
  }
  template <typename T>
  void split1(Node<T> *root, T key, Node<T> *&x, Node<T> *&y) {
    if (root == nullptr) {
      x = y = nullptr;
      return;
    }
    if (root->key < key) {
      x = root;
      split1(root->right, key, root->right, y);
    } else {
      y = root;
      split1(root->left, key, x, root->left);
    }
    pushup(root);
  }
  template <typename T>
  void split2(Node<T> *root, T key, Node<T> *&x, Node<T> *&y) {
    if (root == nullptr) {
      x = y = nullptr;
      return;
    }
    if (!(key < root->key)) {
      x = root;
      split2(root->right, key, root->right, y);
    } else {
      y = root;
      split2(root->left, key, x, root->left);
    }
    pushup(root);
  }
  template <typename T>
  Node<T> *merge(Node<T> *x, Node<T> *y) {
    if (x == nullptr)
      return y;
    if (y == nullptr)
      return x;
    if (x->priority > y->priority) {
      x->right = merge(x->right, y);
      pushup(x);
      return x;
    } else {
      y->left = merge(x, y->left);
      pushup(y);
      return y;
    }
  }
  template <typename T> struct FhqTreap {
  public:
    FhqTreap(int seed = 0) {
      this->seed = seed;
      root = nullptr;
    }
  
    ~FhqTreap() {
      if (root)
        delete root;
    }
    Node<T> *root;
    int seed;
  
    int random() { return seed = int((seed + 3) * 482711ll % 2147483647); }
  
    void insert(T key) {
      Node<T> *x, *y;
      split1(root, key, x, y);
      root = merge(merge(x, create(key)), y);
    }
  
    void remove(T key) {
      Node<T> *x, *y, *z;
      split2(root, key, x, z);
      split1(x, key, x, y);
      if (y) {
        y = merge(y->left, y->right);
      }
      root = merge(merge(x, y), z);
    }
  
    int rank(T key) {
      Node<T> *x, *y;
      int ans;
      split1(root, key, x, y);
      ans = (x ? x->size : 0) + 1;
      root = merge(x, y);
      return ans;
    }
  
    T at(int r) {
      if (root == nullptr || r > root->size)
        return T();
      Node<T> *root = root;
      while (root) {
        int ls = root->left ? root->left->size : 0;
        if (ls + 1 == r) {
          break;
        } else if (ls + 1 > r) {
          root = root->left;
        } else {
          r -= ls + 1;
          root = root->right;
        }
      }
      return root->key;
    }
  
    T previous(T key) {
      Node<T> *x, *y, *root;
      T ans;
      split1(root, key, x, y);
      root = x;
      if (root == nullptr)
        return std::numeric_limits<T>::min();
      while (root->right)
        root = root->right;
      ans = root->key;
      root = merge(x, y);
      return ans;
    }
  
    T next(T key) {
      Node<T> *x, *y, *root;
      T ans;
      split2(root, key, x, y);
      root = y;
      if (root == nullptr)
        return std::numeric_limits<T>::max();
      while (root->left)
        root = root->left;
      ans = root->key;
      root = merge(x, y);
      return ans;
    }
  
    int size() { return (root ? root->size : 0); }
  
    bool find(T key) {
      Node<T> *x, *y, *z;
      split2(root, key, x, z);
      split1(x, key, x, y);
      bool ans;
      if (y)
        ans = true;
      else
        ans = false;
      root = merge(merge(x, y), z);
      return ans;
    }
  };
  } // namespace FhqTreap