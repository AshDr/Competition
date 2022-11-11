#include<bits/stdc++.h>
//#define cerr cout<<"case#:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
const int N = 200;
const int M = 1e5 + 10;
const int INF = 2147483647;
const int MOD = 1e9;
int T,n,m;
char s[N][N];
int id[N][N];
int lapls[N][N];
void add(int x, int y) {
    lapls[x][x]++;
    lapls[y][y]++;
    lapls[x][y]--;
    lapls[y][x]--;
}
void solve() {
    cin>>n>>m;
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin>>s[i][j];
            if(s[i][j] == '.') id[i][j] = ++cnt;
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(s[i][j]=='.' && s[i+1][j]=='.') add(id[i][j],id[i+1][j]);
            if(s[i][j]=='.' && s[i][j+1]=='.') add(id[i][j],id[i][j+1]);
        }
    }

    --cnt;// 对lplas矩阵的一个子矩阵进行行列式求值

    int sign = 1;
    for(int i = 1; i <= cnt; i++) {
        for(int j = i + 1; j <= cnt; j++) {
            while(lapls[i][i]) {
                int div = lapls[j][i] / lapls[i][i];
                //debug(div);
                for(int k = i; k <= cnt; k++) lapls[j][k] = (lapls[j][k] - div*1ll*lapls[i][k]%MOD + MOD) % MOD;
                swap(lapls[i],lapls[j]);sign = -sign;
            }
            swap(lapls[i],lapls[j]);sign = -sign;
        }
    } 
    LL res = 1;
    for(int i = 1; i <= cnt; i++) res = res * lapls[i][i] % MOD;
    res = res * sign;
    cout<<(res%MOD + MOD) % MOD<<'\n';

}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    //cin>>T;
    T = 1;
    while(T--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}