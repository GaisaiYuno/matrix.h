#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=Plane("a","b","1","d");
    Line L1=make_pair(Vector(0,0,0),Vector(1,0,0));
    poly eq1=para_vec_pl(L1.second,P);
    poly eq2=dot_on_pl(L1.first,P);
    // cout<<eq1<<" "<<eq2<<endl;
    solve(vector<poly>{eq1,eq2});
    outputResult();
    P=substitute(P);
    poly eq3=angle2(Nvec(P),Nvec(Plane("1","-1","0","0")))-poly("1/4");
    cout<<"eq:"<<eq3<<endl;
    Num l=Factorization(eq3).sol().front();
    cout<<l<<endl;
    solvedResults.push_back(make_pair('b',l.x));
    cout<<substitute(P)<<endl;
    l=Factorization(eq3).sol().back();
    cout<<l<<endl;
    solvedResults.pop_back();
    solvedResults.push_back(make_pair('b',l.x));
    cout<<substitute(P)<<endl;
}
/*
eq1,2->a=0,d=0
b=+-c
*/