#define Num frac
#include "fraction.h"
#include "matrix.h"
using namespace std;
int main(){
    Matrix M(3,3);//初始化3x3矩阵
    M[1][1]=frac("1"),M[1][2]=frac("2"),M[1][3]=frac("1/2");
    M[2][1]=frac("2"),M[2][2]=frac("4"),M[2][3]=frac("-1/4");
    M[3][1]=frac("2"),M[3][2]=frac("4"),M[3][3]=frac("1");
    cout<<M<<endl<<M.transpose()<<endl;//输出M及转置
    // cout<<(M^-1)<<endl;
    cout<<tr(M)<<endl;//矩阵的迹
    cout<<Gauss(M)<<endl;
    cout<<Gauss(M,true)<<endl;
    vector<Matrix>baseS=baseSolution(M);//齐次线性方程组的基础解系
    for (int i=0;i<baseS.size();++i) cout<<baseS[i]<<endl;
    baseS=baseSolution(M,vector<Num>{(Num)(1),(Num)(2),(Num)(3)});//非齐次线性方程组的基础解系
    for (int i=0;i<baseS.size();++i) cout<<baseS[i]<<endl;
    M[3][1]=frac("3");
    cout<<M<<endl;
    cout<<Determinant(M)<<endl;//行列式
    cout<<Inverse(M)<<endl;//逆矩阵
    cout<<rk(M)<<endl;//矩阵的秩
    Matrix N(3,3,1);//单位矩阵
    cout<<N<<endl;
    N.diag(vector<Num>{1,2,3});//对角阵
    cout<<N<<endl;
    cout<<M*N<<endl;//矩阵乘法
    cout<<(M^4)<<endl;//矩阵快速幂
}