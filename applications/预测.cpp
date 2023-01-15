#include "matrix.h"
#include "euclid.h"
using namespace std;
int main(){
    vector<Matrix<long double> >v;
    int n;
    cin>>n;
    for (int i=1;i<=n;++i){
        Matrix<long double>V(3,1);
        cin>>V[1][1]>>V[2][1]>>V[3][1];
        v.push_back(V);
    }
    auto R=regression(v);
    auto M=mean(v);
    cout<<R<<endl;
    for (int i=1;i<=n;++i){
        long double y,z;
        cin>>y>>z;
        y-=M[2][1],z-=M[3][1];
        long double s=y*R[2][1]+z*R[3][1];
        cout<<(-s/R[1][1])+M[1][1]<<endl;
    }
}
/*
9
95 98 78
80 77 79
65 58 72
90 90 85
71 75 74
56 62 72
77 80 70
84 79 92
100 99 88
*/