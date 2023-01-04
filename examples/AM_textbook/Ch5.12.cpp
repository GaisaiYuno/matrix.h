#include "poly.h"
using namespace std;
int main(){
    cout<<Limit(variableLimit("x^2","0",Arctan(Pow("x",sqrtNum("1/2")))),Ln("1+x^3"));
}