#include "poly.h"
#include "matrix.h"
using namespace std;
int main(){
    Matrix<poly<double> > A;
    cin>>A;
    Matrix<poly<double> > B;
    cin>>B;
    cout<<A*B<<endl;
}