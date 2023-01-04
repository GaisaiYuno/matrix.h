#include "poly.h"
using namespace std;
int main(){
    upoly LHS=definiteInt("x^4","0","1/2a")+definiteInt("x^4"-(upoly)("2ax-a^2")*(upoly)("2ax-a^2"),"1/2a","a");
    upoly RHS=definiteInt((upoly)("1/2a+1/2a^-1x")-upoly("x"),"0","a^2");
    solve(vectpr<poly>{poly(RHS-LHS)});
    
}