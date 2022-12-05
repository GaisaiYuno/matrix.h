#include "poly.h"
using namespace std;
int main(){
    cout<<EquivInf(Exp("-1/2x^2")-Cos("x"))<<endl;
    cout<<EquivInf(Ln("1+x+x^2")+Ln("1-x+x^2"))<<endl;
    cout<<Limit(upoly("x")*(Exp("x")+Exp("-x")-upoly("2")),upoly("x")-Sin("x"))<<endl;
    cout<<Limit(Exp(shift(-1,Ln("1+x"))-upoly("1"))-upoly("1"),"x")<<endl;
    cout<<Limit(2*Sin("x")*Ln("1+x")-2*upoly("x")*Arctan("x")+upoly("x^3"),upoly("x^4"))<<endl;
    //cout<<Sin(Tan("x"))-Tan(Sin("x"))<<endl;
    cout<<Limit(Sin(Tan("x"))-Tan(Sin("x")),upoly("x^3"))<<endl;
    cout<<Limit(Sin(Exp("x")-upoly("1"))-(Exp(Sin("x"))-upoly("1")),upoly("x^4"))<<endl;
}