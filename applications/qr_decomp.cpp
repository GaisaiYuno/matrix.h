#include "matrix.h"
#include "euclid.h"
using namespace std;
int main(){
    Matrix<double> A;
    cin>>A;
    auto x=EigenVals(A);
    for (auto val:x) cout<<val<<endl;
}
/*
1 2 3
4 5 6
3 5 7

1 0 1
0 1 0
1 0 3

3.08 0 -0.76 
0 1 0 
0.2 0 0.6
*/