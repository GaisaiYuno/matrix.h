#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix B=Matrix('R',vector<poly>{7,-4,-4});
    Matrix C=Matrix('R',vector<poly>{-2,-1,2});
    Matrix T=Matrix('R',vector<poly>{"1","l"});
    Matrix A=T*addV(B,C);
    Num lB=length(B),lC=length(C);
    Num eq=lB*(A&C)-lC*(A&B);
    cout<<eq<<endl;
    Num l=Factorization(eq).sol().front();
    cout<<l<<endl;
}