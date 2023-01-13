#include "poly.h"
#include "matrix.h"
#include "euclid.h"
#include <fstream>
using namespace std;
Matrix<double> Lambda;
bool comp(double a,double b){
    return equals(a,b);
}
Matrix<double> diagonalize(Matrix<double> A){
    assert(A.row==A.col);
    // Matrix<poly<double> >B=Matrix<poly<double> >(A);
    // for (int i=1;i<=A.row;++i) B[i][i]=B[i][i]-poly<double>("x");
    // // cout<<B<<endl;
    // _poly<double> x=Determinant(B).x;
    // cout<<"特征多项式"<<x<<endl;
    // upoly<double> _x(x);
    // vector<double> sol=solve(_x);
    auto eig=EigenVals(A);
    sort(eig.begin(),eig.end(),greater<double>());
    eig.erase(unique(eig.begin(),eig.end(),comp),eig.end());
    vector<Matrix<double> >s;
    for (double lambda:eig){
        // cout<<lambda<<endl;
        // cout<<F(_x,lambda)<<endl;
        Matrix<double> B=A-lambda*Matrix<double>(A.row,A.col,1);
        // cout<<B<<endl;
        auto baseS=Schmidt(baseSolution(B));
        cout<<"size"<<baseS.size()<<endl;
        for (auto x:baseS) s.push_back(x);
    }
    if (s.size()==A.row){
        for (auto &x:s) x=identilize(x).first;
        Matrix<double> Q=addH(s);
        Lambda=(Q.transpose())*A*Q;
        return Q;
    }
    else{
        cout<<"矩阵不可相似对角化"<<endl;
        assert(0);
    }
}
int main(){
    Matrix<double> A;
    cin>>A;
    int m=A.row,n=A.col;
    vector<Matrix<double> >u;
    Matrix<double> V=diagonalize(A.transpose()*A);
    auto v=breakAsVector(V,'C');
    Matrix<double> Sigma=Lambda.resize(m,n);
    for (int i=1;i<=min(m,n);++i){
        if (!equals(Sigma[i][i],(double)(0))){
            Sigma[i][i]=sqrt(Sigma[i][i]);
            u.push_back(1/Sigma[i][i]*(A*v[i-1]));
        }
    }
    // std::cout<<baseSolution(addH(u).transpose()).size()<<std::endl;
    // std::cout<<addH(baseExpansion(u))<<std::endl;
    Matrix<double>U=addH(addH(u),addH(baseExpansion(u)));
    // U=diagonalize(A*A.transpose());
    V=V.transpose();
    cout<<U.message("U")<<endl;
    cout<<Sigma.message("Sigma")<<endl;
    cout<<V.message("V")<<endl;
    cout<<(U*Sigma*V).message("SVD")<<endl;
    int k=min(n,m);
    for (int i=1;i<=min(n,m);++i){
        if (equals(Sigma[i][i],(double)(0))){k=i-1;break;}
    }
    for (int j=k;j>=1;--j){
        U.resize(m,j);
        Sigma.resize(j,j);
        V.resize(j,n);
        cout<<U.message("New U")<<endl;
        cout<<Sigma.message("New Sigma")<<endl;
        cout<<V.message("New V")<<endl;
        cout<<(U*Sigma*V).message("SVD")<<endl;
        cout<<"舍弃第"<<j<<"个奇异值"<<Sigma[j][j]<<"，得到："<<endl;
    }
}
/*
1 0 0 0 0 0
1 0 1 1 0 0
1 1 1 0 0 1
1 1 1 0 0 0
1 1 1 1 1 0
1 0 0 0 0 0

svd {{1,0,0,0,0,0},{1,0,1,1,0,0},{1,1,1,0,0,1},{1,1,1,0,0,0},{1,1,1,1,1,0},{1,0,0,0,0,0}}

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1 1 1 1 0 0 0 1
1 0 1 0 0 1 1 1 1 1 0 0 1 0 0
1 0 0 0 0 0 1 1 1 1 0 1 1 1 0
1 0 0 1 1 0 0 1 1 0 0 1 1 1 1
1 0 0 1 1 1 0 1 1 0 1 1 1 1 1
1 0 0 1 1 1 0 1 1 0 1 1 1 1 0
1 0 1 1 1 1 0 1 1 0 1 1 1 0 0
1 0 1 1 1 1 0 1 1 1 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1 1 0 0 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/