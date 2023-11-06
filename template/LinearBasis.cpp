//https://oi.men.ci/linear-basis-notes/
//不显式构造出集合 支持动态插入。
const int MAXL = 63;
struct LinearBasis
{
    long long a[MAXL + 1];

    LinearBasis()
    {
        std::fill(a, a + MAXL + 1, 0);
    }

    LinearBasis(long long *x, int n)
    {
        build(x, n);
    }

    bool insert(long long t)
    {
        for (int j = MAXL; j >= 0; j--)
        {
            if (!t) return false;
            if (!(t & (1ll << j))) continue;

            if (a[j]) t ^= a[j];
            else
            {
                for (int k = 0; k < j; k++) if (t & (1ll << k)) t ^= a[k];
                for (int k = j + 1; k <= MAXL; k++) if (a[k] & (1ll << j)) a[k] ^= t;
                a[j] = t;
                return true;
                break;
            }
        }
        return false;
    }

    // 数组 x 表示集合 S，下标范围 [1...n]
    void build(long long *x, int n)
    {
        std::fill(a, a + MAXL + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            insert(x[i]);
        }
    }

    long long queryMax()
    {
        long long res = 0;
        for (int i = 0; i <= MAXL; i++) res ^= a[i];
        return res;
    }
    void mergeFrom(const LinearBasis &other)
    {
        for (int i = 0; i <= MAXL; i++) insert(other.a[i]);
    }

    static LinearBasis merge(const LinearBasis &a, const LinearBasis &b)
    {
        LinearBasis res = a;
        for (int i = 0; i <= MAXL; i++) res.insert(b.a[i]);
        return res;
    }
}linbis;


//显式构造出集合，不支持动态插入。
struct LinearBasis
{
    std::vector<long long> v;
    int n; // 原有集合 S 的大小

    // 数组 x 表示集合 S，下标范围 [1...n]
    void build(long long *x, int n)
    {
        this->n = n;
        std::vector<long long> a(MAXL + 1);

        for (int i = 1; i <= n; i++)
        {
            long long t = x[i];

            for (int j = MAXL; j >= 0; j--)
            {
                if ((t & (1ll << j)) == 0) continue;

                if (a[j]) t ^= a[j];
                else
                {
                    for (int k = 0; k < j; k++) if (t & (1ll << k)) t ^= a[k];
                    for (int k = j + 1; k <= MAXL; k++) if (a[k] & (1ll << j)) a[k] ^= t;

                    a[j] = t;
                    break;
                }
            }
        }

        v.clear();
        for (int i = 0; i <= MAXL; i++) if (a[i]) v.push_back(a[i]);
    }

    long long queryMax()
    {
        long long x = 0;
        for (size_t i = 0; i < v.size(); i++) x ^= v[i];
        return x;
    }
}linbis;