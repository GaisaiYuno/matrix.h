#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Line L=make_pair(Vector(0,1,-1),Vector(1,0,0));
    Matrix P=Plane(1,1,1,-1);
    Line L2=make_pair(Vector("a","b","c"),Vector("d","e","f"));
    poly eq1=(L2.first&Nvec(P))+P[1][4];
    poly eq2=(L2.second&Nvec(P));
    poly eq3=(L2.second&L.second);
    solve(vector<poly>{eq1,eq2,eq3});
    outputResult();
    L2.first=substitute(L2.first);
    L2.second=substitute(L2.second);
    output(L2);
}