#define Num frac
#include "fraction.h"
#include "matrix.h"
using namespace std;
int main(){
    Matrix M;
    cin>>M;
    vector<Matrix>baseS=baseSolution(M);//齐次线性方程组的基础解系
    for (int i=0;i<baseS.size();++i) cout<<baseS[i]<<endl;
    // baseS=baseSolution(M,vector<Num>{(Num)(7),(Num)(15),(Num)(22)});//非齐次线性方程组的基础解系
    // for (int i=0;i<baseS.size();++i) cout<<baseS[i]<<endl;
}
/*
1 1 2 1 2
1 2 3 4 5
2 3 5 5 7
*/