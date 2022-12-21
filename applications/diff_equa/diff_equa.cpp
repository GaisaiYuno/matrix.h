#include "poly.h"
#include "fraction.h"
#define Num frac
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
    for (int i=1;i<=sz;++i){
        if (g[i][1]!=0){
            g=g/g[i][1];
            break;
        }
    }
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
    Matrix f=Matrix(sz,sz,1);
    // Matrix r=upoly("x")*Deriv(Deriv(f))+Deriv(f);
    // upoly g=upoly("4x");
    Matrix r=Deriv(Deriv(f))+f;
    upoly g=Tan("x");
    // cout<<r<<endl;
    vector<Matrix>baseS=baseSolution(r.resize(sz-rk,sz),toVector(g).resize(sz-rk,1));
    for (int i=0;i<baseS.size()-1;++i){
        cout<<"C"<<i<<" * ";
        cout<<toUpoly(baseS[i])<<endl;
    }
    cout<<toUpoly(baseS.back())<<endl;
}