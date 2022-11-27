#define Num poly
#include "poly.h"
#include "matrix.h"
// #include "euclid.h"
using namespace std;
int main(){
    Matrix M;
    cin>>M;
    M=M.transpose();
    cout<<Gauss(M);
    vector<Matrix>baseS=baseSolution(M);
    for (int i=0;i<baseS.size();++i){
        cout<<baseS[i]<<endl;
    }
}
/*
输入：
3 4
k 1 1 1
1 k 1 k
1 1 k k^2
输入
4 3
1 2 -1
2 1 k
3 -1 0
4 1 2

输入 
3 2 4
1 -2 0
x^3+x^2+x+1
0x^3+3x^2+2x^1+1x^0+0
[0 0 0 0]
[1 0 0 0]
[0 2 0 0]
[0 0 3 0]

[1 0 1] ^T
[-1 2 0]
[1 0 -1]
CB=AC

[e1,en]C=[i1,in]

(i1,in)B=(e1,en)AC
[e1,en]CB=(e1,en)AC
CB=AC
*/