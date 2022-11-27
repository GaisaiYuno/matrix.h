#define Num frac
#include "fraction.h"
#include "matrix.h"
using namespace std;
int main(){
    Matrix A,B;
    cin>>A>>B;
    // cout<<A*B<<B*A<<endl;
    cout<<(B^-1)*A<<endl;
    cout<<A*(B^-1)<<endl;
    cout<<(A^-1)*B<<endl;
    cout<<B*(A^-1)<<endl;
    // cout<<A*(B^(-1))<<(B^(-1))*A<<endl;
}
/*
-5 0 -5
0 -1 -1
3 6 9

4/5 21/5 5
7/5 -12/5 -1
7/5 -7/5 0

-1 0 -3
0 1 -1
2 1 0

0 1 1 1
-1 1 1 0
2 -1 2 -1
1 1 -1 -1

-1 1 1 0
4 -2 4 -2
3 3 -3 -3
0 0 0 0
*/