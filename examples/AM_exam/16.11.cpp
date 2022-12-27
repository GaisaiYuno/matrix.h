#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=poly("t")*Plane(1,-1,-2,1)+Plane(0,2,-2,1);
    poly eq=angle2(Nvec(P),Vector(-1,1,-1))-poly("6/9");
    cout<<Factorization(eq)<<endl;
}