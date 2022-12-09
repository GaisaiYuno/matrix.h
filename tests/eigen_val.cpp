#include "poly.h"
#define Num poly
#include "matrix.h"
using namespace std;
int main(){
    Matrix A;
    cin>>A;
    Matrix B=A;
    for (int i=1;i<=A.row;++i){
        B[i][i]=B[i][i]-Num("l");
    }
    cout<<"Eigen Poly"<<endl;
    _poly x=Determinant(B).x;
    cout<<x<<endl;
    upoly _x;
    _x.init_from_poly(x);
    cpoly v=Factorization(_x);
    cout<<"Factorization"<<endl<<v<<endl;
    vector<Matrix>s;
    for (int i=0;i<v.v.size();++i){
        if (v.v[i].first.deg()==1){
            Num lambda=poly(poly_ele((frac)(0)-v.v[i].first[0]));
            cout<<"lambda="<<lambda<<endl;
            cout<<"n="<<v.v[i].second<<endl;//代数重数
            Matrix B=A-lambda*Matrix(A.row,A.col,1);
            vector<Matrix>baseS=baseSolution(B);
            cout<<"m="<<baseS.size()<<endl;//几何重数，几何重数不超过代数重数
            cout<<B<<endl;
            for (int i=0;i<baseS.size();++i){
                cout<<baseS[i]<<endl;
                s.push_back(baseS[i]);
            }
        }
    }
    if (s.size()==A.row){
        Matrix P=s[0];
        for (int i=1;i<s.size();++i){
            P=addH(P,s[i]);
        }
        cout<<P.message("P")<<endl;
        cout<<((P^-1)*A*P).message("P^-1AP")<<endl;
    }
    else{
        cout<<"Non-similar diagonalization"<<endl;
    }
}
/*
-2 1 1
0 2 0
-4 1 3

1 2 4 
2 4 8
4 8 16

(1,1,-1)*(1,1,2)
1 1 2
1 1 2
-1 -1 -2

x 0 0 0 0
1 x 0 0 0
0 1 x 0 0
0 0 1 x 0
0 0 0 1 x

-3 -12 -8 -11 
-7 -26 -20 -25 
-11 -40 -32 -39 
-15 -54 -44 -53

5 9 14 
8 15 23 
7 12 19
*/