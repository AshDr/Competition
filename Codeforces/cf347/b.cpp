/*
  ID:Agreement
  LANG:C++
*/
// Invincible
#include <bits/stdc++.h>
#define rep( i , l , r ) for( int i = (l) ; i <= (r) ; i++ )
#define per( i , r , l ) for( int i = (r) ; i >= (l) ; i-- )
using namespace std;
const int maxn = 100 + 5;
const int INF = 1e9 + 7;

char str[maxn] , sig[maxn];
int val[maxn] , p1 , p2 ;
int N = 0;
vector<int> ans;
int main(){
    p1 = p2 = 0;
    sig[p1 ++ ] = '+';
    while( scanf("%s" , str) == 1 && str[0] != '=' )
        if( str[0] != '?' ) sig[ p1 ++ ] = str[0]; 
    
    sig[p1] = '\0';
    scanf( "%d" , &N );
    int Min = 0 , Max = 0 ;
    rep( i , 0 , p1 - 1 ){
        if( sig[i] == '+' ) Min++ , Max += N , ans.push_back(1);
        else Min -= N , Max -= 1 , ans.push_back(N); 
    }
    if( N >= Min && N <= Max ){
        int d = N - Min;
        rep( i , 0 , p1 - 1 ){
            if( sig[i] == '+' ){
                if( d >= N - 1 ) ans[i] = N , d -= (N - 1);
                else ans[i] += d , d = 0; 
            }else{
                if( d >= N - 1 ) ans[i] = 1 , d -= (N - 1);
                else ans[i] -= d ,  d = 0;
            }
            if( d == 0 ) break;
        }
        puts("Possible");
        rep( i , 0 , p1 - 2 ){
            printf("%d %c " , ans[i] , sig[i + 1]);
        }
        printf( "%d = %d\n" , ans[p1 - 1] , N );
    }else puts("Impossible");
    return 0;
}


