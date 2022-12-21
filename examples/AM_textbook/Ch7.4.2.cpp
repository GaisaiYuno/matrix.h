#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    //7.20
    Matrix Pl1('R',vector<poly>{2,-1,-5});
    Matrix Pl2('R',vector<poly>{1,0,-4});
    Matrix P('R',vector<poly>{3,-1,5});
    output(P,cross(Pl1,Pl2));
    //7.21
    Pl1=Matrix('R',vector<poly>{2,-3,1,-5});
    Pl2=Matrix('R',vector<poly>{3,1,-2,-2});
    pair<Matrix,Matrix>p=toLine(Pl1,Pl2);
    cout<<p.first<<endl<<p.second<<endl;
    output(p.first,p.second);
    //7.22
    Pl1=Matrix('R',vector<poly>{2,-1,-2,1});
    Pl2=Matrix('R',vector<poly>{1,1,4,-2});
    Matrix C=Matrix('R',vector<poly>{"1","l"});
    Matrix D=C*addV(Pl1,Pl2);
    cout<<D<<endl;
    cout<<toIntercept(D)<<endl;
    cout<<Factorization(D[1][2]-D[1][3])<<endl;
    C[1][2]=poly("1/3");
    cout<<C*addV(Pl1,Pl2)<<endl;
}