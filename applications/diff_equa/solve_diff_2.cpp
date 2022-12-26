#include "poly.h"
#undef POLY_H
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
struct diff{
    frac a,b;
    Matrix P;
    Matrix Q;
    diff(){a=0,b=0;}
    diff(frac _a,frac _b,int n){
        a=_a,b=_b;
        P=addH(Matrix(n,n,1),Matrix(n,n));
        Q=addH(Matrix(n,n),Matrix(n,n,1));
    }
    diff(frac _a,frac _b,Matrix _P,Matrix _Q){
        a=_a,b=_b,P=_P,Q=_Q;
    }
};
diff Deriv(diff t){
    int n=t.P.row;
    Matrix DP=Deriv(t.P),DQ=Deriv(t.Q);
    return diff(t.a,t.b,DP+t.a*t.P+t.b*t.Q,DQ+t.a*t.Q-t.b*t.P);
}
diff operator + (diff A,diff B){
    diff C;
    C.a=A.a,C.b=A.b;
    C.P=A.P+B.P,C.Q=A.Q+B.Q;
    return C;
}
diff operator - (diff A,diff B){
    diff C;
    C.a=A.a,C.b=A.b;
    C.P=A.P-B.P,C.Q=A.Q-B.Q;
    return C;
}
diff operator * (frac lambda,diff A){
    diff C;
    C.a=A.a,C.b=A.b;
    C.P=lambda*A.P,C.Q=lambda*A.Q;
    return C;
}
const int sz=2;
frac Alpha=0,Beta=1;
void output(Matrix v){
    // cout<<v<<endl;
    upoly a,b;
    a.v.resize(sz),b.v.resize(sz);
    int cnt=0;
    for (int i=1;i<=v.row;++i){
        for (int j=1;j<=v.col;++j){
            if (cnt<sz) a[cnt++]=v[i][j];
            else b[(cnt++)-sz]=v[i][j];
        }
    }
    cout<<"[("<<a<<")cos("<<Beta<<"x)+("<<b<<")sin("<<Beta<<"x)"<<"]e^"<<Alpha<<"x"<<endl;
}
//
int main(){
    diff d=diff(Alpha,Beta,sz);
    // 解y''-2y'+2y=e^xcosx
    // diff ans=Deriv(Deriv(d))-2*Deriv(d)+2*d;
    // Matrix f=Matrix('C',vector<frac>{1,0,0,0});

    // 解y''+y=cosx
    // diff ans=Deriv(Deriv(d))+d;
    // Matrix f=Matrix('C',vector<frac>{1,0,0,0});

    // 解y''+4y=xsinx
    // diff ans=Deriv(Deriv(d))+4*d;
    // Matrix f=Matrix('C',vector<frac>{0,0,0,1});

    // 解y''+y=-sin2x
    // diff ans=Deriv(Deriv(d))+d;
    // Matrix f=Matrix('C',vector<frac>{0,0,-1,0});

    // 解y''+4y'+4y=cos2x
    // diff ans=Deriv(Deriv(d))+4*Deriv(d)+4*d;
    // Matrix f=Matrix('C',vector<frac>{1,0,0,0});

    diff ans=Deriv(Deriv(d))-2*Deriv(d)-3*d;
    Matrix f=Matrix('C',vector<frac>{0,0,1,0});

    // cout<<addV(ans.P,ans.Q)<<endl<<f<<endl;
    vector<Matrix>baseS=baseSolution(addV(ans.P,ans.Q),f);
    for (int i=0;i<baseS.size()-1;++i){
        cout<<"C"<<i<<" * ";
        output(baseS[i]);
    }
    // cout<<baseS.back()<<endl;
    output(baseS.back());
}