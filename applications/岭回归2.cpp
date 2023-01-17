#include "matrix.h"
#include "euclid.h"
using namespace std;
ifstream in;
Matrix<long double>X[100],Y,w;
long double res[100];
int n,practical,m;
long double lambda=0.01;
Matrix<long double>grad(){
    Matrix<long double>gw(1,m);
    for (int j=1;j<=m;++j){
        for (int i=1;i<=n;++i){
            gw[1][j]+=2*X[i][1][j]*res[i]/n;
        }
        // gw[1][j]+=2*lambda*w[1][j];
        // if (w[1][j]>0) gw[1][j]+=2*lambda;
        // if (w[1][j]<0) gw[1][j]-=2*lambda;
    }
    return gw;
}
bool on[20];
int main(){
    in.open("bangumi_data4.txt");
    in>>n>>practical>>m;
    for (int i=1;i<=m;++i) in>>on[i];
    double alpha=0.03;
    for (int i=1;i<=n;++i) X[i].resize(1,m);
    Y.resize(n,1);
    w.resize(1,m);
    for (int i=1;i<=n;++i){
        X[i][1][1]=1;
        in>>Y[i][1];
        for (int j=1;j<=m-1;++j){
            in>>X[i][1][j+1];
            if (j==5||j==10||j==15) X[i][1][j+1]=0;
        }
        cout<<"评分："<<Y[i][1]<<endl;
        cout<<X[i]<<endl;
    }
    int iter=1000;
    while (iter--){
        long double J=0;
        for (int i=1;i<=n;++i){
            res[i]=(X[i]&w)-Y[i][1];
            J+=res[i]*res[i];
        }
        J/=n;
        cout<<J<<endl;
        w=w-(alpha*grad());
    }
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
/*
岭回归数据
0.05 0.02
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
与原数据 10,2,3 相差太大，因此需要岭回归
*/