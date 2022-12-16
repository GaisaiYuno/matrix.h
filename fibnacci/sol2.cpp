#include "poly.h"
#define Num poly
#include "matrix.h"
// #include "euclid.h"
#include <fstream>
using namespace std;
int main(){
    ofstream out;
    out.open("sol2.tex");
    Matrix A(3,3);
    A.Message="A";
    A[1][1]=-2,A[1][2]=1,A[1][3]=2;
    A[2][1]=1,A[2][2]=0,A[2][3]=0;
    A[3][1]=0,A[3][2]=1,A[3][3]=0;
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
            // baseS=Schmidt(baseS); 如果需要正交矩阵的话需要施密特正交化
            cout<<"m="<<baseS.size()<<endl;//几何重数，几何重数不超过代数重数
            cout<<B<<endl;
            for (int i=0;i<baseS.size();++i){
                cout<<baseS[i]<<endl;
                s.push_back(baseS[i]);
                out<<to_latex(baseS[i])<<endl<<endl;
            }
        }
        else if (v.v[i].first.deg()==2){
            Num lambda_1,lambda_2;
            frac a=v.v[i].first[2],b=v.v[i].first[1],c=v.v[i].first[1];
            frac delta=b*b-4*a*c;
            lambda_1=poly_ele(sqrtNum(-b/(2*a),1/(2*a),delta));
            lambda_2=poly_ele(sqrtNum(-b/(2*a),-1/(2*a),delta));
            out<<"For eigen value $\\lambda="<<to_latex(lambda_1,0)<<"$ ,we have vectors,"<<endl<<endl;
            cout<<"lambda="<<lambda_1<<endl;
            cout<<"n="<<v.v[i].second<<endl;//代数重数
            Matrix B=A-lambda_1*Matrix(A.row,A.col,1);
            vector<Matrix>baseS=baseSolution(B);
            cout<<"m="<<baseS.size()<<endl;//几何重数，几何重数不超过代数重数
            cout<<B<<endl;
            for (int i=0;i<baseS.size();++i){
                cout<<baseS[i]<<endl;
                s.push_back(baseS[i]);
                out<<to_latex(baseS[i])<<endl<<endl;
            }
            out<<"For eigen value $\\lambda="<<to_latex(lambda_2,0)<<"$ ,we have vectors,"<<endl<<endl;
            cout<<"lambda="<<lambda_2<<endl;
            cout<<"n="<<v.v[i].second<<endl;//代数重数
            B=A-lambda_2*Matrix(A.row,A.col,1);
            baseS=baseSolution(B);
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
        cout<<(P^(-1)).message("P^{-1}")<<endl;
        cout<<((P^-1)*A*P).message("P^{-1}AP")<<endl;
        Matrix Lambda=(P^-1)*A*P;
        out<<to_latex(P.message("P"))<<endl<<endl;
        out<<to_latex(((P^-1)*A*P).message("\\Lambda=PAP^{-1}"))<<endl<<endl;
        out<<"So $A^n=P^{-1}\\Lambda^n P$"<<endl<<endl;
        out<<"For calculating $A^n$, assume $\\Lambda^n=[a,0,0;0,b,0;0,0,c]$, then we have:"<<endl<<endl;
        Matrix _A(3,3);
        _A[1][1]=poly("a"),_A[2][2]=poly("b"),_A[3][3]=poly("c");
        cout<<P*_A*(P^-1)<<endl;
        out<<to_latex((P*_A*(P^-1))[1][1])<<endl<<endl;
        out<<"Then, substitute $a=("<<to_latex(Lambda[1][1],0)<<")^{n-1}$ and $b=("<<to_latex(Lambda[2][2],0)<<")^{n-1}$ and $c=("<<to_latex(Lambda[3][3],0)<<")^{n-1}$, we have the final answer"<<endl<<endl;
    }
    else{
        cout<<"Non-similar diagonalization"<<endl;
        out<<"Non-similar diagonalization"<<endl<<endl;
    }
    out<<end_latex()<<endl<<endl;
    out.close();
}