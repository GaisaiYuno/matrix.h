#include "poly.h"
#define Num poly
#include "matrix.h"
//#include "euclid.h"
#include <fstream>
using namespace std;
int main(){
    ofstream out;
    out.open("test.tex");
    Matrix A;
    cin>>A;
    out<<begin_latex()<<endl<<endl;
    out<<to_latex(A)<<endl<<endl;
    Matrix B=A;
    for (int i=1;i<=A.row;++i){
        B[i][i]=B[i][i]-Num("l");
    }
    cout<<"Eigen Poly"<<endl;
    _poly x=Determinant(B).x;
    cout<<x<<endl;
    out<<to_latex(B,"vmatrix")<<"="<<to_latex(x)<<endl<<endl;
    upoly _x;
    _x.init_from_poly(x);
    cpoly v=Factorization(_x);
    v.sort();
    cout<<"Factorization"<<endl<<v<<endl;
    out<<"Factorize it then we have "<<to_latex(v)<<endl<<endl;
    vector<Matrix>s;
    for (int i=0;i<v.v.size();++i){
        if (v.v[i].first.deg()==1){
            Num lambda=poly(poly_ele((frac)(0)-v.v[i].first[0]));
            out<<"For eigen value $\\lambda="<<to_latex(lambda,0)<<"$ ,we have vectors,"<<endl<<endl;
            cout<<"lambda="<<lambda<<endl;
            cout<<"n="<<v.v[i].second<<endl;//代数重数
            Matrix B=A-lambda*Matrix(A.row,A.col,1);
            vector<Matrix>baseS=baseSolution(B);
            //baseS=Schmidt(baseS);
            cout<<"m="<<baseS.size()<<endl;//几何重数，几何重数不超过代数重数
            cout<<B<<endl;
            for (int i=0;i<baseS.size();++i){
                cout<<baseS[i]<<endl;
                s.push_back(baseS[i]);
                out<<to_latex(baseS[i])<<endl<<endl;
            }
        }
    }
    if (s.size()==A.row){
        Matrix P=s[0];
        out<<"Combine the vectors together then we get, "<<endl<<endl;
        for (int i=1;i<s.size();++i){
            P=addH(P,s[i]);
        }
        cout<<P.message("P")<<endl;
        cout<<((P^-1)*A*P).message("P^{-1}AP")<<endl;
        out<<to_latex(P.message("P"))<<endl<<endl;
        out<<to_latex(((P^-1)*A*P).message("P^{-1}AP"))<<endl<<endl;
    }
    else{
        cout<<"Non-similar diagonalization"<<endl;
        out<<"Non-similar diagonalization"<<endl<<endl;
    }
    out<<end_latex()<<endl<<endl;
    out.close();
}
/*
2 1 0 0
1 2 1 0
0 1 2 1
0 0 1 2

2 1 0 0 1
1 2 1 0 0
0 1 2 1 0
0 0 1 2 1
1 0 0 1 2


2 1 0 0 0 0
1 2 1 0 0 0
0 1 2 1 0 0
0 0 1 2 1 0
0 0 0 1 2 1
0 0 0 0 1 2

Please enter the row and col of the matrix
3 3
Please enter the matrix
2 2 -2
2 3 0
-2 0 1
Eigen Poly
-l^3+6l^2-3l-10
1
Factorization
(l-5)(l-2)(l+1)
lambda=5
n=1
m=1
Matrix
3 by 3
-3 2 -2 
2 -2 0 
-2 0 -4 

eta1
3 by 1
-2 
-2 
1 

lambda=2
n=1
m=1
Matrix
3 by 3
0 2 -2 
2 1 0 
-2 0 -1 

eta1
3 by 1
-1/2 
1 
1 

lambda=-1
n=1
m=1
Matrix
3 by 3
3 2 -2 
2 4 0 
-2 0 2 

eta1
3 by 1
1 
-1/2 
1 

P
3 by 3
-2 -1/2 1 
-2 1 -1/2 
1 1 1 

P^-1AP
3 by 3
5 0 0 
0 2 0 
0 0 -1
*/