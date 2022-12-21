#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix V('R',vector<poly>{2,-3,3});
    Matrix P('R',vector<poly>{1,-1,-2});
    cout<<Plane(V,P)<<endl;

    Matrix A('R',vector<poly>{"a","0","0"});
    Matrix B('R',vector<poly>{"0","b","0"});
    Matrix C('R',vector<poly>{"0","0","c"});

    Matrix Pl=Plane(A,B,C);
    cout<<toIntercept(Pl)<<endl;

    Pl=Matrix('R',vector<poly>{1,-2,3,-12});
    cout<<toIntercept(Pl)<<endl;
}