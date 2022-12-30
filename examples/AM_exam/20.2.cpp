#include "poly.h"
using namespace std;
int main(){
    cout<<EquivInf(upoly("x^2")-variableLimit(Cos("x^2"),"0","x^2"));
}