#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=Plane("a","b","c","d");
    Line L1=make_pair(Vector(2,0,5),Vector(3,-4,6));
    Line L2=make_pair(Vector(0,-2,1),Vector(1,2,2));
    poly eq1=Nvec(P)&L1.second;
    poly eq2=Nvec(P)&L2.second;
    poly eq3=dot_on_pl(Vector(-1,-2,3),P);
    solve(vector<poly>{eq1,eq2,eq3});
    outputResult();
}