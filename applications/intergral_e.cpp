#include "poly.h"
#include "fraction.h"
#include "matrix.h"
using namespace std;
Matrix<frac> D(int n){
    Matrix<frac> D(n,n);
    for (int i=1;i<=n-1;++i){
        D[i][i+1]=i;
    }
    return D;
}
Matrix<frac> Deriv(Matrix<frac> M){
    return D(M.row)*M;
}
Matrix<frac> S(int n,int shift){
    Matrix<frac> S(n,n);
    for (int i=1;shift+i<=n;++i){
        S[shift+i][i]=1;
    }
    return S;
}
Matrix<frac> Shift(Matrix<frac> M,int shift){
    return S(M.row,shift)*M;
}
const int sz=10;
Matrix<frac> toVector(upoly g){
    Matrix<frac> ret=Matrix<frac>(sz,1);
    for (int i=0;i<g.v.size() && i<sz;++i) ret[i+1][1]=g[i];
    return ret;
}
upoly toUpoly(Matrix<frac> g){
    upoly ret;
    ret.v.resize(sz+1);
    for (int i=1;i<=sz;++i) ret.v[i-1]=g[i][1];
    return ret;
}
Matrix<frac> operator * (Matrix<frac> M,upoly u){
    Matrix<frac> ret=Matrix<frac>(M.row,M.col);
    for (int i=0;i<u.v.size();++i) ret=ret+u.v[i]*Shift(M,i);
    return ret;
}
Matrix<frac> operator * (upoly u,Matrix<frac> M){return M*u;}
int main(){
    int rk=2;
    Matrix<frac> F=Matrix<frac>(sz,sz,1);
    //求解 f(x)/(g(x))^2 e^phi(x) 的积分
    upoly g=upoly("1+x"),f=upoly("x"),phi=upoly("x");
    Matrix<frac> M=g*Deriv(phi)*F+g*Deriv(F)-Deriv(g)*F;
    vector<Matrix<frac> >baseS=baseSolution(M,toVector(f));
    cout<<toUpoly(baseS.back())<<"|"<<g<<" e^"<<phi<<"+C"<<endl;
}