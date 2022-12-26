#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Line L1=make_pair(Vector(0,0,-1),Vector(1,-1,0));
    Line L2=make_pair(Vector(0,0,1),Vector(1,1,0));
    output(distLine(L1,L2));
}