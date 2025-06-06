// 除法很慢，尽量少做除法
class BigInt {
#define Value(x, nega) ((nega) ? -(x) : (x))
#define At(vec, index) ((index) < vec.size() ? vec[(index)] : 0)
  // C风格的比较函数,其正负等于abs(lhs)-abs(rhs)的正负
  static int absComp(const BigInt &lhs, const BigInt &rhs) {
    if (lhs.size() != rhs.size()) return lhs.size() < rhs.size() ? -1 : 1;
    for (int i = lhs.size() - 1; i >= 0; --i)
      if (lhs[i] != rhs[i]) return lhs[i] < rhs[i] ? -1 : 1;
    return 0;
  }
  using Long = long long;
  const static int Exp = 9;  // 压9位
  const static Long Mod = 1000000000;
  mutable std::vector<Long> val;
  mutable bool nega = false;
  // 规定:0的nega必须是false,0的size必须是0
  void trim() const {
    while (val.size() && val.back() == 0) val.pop_back();
    if (val.empty()) nega = false;
  }
  int size() const { return val.size(); }
  Long &operator[](int index) const { return val[index]; }
  Long &back() const { return val.back(); }
  BigInt(int size, bool nega) : val(size), nega(nega) {}
  BigInt(const std::vector<Long> &val, bool nega) : val(val), nega(nega) {}

 public:
  friend std::ostream &operator<<(std::ostream &os, const BigInt &n) {
    if (n.size()) {
      if (n.nega) cout<<"-";
      for (int i = n.size() - 1; i >= 0; --i) {
        if (i == n.size() - 1)
          cout<<n[i];
        else
          cout << std::setfill('0') << std::setw(n.Exp) << n[i];
      }
    } else
      cout<<'0';
    return os;
  }
  friend BigInt operator+(const BigInt &lhs, const BigInt &rhs) {
    BigInt ret(lhs);
    return ret += rhs;
  }
  friend BigInt operator-(const BigInt &lhs, const BigInt &rhs) {
    BigInt ret(lhs);
    return ret -= rhs;
  }
  BigInt(Long x = 0) {
    if (x < 0) x = -x, nega = true;
    while (x >= Mod) val.push_back(x % Mod), x /= Mod;
    if (x) val.push_back(x);
  }
  BigInt(const char *s) {
    int bound = 0, pos;
    if (s[0] == '-') nega = true, bound = 1;
    Long cur = 0, pow = 1;
    for (pos = strlen(s) - 1; pos >= Exp + bound - 1; pos -= Exp, val.push_back(cur), cur = 0, pow = 1)
      for (int i = pos; i > pos - Exp; --i) cur += (s[i] - '0') * pow, pow *= 10;
    for (cur = 0, pow = 1; pos >= bound; --pos) cur += (s[pos] - '0') * pow, pow *= 10;
    if (cur) val.push_back(cur);
  }
  BigInt &operator+=(const BigInt &rhs) {
    const int cap = std::max(size(), rhs.size()) + 1;
    val.resize(cap);
    int carry = 0;
    for (int i = 0; i < cap - 1; ++i) {
      val[i] = Value(val[i], nega) + Value(At(rhs, i), rhs.nega) + carry, carry = 0;
      if (val[i] >= Mod)
        val[i] -= Mod, carry = 1;  // 至多只需要减一次，不需要取模
      else if (val[i] < 0)
        val[i] += Mod, carry = -1;  // 同理
    }
    if ((val.back() = carry) == -1)  // assert(val.back() == 1 or 0 or -1)
    {
      nega = true, val.pop_back();
      bool tailZero = true;
      for (int i = 0; i < cap - 1; ++i) {
        if (tailZero && val[i])
          val[i] = Mod - val[i], tailZero = false;
        else
          val[i] = Mod - 1 - val[i];
      }
    }
    trim();
    return *this;
  }
  friend BigInt operator-(const BigInt &rhs) {
    BigInt ret(rhs);
    ret.nega ^= 1;
    return ret;
  }
  BigInt &operator-=(const BigInt &rhs) {
    rhs.nega ^= 1;
    *this += rhs;
    rhs.nega ^= 1;
    return *this;
  }
  // 高精*高精没办法原地操作，所以实现operator*
  // 高精*低精可以原地操作，所以operator*=
  friend BigInt operator*(const BigInt &lhs, const BigInt &rhs) {
    const int cap = lhs.size() + rhs.size() + 1;
    BigInt ret(cap, lhs.nega ^ rhs.nega);
    // j < l.size(),i - j < rhs.size() => i - rhs.size() + 1 <= j
    for (int i = 0; i < cap - 1; ++i)  // assert(0 <= ret[cap-1] < Mod)
      for (int j = std::max(i - rhs.size() + 1, 0), up = std::min(i + 1, lhs.size()); j < up; ++j) {
        ret[i] += lhs[j] * rhs[i - j];
        ret[i + 1] += ret[i] / Mod, ret[i] %= Mod;
      }
    ret.trim();
    return ret;
  }
  BigInt &operator*=(const BigInt &rhs) { return *this = *this * rhs; }
  friend BigInt operator/(const BigInt &lhs, const BigInt &rhs) {
    static std::vector<BigInt> powTwo{BigInt(1)};
    static std::vector<BigInt> estimate;
    estimate.clear();
    if (absComp(lhs, rhs) < 0) return BigInt();
    BigInt cur = rhs;
    int cmp;
    while ((cmp = absComp(cur, lhs)) <= 0) {
      estimate.push_back(cur), cur += cur;
      if (estimate.size() >= powTwo.size()) powTwo.push_back(powTwo.back() + powTwo.back());
    }
    if (cmp == 0) return BigInt(powTwo.back().val, lhs.nega ^ rhs.nega);
    BigInt ret = powTwo[estimate.size() - 1];
    cur = estimate[estimate.size() - 1];
    for (int i = estimate.size() - 1; i >= 0 && cmp != 0; --i)
      if ((cmp = absComp(cur + estimate[i], lhs)) <= 0) cur += estimate[i], ret += powTwo[i];
    ret.nega = lhs.nega ^ rhs.nega;
    return ret;
  }
  bool operator==(const BigInt &rhs) const { return nega == rhs.nega && val == rhs.val; }
  bool operator!=(const BigInt &rhs) const { return nega != rhs.nega || val != rhs.val; }
  bool operator>=(const BigInt &rhs) const { return !(*this < rhs); }
  bool operator>(const BigInt &rhs) const { return !(*this <= rhs); }
  bool operator<=(const BigInt &rhs) const {
    if (nega && !rhs.nega) return true;
    if (!nega && rhs.nega) return false;
    int cmp = absComp(*this, rhs);
    return nega ? cmp >= 0 : cmp <= 0;
  }
  bool operator<(const BigInt &rhs) const {
    if (nega && !rhs.nega) return true;
    if (!nega && rhs.nega) return false;
    return (absComp(*this, rhs) < 0) ^ nega;
  }
  void swap(const BigInt &rhs) const {
    std::swap(val, rhs.val);
    std::swap(nega, rhs.nega);
  }
};