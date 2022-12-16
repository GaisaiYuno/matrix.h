#include <poly.h>
#define Num frac
#include <matrix.h>
#define MAXN 1005
using namespace std;
frac a[MAXN];
int main(){
    int n,k;
    cin>>n>>k;
    upoly g;
    g.v.resize(k+1);
    g[k]=frac(1);
    for (int i=1;i<=k;++i){
        cin>>a[i];
        g[k-i]=-a[i];
    }
    Matrix A(k,k);
    for (int i=1;i<=k;++i) A[1][i]=a[i];
    for (int i=1;i<=k-1;++i) A[i+1][i]=1;
    upoly M;
    M.v.resize(n+1);
    M[n]=frac(1);
    upoly r=M%g;
    Matrix An=Matrix(k,k);
    for (int i=r.v.size()-1;i>=0;--i) An=An*A+r.v[i]*Matrix(k,k,1);
    Matrix F(k,1);
    for (int i=1;i<=k;++i) cin>>F[k-i+1][1];
    cout<<(An*F)[k][1]<<endl;
}