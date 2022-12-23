#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P1=Plane(1,-2,1,1),P2=Plane(1,1,2,-3);
    Matrix N1=P1/length(Nvec(P1)),N2=P2/length(Nvec(P2));
    cout<<N1+N2<<N1-N2<<endl;
}