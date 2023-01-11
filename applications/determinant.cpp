#include "poly.h"
#include "matrix.h"
using namespace std;
int main(){
    Matrix<poly> A;
    cin>>A;
    cout<<Determinant(A)<<endl;
}