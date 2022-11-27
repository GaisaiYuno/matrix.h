#define Num poly
#include "poly.h"
#include "matrix.h"
using namespace std;
int main(){
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