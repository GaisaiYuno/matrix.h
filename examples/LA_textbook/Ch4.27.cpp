#include "poly.h"
#define Num poly
#include "matrix.h"
using namespace std;
int main(){
    Matrix A;
    cin>>A;
    cout<<A*A.transpose()<<endl;
}