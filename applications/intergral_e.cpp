#include "poly.h"
#include "fraction.h"
#define Num sqrtNum
#undef POLY_H
#include "matrix.h"
using namespace std;
Matrix D(int n){
    Matrix D(n,n);
    for (int i=1;i<=n-1;++i){
        D[i][i+1]=i;
    }
    return D;
}
Matrix Deriv(Matrix M){
    return D(M.row)*M;
}
Matrix S(int n,int shift){
    Matrix S(n,n);
    for (int i=1;shift+i<=n;++i){
        S[shift+i][i]=1;
    }
    return S;
}
Matrix Shift(Matrix M,int shift){
    return S(M.row,shift)*M;
}
const int sz=10;
Matrix toVector(upoly g){
    Matrix ret=Matrix(sz,1);
    for (int i=0;i<g.v.size() && i<sz;++i) ret[i+1][1]=g[i];
    return ret;
}
upoly toUpoly(Matrix g){
    upoly ret;
    ret.v.resize(sz+1);
    for (int i=1;i<=sz;++i) ret.v[i-1]=g[i][1];
    return ret;
}
Matrix operator * (Matrix M,upoly u){
    Matrix ret=Matrix(M.row,M.col);
    for (int i=0;i<u.v.size();++i) ret=ret+u.v[i]*Shift(M,i);
    return ret;
}
Matrix operator * (upoly u,Matrix M){return M*u;}
int main(){
    int rk=2;
    Matrix F=Matrix(sz,sz,1);
    upoly g=upoly("1+x"),f=upoly("x"),phi=upoly("x");
    Matrix M=g*Deriv(phi)*F+g*Deriv(F)-Deriv(g)*F;
    vector<Matrix>baseS=baseSolution(M,toVector(f));
    cout<<toUpoly(baseS.back())<<"|"<<g<<" e^"<<phi<<endl;
}