#include "matrix.h"
#include "euclid.h"
using namespace std;
ifstream in;
bool on[20];
int main(){
    in.open("bangumi_data4.txt");
    vector<Matrix<long double> >v;
    int n,practical,m;
    in>>n>>practical>>m;
    for (int i=1;i<=m;++i) in>>on[i];
    int sz=0;
    for (int i=1;i<=m;++i) sz+=on[i];
    for (int i=1;i<=n;++i){
        Matrix<long double>V(sz,1);
        int j=0;
        for (int k=1;k<=m;++k){
            long double x;
            in>>x;
            if (on[k]) V[++j][1]=x;
        }
        v.push_back(V);
    }
    auto R=pca(v);
    auto M=mean(v);
    cout<<R<<endl;
    long double sum=0;
    for (int i=1;i<=practical;++i){
        long double data[40],s=0;
        long double rate;
        in>>rate;
        int j=1;
        for (int k=2;k<=m;++k){
            long double x;
            in>>x;
            if (on[k]){
                j++;
                data[j]=x,data[j]-=M[j][1];
            }
        }
        for (int j=2;j<=sz;++j) s+=data[j]*R[j][1];
        long double my_rate=(-s/R[1][1])+M[1][1];
        cout<<rate<<" "<<my_rate<<endl;
        sum+=myabs(rate-my_rate);
    }
    cout<<sum/practical<<endl;
    while (true){
        long double data[40],s=0;
        cout<<"please enter the data"<<endl;
        int j=1;
        for (int k=2;k<=m;++k){
            long double x;
            cin>>x;
            if (on[k]){
                j++;
                data[j]=x,data[j]-=M[j][1];
            }
        }
        for (int j=2;j<=sz;++j) s+=data[j]*R[j][1];
        cout<<(-s/R[1][1])+M[1][1]<<endl;
    }
}