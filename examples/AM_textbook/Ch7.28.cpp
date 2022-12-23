#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Matrix P=Vector(2,-1,3);
    cout<<dist(P,make_pair(Vector(2,-1,0),Vector(3,4,5)))<<endl;
}