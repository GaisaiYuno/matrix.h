#define Num poly
#include "poly.h"
#include "matrix.h"
using namespace std;
int main(){
    // cout<<poly("1-12a^2+45a^4+10a^3-66a^5-48a^6+132a^7-21a^8-100a^9+60a^10+18a^11-25a^12+6a^13|1-6a^2+12a^4+2a^3-6a^5-10a^6+6a^7+3a^8-2a^9")-poly("1-13a^2+57a^4+10a^3-76a^5-93a^6+198a^7+27a^8-232a^9+81a^10+118a^11-85a^12-12a^13+25a^14-6a^15|1-7a^2+18a^4+2a^3-8a^5-22a^6+12a^7+13a^8-8a^9-3a^10+2a^11")<<endl;
    Matrix A;
    cin>>A;
    cout<<Determinant(A)<<endl;
}
/*
0 x y z
x 0 z y
y z 0 x
z y x 0
ans=-2y^2z^2+x^4-2x^2y^2-2x^2z^2+z^4+y^4

x -1 0 0
0 x -1 0
0 0 x -1
a b c d+x
ans=dx^3+x^4+cx^2+bx+a

1 a a a
a 1 a a
a a 1 a
a a a 1

1-11a^2+34a^4+10a^3-56a^5+76a^7-35a^8-14a^6-24a^9+25a^10-6a^11|1-5a^2+7a^4+2a^3-4a^5-3a^6+2a^7
答案应该是 - 3*a^4 + 8*a^3 - 6*a^2 + 1
这已经是比较简化的形式了，看看之后用单元多项式分解乱搞吧
如果是用类似于整项+余项的方式存储是不是会好一点……
*/