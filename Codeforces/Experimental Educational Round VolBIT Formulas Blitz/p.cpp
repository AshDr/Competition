#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
double n,r,S,a,b;
const double Pi=acos(-1.0);
int main(){
	scanf("%lf%lf",&n,&r);
	S=(r*r*sin(Pi/n)*sin(Pi/(2*n)))/(2*sin(Pi-Pi*3/2/n));
	printf("%.12lf\n",2*n*S);
	return 0;
}