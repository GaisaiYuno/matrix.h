#include "poly.h"
using namespace std;
int main(){
    upoly p=shift(-1,variableLimit(Exp("x^2"),"x","2x"));
    cout<<EquivInf(p)<<endl;
    cout<<EquivInf(Deriv(p))<<endl;
}