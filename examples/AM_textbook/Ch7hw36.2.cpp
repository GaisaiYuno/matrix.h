#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    /*
    直线 X，过点 (-1,0,4)，方向向量未知
    直线 L，过点 (-1,3,0)，方向向量 (3,1,2)，X,L共面
    X 垂直于平面 P：3x-4y+1z-10=0
    */
    Line X=make_pair(Vector(-1,0,4),Vector("d","e","f"));
    Line L=make_pair(Vector(-1,3,0),Vector(3,1,2));
    Matrix P=Plane(3,-4,1,-10);
    poly eq1=(X.second&Nvec(P));
    poly eq2=cross((X.first-L.first),X.second)&L.second;
    cout<<eq1<<" "<<eq2<<endl;
}