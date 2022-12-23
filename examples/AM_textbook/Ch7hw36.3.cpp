#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Line X=make_pair(Vector(1,2,1),Vector("d","e","f"));
    Line L=make_pair(Vector(0,0,0),Vector(2,1,-1));
    Line M=make_pair(Vector(1,0,-1),Vector(3,2,1));
    poly eq1=X.second&M.second;
    poly eq2=cross((X.first-L.first),X.second)&L.second;
    solve(vector<poly>{eq1,eq2});
    outputResult();
}