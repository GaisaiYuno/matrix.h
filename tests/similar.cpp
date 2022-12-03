#define Num poly
#include "poly.h"
#include "matrix.h"
using namespace std;
int main(){
    Matrix A;
    cin>>A;
    Matrix P;
    cin>>P;
    cout<<((P^(-1))*A*P)<<endl;
}
/*
A=
-1 1 1
1 -1 1
1 1 -1
P=
1 2 3
3 2 1
2 1 3
P^-1AP=
-1 5/6 7/6 
1 -7/6 7/6 
1 5/6 -5/6
*/