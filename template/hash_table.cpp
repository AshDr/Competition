struct HashTable{
    int head[262144] , pre[7005] , siz[7005] , que[7005] , fr , ba , tp ;
    long long val[7005] ;
    void init(){ fr = 1 , tp = ba = 0 ; }
    void Insert( long long h ){
        int id = h&262143 , t ;
        for( int i = head[id] ; i ; i = pre[i] )
            if( val[i] == h ){
                ans += siz[i] , siz[i] ++ ;
                return ;
            }
        if( ba != ( fr - 1 + 7005 )%7005 )t = que[fr] , fr = ( fr == 7004 ? 0 : fr + 1 );//有被回收的空间就用
        else t = ++tp ;
        pre[t] = head[id] , head[id] = t ;
        val[t] = h , siz[t] = 1 ;
    }
    void Erase( long long h ){
        int id = h&262143 ;
        for( int i = head[id] , las = -1 ; i ; las = i , i = pre[i] ){
            if( val[i] == h ){
                siz[i] -- , ans -= siz[i] ;
                if( !siz[i] ){
                    ba = ( ba == 7004 ? 0 : ba + 1 ) , que[ba] = i ; //回收空间i
                    if( las != -1 ) pre[las] = pre[i] ;
                    else head[id] = pre[i] ;
                } return ;
            }
        }
    }
} Hs ;//must init!