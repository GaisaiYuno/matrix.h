#define Num frac
#include "fraction.h"
#include "euclid.h"
using namespace std;
int main(){
    Matrix M=Matrix(3,3,vector<frac>{1,-8,-4,-8,1,-4,-4,-4,7});
    M=frac("1/9")*M;
    cout<<M*M.transpose()<<endl;
    cout<<isOrthogonalMatrix(M)<<endl;
}