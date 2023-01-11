#include "poly.h"
#include "matrix.h"
using namespace std;
int main(){
    Matrix<poly> A;
    cin>>A;
    Matrix<poly> B;
    cin>>B;
    cout<<A*B<<endl;
}