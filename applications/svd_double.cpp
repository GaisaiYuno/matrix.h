#include "poly.h"
#include "matrix.h"
#include "euclid.h"
#include <fstream>
using namespace std;
int main(){
    Matrix<long double> A;
    cin>>A;
    Matrix<long double>U,Sigma,V;
    tie(U,Sigma,V)=svd(A);
    cout<<U.message("U")<<endl;
    cout<<Sigma.message("Sigma")<<endl;
    cout<<V.message("V")<<endl;
    cout<<(U*Sigma*V).message("SVD")<<endl;
    int n=A.row,m=A.col;
    int k=min(n,m);
    for (int i=1;i<=min(n,m);++i){
        if (equals(Sigma[i][i],(long double)(0))){k=i-1;break;}
    }
    for (int j=k;j>=1;--j){
        U.resize(n,j);
        Sigma.resize(j,j);
        V.resize(j,m);
        cout<<U.message("New U")<<endl;
        cout<<Sigma.message("New Sigma")<<endl;
        cout<<V.message("New V")<<endl;
        cout<<(U*Sigma*V).message("SVD")<<endl;
        cout<<"舍弃第"<<j<<"个奇异值"<<Sigma[j][j]<<"，得到："<<endl;
    }
}