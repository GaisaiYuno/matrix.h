#define Num frac
#include "fraction.h"
#include "euclid.h"
using namespace std;
Num F(Num x){
    return x*x*x;
}
Num G(Num x){
    return x*x;
}
int main(){
    Matrix A=Matrix('R',vector<Num>{(Num)(1),(Num)(2),(Num)(3)});
    Matrix B=Matrix('R',vector<Num>{(Num)(1),(Num)(3),(Num)(3)});
    Cauchy_Schwarz(A,B);
    Matrix _F=Discrete(F,(Num)(1),(Num)("3/2"),(Num)("1/10"));
    Matrix _G=Discrete(G,(Num)(1),(Num)("3/2"),(Num)("1/10"));
    Cauchy_Schwarz(_F,_G);
}