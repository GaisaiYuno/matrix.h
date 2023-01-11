#include <poly.h>
#include <matrix.h>
using namespace std;
int main(){
    Matrix<poly> C(2,2,vector<poly>{"a","b","c","d"});
    for (int i=1;i<=2;++i){
        for (int j=1;j<=2;++j){
            Matrix<poly> eps;
            eps.init(2,2);
            eps[i][j]=1;
            cout<<C.transpose()*eps*C<<endl;
        }
    }
}
/*
在交大线性代数课本 162 页
*/