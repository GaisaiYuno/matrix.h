#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix B=Matrix('R',vector<poly>{1,28,-2,17});
    Matrix C=Matrix('R',vector<poly>{5,8,-1,1});
    Matrix T=Matrix('R',vector<poly>{"1","l"});
    Matrix A=T*addV(B,C);
    cout<<A<<endl;
    Num eq=(Nvec(A)&Nvec(A))-(A[1][4]*A[1][4]);
    cout<<eq<<endl;
    Num l=Factorization(eq).sol().front();
    cout<<l<<endl;
    T[1][2]=l;
    cout<<T*addV(B,C)<<endl;
    l=Factorization(eq).sol().back();
    cout<<l<<endl;
    T[1][2]=l;
    cout<<T*addV(B,C)<<endl;
}