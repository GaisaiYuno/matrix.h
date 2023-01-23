#include "matrix.h"
#include "euclid.h"
#define MAXN 105
using namespace std;
ifstream in;
bool on[MAXN];
Matrix<long double>M,D,R;
int sz;
int n,practical,m;
long double predict(bool flag=true){
    long double data[MAXN],s=0;
    int j=1;
    for (int k=2;k<=m;++k){
        long double x;
        if (flag) in>>x;
        else cin>>x;
        if (on[k]){
            j++;
            data[j]=(x-M(j))/D(j);
            // j++;
            // data[j]=(sqrt(x)-M(j))/D(j);
            // j++;
            // data[j]=(log(x+1e-4)-M(j))/D(j);
        }
    }
    for (int j=2;j<=sz;++j) s+=data[j]*R(j);
    return (-s/R(1))*D(1)+M(1);
}
int main(){
    in.open("bangumi_data4.txt");
    vector<Matrix<long double> >v;
    in>>n>>practical>>m;
    for (int i=1;i<=m;++i) in>>on[i];
    for (int i=1;i<=m;++i) sz+=on[i];
    // sz=sz*2-1;
    for (int i=1;i<=n;++i){
        Matrix<long double>V(1,sz);
        int j=0;
        for (int k=1;k<=m;++k){
            long double x;
            in>>x;
            if (on[k]){
                V(++j)=x;
                // if (k!=1) V(++j)=sqrt(x);
                // if (k!=1) V(++j)=log(x+1e-4);
            }
        }
        v.push_back(V);
    }
    M=mean(v),D=devi(v);
    cout<<M<<D<<endl;
    R=pca(to_std(v));
    cout<<R<<endl;
    long double sum=0;
    for (int i=1;i<=practical;++i){
        long double rate;
        in>>rate;
        long double my_rate=predict();
        cout<<rate<<" "<<my_rate<<endl;
        sum+=myabs(rate-my_rate);
    }
    cout<<sum/practical<<endl;
    while (true){
        cout<<predict(false)<<endl;
    }
}