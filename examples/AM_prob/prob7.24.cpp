#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    auto P0=Matrix('R',vector<poly>{-7,-2,-2});
    auto V=Matrix('R',vector<poly>{1,2,3});
    auto P=P0+poly("l")*V;
    auto A=Matrix('R',vector<poly>{2,3,1});
    auto eq=(A-P)&V;
    auto l=Factorization(eq).sol().front();
    cout<<P0+l*V<<endl;
}