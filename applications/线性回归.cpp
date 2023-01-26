#include "matrix.h"
#include "euclid.h"
using namespace std;
Matrix<long double>X[20],Y,w;
long double res[20];
int n,m;
Matrix<long double>grad(){
    Matrix<long double>gw(1,m+1);
    for (int j=1;j<=m+1;++j){
        for (int i=1;i<=n;++i){
            gw[1][j]+=2*X[i][1][j]*res[i]/n;
        }
    }
    return gw;
}
int main(){
    const double alpha=0.03;
    cin>>n>>m;
    for (int i=1;i<=n;++i) X[i].resize(1,m+1);
    Y.resize(n,1);
    w.resize(1,m+1);
    for (int i=1;i<=n;++i){
        X[i][1][1]=1;
        for (int j=1;j<=m;++j) cin>>X[i][1][j+1];
    }
    for (int i=1;i<=n;++i) cin>>Y[i][1];
    int iter=10000;
    while (iter--){
        long double J=0;
        for (int i=1;i<=n;++i){
            res[i]=(X[i]&w)-Y[i][1];
            J+=res[i]*res[i];
        }
        J/=n;
        // cout<<J<<endl;
        w=w-alpha*grad();
    }
    cout<<w<<endl;
}
/*
9.5 0.21034 3.83
7.2 4.426 0.175
8.1 

3 1
2
4
6
1
2
3
岭回归数据
10 2
1.1 1.1
1.4 1.5
1.7 1.8
1.7 1.7
1.8 1.9
1.8 1.8
1.9 1.8
2.0 2.1
2.3 2.4
2.4 2.5
16.3 16.8 19.2 18.0 19.5 20.9 21.1 20.9 20.3 22.0

得到
Row Vector
11.473 8.58426 -4.03773

与原数据 10,2,3 相差太大，因此需要岭回归
*/