#include "matrix.h"
#include "euclid.h"
using namespace std;
Matrix<long double>X[20],Y,w;
long double res[20];
int n,m=4;
Matrix<long double>grad(){
    Matrix<long double>gw(1,m);
    for (int j=1;j<=m;++j){
        for (int i=1;i<=n;++i){
            gw(j)+=2*X[i](j)*res[i]/n;
        }
    }
    cout<<gw<<endl;
    return gw;
}
int main(){
    const double alpha=0.001;
    cin>>n;
    Y.resize(n,1);
    w.resize(1,m);
    for (int i=1;i<=n;++i){
        X[i].resize(1,m);
        X[i](1)=1;
        for (int j=2;j<=4;++j) cin>>X[i](j);
        // for (int j=5;j<=7;++j) X[i](j)=X[i](j-3)*X[i](j-3);//添加二次项
    }
    for (int i=1;i<=n;++i) cin>>Y(i);
    int iter=20;
    while (iter--){
        long double J=0;
        for (int i=1;i<=n;++i){
            res[i]=(X[i]&w)-Y(i);
            J+=res[i]*res[i];
        }
        J/=n;
        cout<<J<<endl;
        w=w-alpha*grad();
    }
    while (true){
        Matrix<long double>input(1,m);
        input(1)=1;
        for (int j=2;j<=4;++j) cin>>input(j);
        for (int j=5;j<=7;++j) input(j)=input(j-3)*input(j-3);
        cout<<(input&w)<<endl;
    }
}
/*
5
9.5 141 290
7.2 227962 451.8
8.1 1000 327
8.4 18800 220
8.4 140500 100
61
2000
3068
1500
1000

3
9.5 141 290
8.1 1000 327
8.4 18800 220
61
3068
1500
*/