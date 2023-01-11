#include "poly.h"
#define Num poly
#include "matrix.h"
using namespace std;
int main(){
    Matrix A;
    cin>>A;
    cout<<(A^-1)<<endl;
    cout<<Determinant(A)<<endl;
    cout<<Determinant(A^(-1))<<endl;
}
/*
1-a^2-b^2 b -a 0
b -1 0 0
-a 0 -1 0
0 0 0 -1
*/