#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    //7.24.3
    Matrix A=Matrix('R',vector<poly>{2,1,-3});
    Matrix B=Matrix('R',vector<poly>{5,-1,4});
    Matrix C=Matrix('R',vector<poly>{2,-2,4});
    cout<<Plane(A,B,C)<<endl;
    //7.24.7
    cout<<baseSolution(Matrix(3,4,vector<poly>{3,5,-1,0,8,-3,1,1,4,7,2,1})).front()<<endl;
    //7.25.5
    output(
        Matrix('R',vector<poly>{-1,2,1}),
        toLine(
            Matrix('R',vector<poly>{1,1,-2,-1}),
            Matrix('R',vector<poly>{1,2,-1,1})
        ).second
    );
    //7.27.1
    Matrix Pl1=Matrix('R',vector<poly>{3,2,-6,-1});
    Matrix P=Matrix('R',vector<poly>{1,-3,2});
    cout<<dist(P,Pl1)<<endl;
    //7.28.1
    A=Matrix('R',vector<poly>{1,0,1});
    B=Matrix('R',vector<poly>{0,1,-1});
    cout<<Arccos(abs(angle(A,B)))<<endl;
    //7.28.2
    A=Matrix('R',vector<poly>{-8,-6,2});
    B=Matrix('R',vector<poly>{4,3,-1});
    cout<<Arccos(abs(angle(A,B)))<<endl;
    //7.28.3
    A=Matrix('R',vector<poly>{2,-6,3});
    B=Matrix('R',vector<poly>{3,-1,-4});
    cout<<Arccos(abs(angle(A,B)))<<endl;
}