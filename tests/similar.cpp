#include "poly.h"
#define Num poly
#include "matrix.h"
using namespace std;
int main(){
    Matrix A;
    cin>>A;
    Matrix P;
    cin>>P;
    cout<<(P*A*(P^(-1)))<<endl;
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

-1 0 0
0 -1 0
0 0 8

1 4/5 1
-2 2/5 1/2
0 -1 1
*/