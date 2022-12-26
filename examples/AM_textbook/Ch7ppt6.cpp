#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    solvedResults.push_back(make_pair('x',"1/2r+1/2rc"));
    solvedResults.push_back(make_pair('y',"1/2rs"));
    cout<<substitute(poly("x^2+y^2+z^2-r^2"))<<endl;
}