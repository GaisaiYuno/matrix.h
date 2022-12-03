#include "fraction.h"
#define Num frac
#include "strassen.h"
using namespace std;
using namespace strassen;
int main(){
    Matrix A(4,4);
    Matrix B(4,4);
    A.genRand(),B.genRand();
    Matrix C=A*B;
    Matrix D=strassen_mul(A,B);
    cout<<C<<D<<endl;
    assert(C==D);
    Matrix E=strassen_inverse(A);
    Matrix F=A^(-1);
    cout<<E<<F<<endl;
    assert(E==F);
    Num det1=Determinant(A);
    Num det2=strassen_det(A);
    cout<<det1<<" "<<det2<<endl;
    assert(det1==det2);
}