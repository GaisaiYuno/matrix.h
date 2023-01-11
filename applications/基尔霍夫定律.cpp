#include "poly.h"
#include "matrix.h"
#define MAXN 10005
using namespace std;
int U[MAXN],V[MAXN];
int main(){
    int n,m;
    // cout<<"请输入节点数和边数：";
    cin>>n>>m;
    Matrix<poly> A(m,n);
    Matrix<poly> R(m,m);
    Matrix<poly> Z(n,n);
    Matrix<poly> alpha=Matrix<poly>(n+m,1);
    for (int i=1;i<=m;++i){
        int u,v;
        poly r,e;
        // cout<<"请输入第"<<i<<"条导线的两个端点和电阻、电势：";
        cin>>u>>v>>r>>e;
        U[i]=u,V[i]=v;
        A[i][u]=-1;
        A[i][v]=1;
        R[i][i]=r;
        alpha[i][1]=e;
    }
    Matrix<poly> B=addV(addH(R,A),addH(A.transpose(),Z));
    cout<<B<<endl;
    auto baseS=baseSolution(B,alpha);
    for (int i=1;i<=m;++i){
        cout<<"从"<<U[i]<<"到"<<V[i]<<"的电流为："<<baseS.back()[i][1]<<endl;
    }
    for (int i=1;i<=n;++i){
        cout<<"节点"<<i<<"的电势为"<<baseS.back()[i+m][1]<<endl;
    }
    cout<<trig_add<<" "<<trig_mul<<" "<<trig_div<<endl;
}
/*
4 6
1 2 1
1 3 1
1 4 1
2 3 1
2 4 1
3 4 1


4 6
1 2 u 0
2 4 v 0
2 3 r 0
1 3 v 0
3 4 u 0
1 4 0 e

9 13
1 2 r 0
2 3 r 0
1 4 r 0
2 5 r 0
3 6 r 0
4 5 r 0
5 6 r 0
4 7 r 0
5 8 r 0
6 9 r 0
7 8 r 0
8 9 r 0
7 3 0 e
*/