#include<bits/stdc++.h>
using namespace std;
const int N=5e3;

int a[N][N],b[N][N];
int h[N];
int que[N];
void solve()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
            b[i][j]=0;
            if(i>1){
                b[i][j]=(a[i][j]>=a[i-1][j]);
            }
        }
    }
    for(int i=1;i<=m;i++){
        h[i]=0;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(b[i][j]==0){
                h[j]=1;
            }else{
                h[j]++;
            }
        }
        int tot=0;
        h[m+1]=0;
        for(int j=1;j<=m+1;j++){
            while(tot&&h[que[tot]]>h[j]){
                ans=max(ans,(j-que[tot-1]-1)*h[que[tot]]);
                //printf("%d %d %d\n",j,que[tot-1],h[que[tot]]);
                tot--;
            }
            que[++tot]=j;
        }
    }
    printf("%d\n",ans);
}
int main()
{
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--){
        solve();
    }
}
//int a[N][N];
// int h[N],lb[N][N],rb[N][N];
// void solve() {
//     cin>>n>>m;
//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= m; j++) {
//             cin>>a[i][j];
//         }
//     }
//     int ans1 = 0,ans2 = 0;
//     for(int i = 1; i <= n; i++) {
//         lb[i][1] = 1;
//         for(int j = 2; j <= m; j++) {
//             if(a[i][j] != a[i][j - 1]) lb[i][j] = lb[i][j - 1];
//             else lb[i][j] = j;
//         }
//     }
//     for(int i = 1; i <= n; i++) {
//         rb[i][m] = m;
//         for(int j = m - 1; j >= 1; j--) {
//             if(a[i][j] != a[i][j + 1]) rb[i][j] = rb[i][j + 1];
//             else rb[i][j] = j;
//         }
//     }
//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= m; j++) {
//             if(i == 1) h[j] = 1;
//             else {
//                 if(a[i][j] != a[i - 1][j]) {
//                     h[j]++;
//                     lb[i][j] = max(lb[i][j],lb[i - 1][j]);
//                     rb[i][j] = min(rb[i][j],rb[i - 1][j]);
//                 }
//                 else h[j] = 1;
//             }
//             int w = rb[i][j] - lb[i][j] + 1;
//             int t = min(w,h[j]);
//             ans1 = max(ans1,t * t);
//             ans2 = max(ans2,w * h[j]);
//         }
//     }
//     cout<<ans1<<endl<<ans2<<endl;
// }