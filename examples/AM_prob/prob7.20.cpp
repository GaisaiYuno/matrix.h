#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix Pl1=Matrix('R',vector<poly>{1,1,-2,-1});
    Matrix Pl2=Matrix('R',vector<poly>{1,2,-1,1});
    pair<Matrix,Matrix>p=toLine(Pl1,Pl2);
    output(Matrix('R',vector<poly>{-1,2,1}),p.second);
}