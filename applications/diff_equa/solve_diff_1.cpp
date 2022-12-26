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
struct diff{
    frac lambda;
    Matrix P;
    diff(){lambda=0;}
    diff(frac _lambda,int n){
        lambda=_lambda;
        P=Matrix(n,n,1);
    }
    diff(frac _lambda,Matrix _P){
        lambda=_lambda,P=_P;
    }
};
diff Deriv(diff t){
    return diff(t.lambda,Deriv(t.P)+t.lambda*t.P);
}
diff operator + (diff A,diff B){
    diff C;
    C.lambda=A.lambda;
    C.P=A.P+B.P;
    return C;
}
diff operator - (diff A,diff B){
    diff C;
    C.lambda=A.lambda;
    C.P=A.P-B.P;
    return C;
}
diff operator * (frac lambda,diff A){
    diff C;
    C.lambda=A.lambda;
    C.P=lambda*A.P;
    return C;
}
const int sz=4;
vector<sqrtNum> to_v(upoly u){
    while (u.v.size()<sz) u.v.push_back(0);
    return u.v;
}
const frac lambda=-1;
void output(Matrix v){
    upoly a;
    a.v.resize(sz);
    int cnt=0;
    for (int i=1;i<=v.row;++i){
        for (int j=1;j<=v.col;++j){
            a[cnt++]=v[i][j];
        }
    }
    cout<<"("<<a<<")e^"<<lambda<<"x"<<endl;
}
int main(){
    diff d=diff(lambda,sz);

    diff ans=Deriv(Deriv(d))-2*Deriv(d)-3*d;
    Matrix f=Matrix('C',to_v("5"));

    // cout<<ans.P<<f<<endl;
    vector<Matrix>baseS=baseSolution(ans.P,f);
    for (int i=0;i<baseS.size()-1;++i){
        cout<<"C"<<i<<" * ";
        output(baseS[i]);
    }
    output(baseS.back());
}