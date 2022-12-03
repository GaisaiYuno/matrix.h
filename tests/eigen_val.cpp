#define Num poly
#include "poly.h"
#include "matrix.h"
using namespace std;
int main(){
    Matrix A;
    cin>>A;
    // cout<<A<<endl;
    Matrix B=A;
    for (int i=1;i<=A.row;++i){
        B[i][i]=B[i][i]-Num("l");
    }
    cout<<"Eigen Poly"<<endl;
    // poly x=Determinant(B);
    // cout<<x<<endl;
    _poly x=Determinant(B).x;
    cout<<x<<endl;
    upoly _x;
    _x.init_from_poly(x);
    vector<pair<upoly,int> >v=Factorization(_x);
    cout<<"Factorization"<<endl;
    cout<<"C";
    for (int i=0;i<v.size();++i){
        cout<<"("<<v[i].first<<")^"<<v[i].second;
    }
    cout<<endl;
    vector<Matrix>s;
    // int m;
    // cin>>m;
    for (int i=0;i<v.size();++i){
        if (v[i].first.deg()==1){
            Num lambda=poly(poly_ele((frac)(0)-v[i].first[0]));
            cout<<"lambda="<<lambda<<endl;
            cout<<"n="<<v[i].second<<endl;//代数重数
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
    // for (int i=0;i<m;++i){
    //     Num lambda;
    //     cin>>lambda;
    //     cout<<"lambda="<<lambda<<endl;
    //     // cout<<"n="<<v[i].second<<endl;//代数重数
    //     Matrix B=A-lambda*Matrix(A.row,A.col,1);
    //     vector<Matrix>baseS=baseSolution(B);
    //     // cout<<"m="<<baseS.size()<<endl;//几何重数，几何重数不超过代数重数
    //     cout<<B<<endl;
    //     for (int i=0;i<baseS.size();++i){
    //         cout<<baseS[i]<<endl;
    //         s.push_back(baseS[i]);
    //     }
    // }
    if (s.size()==A.row){
        Matrix P=s[0];
        for (int i=1;i<s.size();++i){
            P=addHorizontal(P,s[i]);
        }
        cout<<P<<endl;
        cout<<(P^-1)*A*P<<endl;
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