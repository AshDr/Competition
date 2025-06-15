// 这里按照sz分裂蕴含啦对idx的偏序
struct node {
  // define info
  ull val, hsh;
  int rd;
  int siz, ch[2];
  int lz;
} fhq[N];
int cnt = 0;
int root;
int newnode(ull val) {
  ++cnt;
  fhq[cnt].val = fhq[cnt].hsh = val;
  fhq[cnt].siz = 1;
  fhq[cnt].ch[0] = fhq[cnt].ch[1] = 0;
  fhq[cnt].rd = rand();
  return cnt;
}
#define ls fhq[cur].ch[0]
#define rs fhq[cur].ch[1]
void push_up(int cur) {
  fhq[cur].siz = fhq[ls].siz + fhq[rs].siz + 1;
  fhq[cur].hsh = (ls ? fhq[ls].hsh : 0) + pw[fhq[ls].siz] * fhq[cur].val + (rs ? fhq[rs].hsh * pw[fhq[ls].siz + 1] : 0);
}
void push_down(int cur) {
  // 下传标记
}
// 分裂以cur为根的树，分为集合：前lim个 、剩余sz-lim个 这里偏序是对index来说的
// 整颗树的前序遍历就是1～n序列的输出
void split(int cur, int limit, int &x, int &y) {
  if (!cur) {
    x = 0;
    y = 0;
    return;
  } else {
    int lsz = fhq[fhq[cur].ch[0]].siz;
    // push_down
    if(fhq[cur].lz) push_down(cur);
    if (limit <= lsz) {
      y = cur;
      split(fhq[cur].ch[0], limit, x, fhq[y].ch[0]);
    } else {
      x = cur;
      split(fhq[cur].ch[1], limit - lsz - 1, fhq[x].ch[1], y);
    }
    push_up(cur);
  }
}
void split_by_val(int cur, int val, int &x, int &y){
  if (!cur) {
    x = 0;
    y = 0;
    return;
  } else {
    // push_down
    if(fhq[cur].lz) push_down(cur);
    if (fhq[cur].val <= val) {
      x = cur;
      split_by_val(fhq[cur].ch[1], val, fhq[x].ch[1], y);
    } else {
      y = cur;
      split_by_val(fhq[cur].ch[0], val, x, fhq[y].ch[0]);
    }
    push_up(cur);
  }
}

int merge(int x, int y) {
  if (!x || !y) return x + y;
  if (fhq[x].rd <= fhq[y].rd) {
    // push_down
    if(fhq[x].lz) push_down(x);
    fhq[x].ch[1] = merge(fhq[x].ch[1], y);
    push_up(x);
    return x;
  } else {
    // push_down
    if(fhq[y].lz) push_down(y);
    fhq[y].ch[0] = merge(x, fhq[y].ch[0]);
    push_up(y);
    return y;
  }
}
void insert(int pos, int val) {
  int t1, t2;
  split(root, pos - 1, t1, t2);
  root = merge(t1, merge(newnode(val), t2));
}
void update(int pos, int val) {
  int t1, t2, t3;
  split(root, pos - 1, t1, t2);
  split(t2, 1, t2, t3);
  fhq[t2].val = fhq[t2].hsh = val;
  root = merge(t1, (merge(t2, t3)));
}
ull query(int pos, int len) {
  int t1, t2, t3;
  split(root, pos - 1, t1, t2);
  split(t2, len, t2, t3);
  ull ret = fhq[t2].hsh;
  root = merge(t1, merge(t2, t3));
  return ret;
}
void del(int pos) {
  int t1,t2,t3;
  split(root,pos-1,t1,t2);
  split(t2,1,t2,t3);
  root=merge(t1,merge(merge(fhq[t2].ch[0],fhq[t2].ch[1]),t3)); 
  // merge fhq[t2].ch[0],fhq[t2].ch[1] 是因为如果是对值偏序的话，有重复值的情况
}