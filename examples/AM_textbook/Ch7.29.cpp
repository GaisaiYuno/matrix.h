#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=Vector("u","v","w");
    cout<<dist2(P,Vector("x","y","z"))-poly("r^2")<<endl;
}