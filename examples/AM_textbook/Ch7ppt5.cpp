#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=Vector("t","1-t","1-2t");
    Line L=make_pair(Vector(0,0,0),Vector(0,0,1));
    solvedResults.push_back(make_pair('t',"1/2-1/2z"));
    cout<<substitute(dist2_dot_ln(Vector("x","y","z"),L)-dist2_dot_ln(P,L))<<endl;
}