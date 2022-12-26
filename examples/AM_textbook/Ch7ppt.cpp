#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Line l1=make_pair(Vector(-1,0,1),Vector(1,1,2));
    Line l2=make_pair(Vector(0,-1,2),Vector(1,3,4));
    Matrix C=distLine(l1,l2).second;
    cout<<angle(l1,l2)<<endl;
    cout<<C<<endl;
    cout<<length(C)<<endl;
    cout<<commonPlumb(l1,l2).first<<" "<<commonPlumb(l1,l2).second;
}