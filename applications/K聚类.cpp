#include "matrix.h"
#include "euclid.h"
using namespace std;
ifstream in;
bool on[20];
int best_belong[100],belong[100];
int core[100];
Matrix<long double>V[100],pt[100];
int sz[100];
int main(){
    in.open("bangumi_data_org.txt");
    int n,practical,m;
    in>>n>>practical>>m;
    for (int i=1;i<=m;++i) in>>on[i];
    int SZ=0;
    for (int i=1;i<=m;++i) SZ+=on[i];
    for (int i=1;i<=n;++i){
        V[i].resize(SZ,1);
        int j=0;
        for (int k=1;k<=m;++k){
            long double x;
            in>>x;
            if (on[k]) V[i][++j][1]=x;
        }
    }
    m=SZ;
    int k=3;//将番剧分为3类
    int iter=500;
    long double min_sum=1e10;
    while (iter--){
        for (int i=1;i<=n;++i) core[i]=i;
        random_shuffle(core+1,core+1+n);
        for (int j=1;j<=k;++j) pt[j]=V[core[j]];
        long double last_sum=0;
        while (true){
            long double sum=0;
            for (int i=1;i<=n;++i){
                long double min_dis=1e10;
                for (int j=1;j<=k;++j){
                    long double dis=length(pt[j]-V[i]);
                    if (dis<min_dis) min_dis=dis,belong[i]=j;
                }
                sum+=min_dis;
            }
            if (myabs(last_sum-sum)<1e-6){
                cout<<"----------------"<<endl;
                for (int j=1;j<=k;++j) cout<<pt[j]<<endl;
                break;
            }
            last_sum=sum;
            for (int j=1;j<=k;++j) sz[j]=0;
            for (int i=1;i<=n;++i) sz[belong[i]]++;
            for (int j=1;j<=k;++j) pt[j]=Matrix<long double>(m,1);
            for (int i=1;i<=n;++i) pt[belong[i]]=pt[belong[i]]+V[i];
            for (int j=1;j<=k;++j) pt[j]=(long double)(1)/sz[j]*pt[j];
        }
        if (last_sum<min_sum){
            min_sum=last_sum;
            cout<<min_sum<<endl;
            for (int i=1;i<=n;++i){
                best_belong[i]=belong[i];
            }
        }
    }
    for (int i=1;i<=n;++i){
        cout<<best_belong[i]<<" ";
    }
    for (int j=1;j<=k;++j){
        cout<<"belong to "<<j<<endl;
        for (int i=1;i<=n;++i){
            if (best_belong[i]==j){
                cout<<V[i];
            }
        }
        cout<<"-----------------------"<<endl;
    }
}