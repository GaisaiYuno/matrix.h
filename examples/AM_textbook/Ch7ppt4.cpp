#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=Vector(1,-1,0);
    Line L=make_pair(Vector(0,1,-2),Vector(1,2,2));
    cout<<dist2(P,L)-dist2(Vector("x","y","z"),L)<<endl;
}