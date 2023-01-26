#include "matrix.h"
#include "euclid.h"
using namespace std;
int main(){
    vector<Matrix<long double> >v;
    int n;
    cin>>n;
    for (int i=1;i<=n;++i){
        Matrix<long double>V(1,4);
        for (int k=1;k<=4;++k){
            cin>>V(k);
        }
        v.push_back(V);
    }
    auto R=pca(to_mean(v));
    auto M=mean(v);
    while (true){
        long double data[40],s=0;
        cout<<"please enter the data"<<endl;
        for (int k=2;k<=4;++k){
            long double x;
            cin>>x;
            data[k]=x,data[k]-=M(k);
        }
        for (int j=2;j<=4;++j) s+=data[j]*R(j);
        cout<<max((long double)(0),(-s/R(1))+M(1))<<endl;
    }
}
/*
5
61 9.5 141 290
2000 7.2 227962 451.8
3068 8.1 1000 327
1500 8.4 18800 220
1000 8.4 140500 100

5
541 9.5 141 290
40000 7.2 227962 451.8
5000 8.1 1000 327
1451 8.4 18800 220
7000 8.4 140500 100
*/