#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix B=Matrix('R',vector<poly>{1,1,-1,-1});
    Matrix C=Matrix('R',vector<poly>{1,-1,1,1});
    Matrix T=Matrix('R',vector<poly>{"1","l"});
    Matrix A=T*addV(B,C);
    Num eq=Nvec(A)&Matrix('R',vector<poly>{1,1,1});
    cout<<eq<<endl;
    Num l=Factorization(eq).sol().front();
    cout<<l<<endl;
    T[1][2]=l;
    cout<<T*addV(B,C)<<endl;
}