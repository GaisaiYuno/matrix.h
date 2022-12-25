#include "poly.h"
#define Num poly
#include "matrix.h"
#include "euclid.h"
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
    cout<<"特征多项式"<<endl;
    _poly x=Determinant(B).x;
    cout<<x<<endl;
    out<<to_latex(B,"vmatrix")<<"="<<to_latex(x)<<endl<<endl;
    upoly _x;
    _x.init_from_poly(x);
    cpoly v=Factorization(_x);
    v.sort();
    cout<<"对其进行分解"<<endl<<v<<endl;
    out<<"对其进行分解，得到，"<<to_latex(v)<<endl<<endl;
    vector<Matrix>s;
    for (int i=0;i<v.v.size();++i){
        if (v.v[i].first.deg()==1){
            Num lambda=poly(poly_ele((frac)(0)-v.v[i].first[0]));
            out<<"对于特征值 $\\lambda="<<to_latex(lambda,0)<<"$ 我们有"<<endl<<endl;
            cout<<"特征值 lambda="<<lambda<<endl;
            cout<<"代数重数 n="<<v.v[i].second<<endl;//代数重数
            Matrix B=A-lambda*Matrix(A.row,A.col,1);
            vector<Matrix>baseS=baseSolution(B);
            baseS=Schmidt(baseS);//进行施密特正交化
            cout<<"几何重数 m="<<baseS.size()<<endl;//几何重数，几何重数不超过代数重数
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
        cout<<"矩阵可以相似对角化，将这些向量组合在一起，"<<endl<<endl;
        out<<"矩阵可以相似对角化，将这些向量组合在一起，"<<endl<<endl;
        for (int i=1;i<s.size();++i){
            P=addH(P,s[i]);
        }
        cout<<P.message("P")<<endl;
        cout<<((P^-1)*A*P).message("P^{-1}AP")<<endl;
        out<<to_latex(P.message("P"))<<endl<<endl;
        out<<to_latex(((P^-1)*A*P).message("P^{-1}AP"))<<endl<<endl;
        //不是对称矩阵，就不正交化。
        if (A!=A.transpose()){
            return 0;
        }
        cout<<"矩阵是对称阵，继续进行正交化"<<endl<<endl;
        out<<"矩阵是对称阵，继续进行正交化"<<endl<<endl;
        vector<Matrix>v=breakAsVector(P,'C');
        for (int i=0;i<v.size();++i){
            v[i]=identilize(v[i]).first;
        }
        Matrix Q=addH(v);
        //Q是一个正交矩阵
        cout<<Q.message("Q")<<endl;
        cout<<((Q.transpose())*A*Q).message("Q^{-1}AQ")<<endl;
        out<<to_latex(Q.message("Q"))<<endl<<endl;
        out<<to_latex(((Q.transpose())*A*Q).message("Q^{-1}AQ"))<<endl<<endl;
        Matrix L=(Q.transpose())*A*Q;
        Matrix R(L.row,L.col);
        for (int i=1;i<=L.row;++i){
            if (L[i][i]!=poly(0)) R[i][i]=1/Sqrt(abs(L[i][i]));
            else R[i][i]=1;
        }
        cout<<"进行替换产生规范标准型"<<endl<<endl;
        out<<"进行替换产生规范标准型"<<endl<<endl;
        Matrix S=Q*R;
        //Sx这个替换可以使二次型化为规范标准型
        cout<<S.message("S")<<endl;
        cout<<((S.transpose())*A*S).message("S^{-1}AS")<<endl;
        out<<to_latex(S.message("S"))<<endl<<endl;
        out<<to_latex(((S.transpose())*A*S).message("S^{-1}AS"))<<endl<<endl;
    }
    else{
        cout<<"矩阵不可相似对角化"<<endl;
        out<<"矩阵不可相似对角化"<<endl<<endl;
    }
    out<<end_latex()<<endl<<endl;
    out.close();
}
/*
2 0 2
0 2 2
2 2 4

-1 1/2 -1 
1 1/2 -1 
0 1 1
*/