#include "matrix.h"
#include "euclid.h"
#define MAXN 1005
using namespace std;
Matrix<long double>pt[MAXN];
long double dis[MAXN][MAXN];
int belong[MAXN];
bool core[MAXN],vis[MAXN];
int cluster;
vector<int>adj[MAXN];
void dfs_paint(int u,int color){
    vis[u]=true;
    belong[u]=color;
    for (int v:adj[u]){
        if (!vis[v]) dfs_paint(v,color);
    }
}
int n,m;
void normalize(int j){
    long double down=0,up=100;
    long double maxn=-1e9,mino=1e9;
    for (int i=1;i<=n;++i){
        maxn=max(maxn,pt[i][1][j]);
        mino=min(mino,pt[i][1][j]);
    }
    for (int i=1;i<=n;++i){
        pt[i][1][j]=((pt[i][1][j]-mino)/(maxn-mino))*(up-down)+down;
    }
}
int main(){
    freopen("bangumi_data_org.txt","r",stdin);
    cin>>n>>m;
    for (int i=1;i<=n;++i){
        pt[i].resize(1,m);
        for (int j=1;j<=m;++j){
            cin>>pt[i][1][j];
        }
    }
    for (int j=1;j<=m;++j) normalize(j);
    for (int i=1;i<=n;++i) cout<<pt[i]<<endl;
    long double eps=50;
    int MinPts=2;
    for (int i=1;i<=n;++i){
        int cnt=0;
        for (int j=1;j<=n;++j){
            dis[i][j]=length(pt[i]-pt[j]);
            // cout<<dis[i][j]<<endl;
            if (dis[i][j]<=eps) cnt++;
        }
        if (cnt>=MinPts) core[i]=true;
    }
    for (int i=1;i<=n;++i){
        if (core[i]){
            for (int j=i+1;j<=n;++j){
                if (dis[i][j]<=eps && core[j]){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                    // cout<<i<<" "<<j<<endl;
                }
            }
        }
    }
    for (int i=1;i<=n;++i){
        if (core[i] && !vis[i]){
            dfs_paint(i,++cluster);
        }
    }
    for (int i=1;i<=n;++i){
        cout<<belong[i]<<" ";
    }
    cout<<endl;
}

/*
8 2
2 10
2 5
8 4
5 8
7 5
6 4
1 2
4 9
*/