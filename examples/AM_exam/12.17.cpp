#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=poly("t")*Plane(1,-3,-1,-4)+Plane(2,-1,1,-1);
    poly eq=dist2_dot_pl(Vector(0,0,0),P)-1;
    cout<<Factorization(eq)<<endl;
}