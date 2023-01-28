#include "conv.h"
using namespace std;
int main(){
    freopen("simplex.txt","r",stdin);
    Matrix<double> A,b,c;
    cin>>A>>b>>c;
    cout<<Simplex(A,b,c)<<endl;
}
/*
3 6
1 1 3 1 0 0
2 2 5 0 1 0
4 1 2 0 0 1

3 1
30
24
36

1 6
-3 -1 -2 0 0 0

1 3
1 -1 1

1 1
0

1 3
1
*/