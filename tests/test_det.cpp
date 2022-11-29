#define Num poly
#include "poly.h"
#include "matrix.h"
using namespace std;
int main(){
    Matrix A;
    cin>>A;
    // cout<<A<<endl;
    // cout<<Gauss(A)<<endl;
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

k 1 1 1
1 k 1 k
1 1 k k^2

a 1 1 4
1 b 1 3
1 2b 1 4

1 0 0 1/32a^2b^3-1/16ab^2+1/32b-1/64a^2b^2+1/32ab-1/64|-1/64a^2b^3+1/32ab^2+1/64a^3b^3-1/32a^2b^2-1/64b+1/64ab 
0 1 0 -1/64a^2b^2+1/32ab+1/32a^3b^2-1/16a^2b-1/64+1/32a-1/64a^4b^2+1/32a^3b-1/64a^2|-1/64a^2b^3+1/32ab^2+1/32a^3b^3-1/16a^2b^2-1/64a^4b^3+1/32a^3b^2-1/64b+1/32ab-1/64a^2b 
0 0 1 1/4ab^2-1/8a^2b^2+1/16ab-1/4b+1/16|1/16ab^2-1/16b-1/16a^2b^2+1/16ab


a-l b
c d-l
l^2-(a+d)l+ad-bc

8/10-l 3/10
2/10 7/10-l
1/2-3/2l+l^2
1-3l+2l^2=0
(2l-1)(l-1)=0
l=1/2,1

2,4
不同的特征值对应的特征向量，是线性无关的 
*/