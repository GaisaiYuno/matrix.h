#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=Vector(0,-1,2)-Vector("0","0","z");
    Matrix V=Vector(1,3,4);
    poly eq=cross(P,V)&Vector(1,1,2);
    cout<<Factorization(eq)<<endl;
}