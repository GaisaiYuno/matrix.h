#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=Plane("1","b","c","d");
    Line L1=toLine(Plane(1,5,1,0),Plane(1,0,-1,4));
    poly eq1=para_vec_pl(L1.second,P);
    poly eq2=dot_on_pl(L1.first,P);
    cout<<"eq:"<<eq1<<" "<<eq2<<endl;
    solve(vector<poly>{eq1,eq2});
    outputResult();
    P=substitute(P);
    poly eq3=angle2(Nvec(P),Nvec(Plane(1,-4,-8,12)))-poly("1/2");
    cout<<"eq:"<<eq3<<endl;
    Num l=Factorization(eq3).sol().front();
    cout<<l<<endl;
    solvedResults.push_back(make_pair('m',l.x));
    cout<<P<<endl;
    cout<<substitute(P)<<endl;
    l=Factorization(eq3).sol().back();
    cout<<l<<endl;
    solvedResults.pop_back();
    solvedResults.push_back(make_pair('m',l.x));
    cout<<substitute(P)<<endl;
}