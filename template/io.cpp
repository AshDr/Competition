namespace IO {
    template <typename T>
    inline void read(T &x) {
        T w=1;x=0;
        char ch = getchar();
        while(!isdigit(ch)) {if(ch=='-') w=-1; ch=getchar();}
        while(isdigit(ch)) {x=(x*10+ch-'0') % MOD;ch=getchar();}
        x *= w;
    }
    template <typename T>
    inline void write (T &x){
        if(x<0)
            putchar('-'),x=-x;
        if(x>9) {
            write(x/10);
            putchar(x%10+'0');
        }
        return;
    } 
}
namespace IO{
    const int SIZE=1<<22;
    char a[SIZE],b[SIZE],*ia=a+SIZE,*ea=a+SIZE,*ib=b,*eb=b+SIZE;
    int num[105],lgt=0;
    inline char gc(){if (ia==ea) fread(a,1,SIZE,stdin),ia=a;return *ia++;}
    void flush(){fwrite(b,1,ib-b,stdout);ib=b;}
    inline void pc(char x){if (ib==eb) flush();*ib++=x;}
    struct F{~F(){flush();}}f;
    inline int read(){
        int x=0;char t=gc();
        for (;t<'0' || t>'9';t=gc());
        for (;'0'<=t && t<='9';t=gc()) x=x*10+t-'0';
        return x;
    }
    inline void write(int x,char ed='\n'){
        if (!x) pc('0');
        for (;x;x/=10) num[++lgt]=x%10;
        for (;lgt;--lgt) pc(num[lgt]+'0');
        pc(ed);
    }
}
using IO::read;
using IO::write;