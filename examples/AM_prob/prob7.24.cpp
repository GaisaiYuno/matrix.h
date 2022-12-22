#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P0=Matrix('R',vector<poly>{-7,-2,-2});
    Matrix V=Matrix('R',vector<poly>{1,2,3});
    Matrix P=P0+poly("l")*V;
    Matrix A=Matrix('R',vector<poly>{2,3,1});
    Num eq=(A-P)&V;
    Num l=Factorization(eq).sol().front();
    cout<<P0+l*V<<endl;
}