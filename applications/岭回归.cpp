#include "matrix.h"
#include "euclid.h"
using namespace std;
Matrix<long double>X[20],Y,w;
long double res[20];
int n,m;
long double lambda=0.01;
Matrix<long double>grad(){
    Matrix<long double>gw(1,m+1);
    for (int j=1;j<=m+1;++j){
        for (int i=1;i<=n;++i){
            gw[1][j]+=2*X[i][1][j]*res[i]/n;
        }
        gw[1][j]+=2*lambda*w[1][j];//岭回归加上这一项
        if (w[1][j]>0) gw[1][j]+=2*lambda;
        if (w[1][j]<0) gw[1][j]-=2*lambda;//Lasso回归加上这一项
    }
    return gw;
}
int main(){
    double alpha=0.03;
    cin>>lambda>>alpha;
    cin>>n>>m;
    for (int i=1;i<=n;++i) X[i].resize(1,m+1);
    Y.resize(n,1);
    w.resize(1,m+1);
    for (int i=1;i<=n;++i){
        X[i][1][1]=1;
        for (int j=1;j<=m;++j) cin>>X[i][1][j+1];
    }
    for (int i=1;i<=n;++i) cin>>Y[i][1];
    int iter=50000;
    while (iter--){
        long double J=0;
        for (int i=1;i<=n;++i){
            res[i]=(X[i]&w)-Y[i][1];
            J+=res[i]*res[i];
        }
        J/=n;
        w=w-alpha*grad();
    }
    //数据统计部分
    long double J=0;
    for (int i=1;i<=n;++i){
        res[i]=(X[i]&w)-Y[i][1];
        cout<<res[i]<<endl;
        J+=res[i]*res[i];
    }
    J/=n;
    cout<<J<<endl;
    cout<<w<<endl;
}