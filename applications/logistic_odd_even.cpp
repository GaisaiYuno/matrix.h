#include "matrix.h"
#include "euclid.h"
using namespace std;
long double sigmoid(long double x){
    return 1/(1+exp(-x));
}
Matrix<long double>sigmoid(Matrix<long double>M){
    for (int i=1;i<=M.row;++i){
        for (int j=1;j<=M.col;++j){
            M[i][j]=sigmoid(M[i][j]);
        }
    }
    return M;
}
Matrix<long double>log(Matrix<long double>M){
    for (int i=1;i<=M.row;++i){
        for (int j=1;j<=M.col;++j){
            M[i][j]=log(M[i][j]);
        }
    }
    return M;
}
Matrix<long double>flip(Matrix<long double>M,const double eps=-1){
    for (int i=1;i<=M.row;++i){
        for (int j=1;j<=M.col;++j){
            M[i][j]=1-M[i][j];
            if (myabs(M[i][j])<eps) M[i][j]=eps;
            //为了防止log出错
        }
    }
    return M;
}
Matrix<long double>mul(Matrix<long double>A,Matrix<long double>B){
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            A[i][j]=A[i][j]*B[i][j];
        }
    }
    return A;
}
int main(){
    long double alpha;
    cin>>alpha;
    int iter;
    cin>>iter;
    Matrix<long double>X(10,5),Y(10,1);
    //X 是数据坐标点，Y 是01标签
    Matrix<long double>beta(1,5);
    // beta[1][1]=0.5,beta[1][2]=0.5;
    for (int i=1;i<=10;++i){
        cin>>X[i][2],X[i][1]=1;
        X[i][3]=X[i][2]*X[i][2];
        X[i][4]=X[i][2]*X[i][2]*X[i][2];
        X[i][5]=X[i][2]*X[i][2]*X[i][2];
    }
    for (int i=1;i<=10;++i) cin>>Y[i][1];
    for (int t=1;t<=iter;++t){
        Matrix y_posi=sigmoid(X*beta.transpose());
        long double cross_entropy=-mean(mul(Y,log(y_posi))+mul(flip(Y),log(flip(y_posi,1e-4))));
        Matrix grad=(Y-y_posi).transpose()*X;
        beta=beta+alpha*grad;
        cout<<cross_entropy<<endl;
    }
    cout<<beta<<endl;
    cout<<sigmoid(X*beta.transpose());
}
/*
0.03 3000
2
4
6
8
10
1
3
5
7
9
1 1 0 0 0 1 1 1 0 0
*/