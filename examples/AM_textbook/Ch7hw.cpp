#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    //7.24.3
    Matrix A=Vector(2,1,-3),B=Vector(5,-1,4),C=Vector(2,-2,4);
    cout<<Plane(A,B,C)<<endl;
    //7.24.7
    cout<<baseSolution(Matrix(3,4,vector<poly>{3,5,-1,0,8,-3,1,1,4,7,2,1})).front()<<endl;
    //7.25.5
    output(Vector(-1,2,1),toLine(Plane(1,1,-2,-1),Plane(1,2,-1,1)).second);
    //7.27.1
    Matrix Pl1=Plane(3,2,-6,-1),P=Vector(1,-3,2);
    cout<<dist(P,Pl1)<<endl;
    //7.28.1
    A=Vector(1,0,1),B=Vector(0,1,-1);
    cout<<Arccos(abs(angle(A,B)))<<endl;
    //7.28.2
    A=Vector(-8,-6,2),B=Vector(4,3,-1);
    cout<<Arccos(abs(angle(A,B)))<<endl;
    //7.28.3
    A=Vector(2,-6,3),B=Vector(3,-1,-4);
    cout<<Arccos(abs(angle(A,B)))<<endl;
}