#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=poly("t")*Plane(2,1,-3,2)+Plane(5,5,-4,3);
    poly eq=dot_on_pl(Vector(4,-3,1),P);
    cout<<eq<<endl;
    solve(vector<poly>{eq});
    cout<<P<<endl;
    cout<<solvedResults[0].second<<endl;
    Matrix P2=substitute(P);
    eq=Nvec(P)&Nvec(P2);
    solve(vector<poly>{eq});
    Matrix P1=substitute(P);
    cout<<P1<<P2;
}