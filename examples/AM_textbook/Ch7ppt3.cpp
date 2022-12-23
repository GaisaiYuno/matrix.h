#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix A=Vector(0,2,-4),B=Vector(-1,0,-2);
    Line L=make_pair(Vector(-1,7,0),Vector(1,-2,1));
    Matrix C=L.first+poly("t")*L.second;
    cout<<length2(cross(B-C,A-C))/2<<endl;
    cout<<length(distLine(make_pair(A,B-A),L))*length(B-A)/2<<endl;
}