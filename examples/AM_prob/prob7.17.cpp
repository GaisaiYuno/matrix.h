#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix B=Matrix('R',vector<poly>{4,-1,3,-6});
    Matrix C=Matrix('R',vector<poly>{1,5,-1,10});
    Matrix T=Matrix('R',vector<poly>{"1","l"});
    Matrix A=T*addV(B,C);
    Num eq=Nvec(A)&Matrix('R',vector<poly>{2,-1,5});
    cout<<eq<<endl;
    Num l=Factorization(eq).sol().front();
    cout<<l<<endl;
    T[1][2]=l;
    cout<<T*addV(B,C)<<endl;
}