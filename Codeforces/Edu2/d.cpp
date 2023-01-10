#include<bits/stdc++.h>
using namespace std;
#define PI acos(-1)
#define double long double
int main()
{
    int T;
    double x1,x2,y1,y2,r1,r2;
    double a,b,s1,s2,d,sum;
    // cin >> T;
    T=1;
    while(T--)
    {
        sum = 0;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        d = sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
        if(r1 + r2 <= d)
            puts("0.00");
        else if(r2 >= r1 && d + r1 <= r2)
        {   
            printf("%.6Lf\n", (r1 * r1 * PI) );
            
            
        } 
        else if(r1 >= r2 && d + r2 <= r1)
        {   
            printf("%.6Lf\n", (r2 * r2* PI) );
        }
        else
        {
            a = acos((r1 * r1 + d * d - r2 * r2) / r1 / d / 2); //弧度            
            s1 = r1 * r1 * a;
            s2 = r1 * r1 * sin(a) * cos(a); 
            sum += s1 - s2;
            
            a = acos((r2 * r2 + d * d - r1 * r1) / r2 / d / 2); //弧度            
            s1 = r2 * r2 * a;
            s2 = r2 * r2 * sin(a) * cos(a); 
            sum += s1 - s2;
            printf("%.6Lf\n", sum);
        }
        
    }
    // 1/2 * (2 * a) * r1 * r1 -  1/2 * r1 * r1 * sin(2 * a)
    return 0;
}