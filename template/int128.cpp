void input(__int128 &x) {
    int f=1;char ch = getchar();
    x=0;
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x = x*10+ch-'0';ch=getchar();}
    x = f*x;
    return ;
}
void output(__int128 x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) output(x/10);
    putchar(x%10 + '0');
    return ;
}