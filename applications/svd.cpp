#include "poly.h"
#include "matrix.h"
#include "euclid.h"
#include <fstream>
using namespace std;
ofstream out;
Matrix<poly> Lambda;
Matrix<poly> diagonalize(Matrix<poly> A){
    assert(A.row==A.col);
    out<<to_latex(A)<<endl<<endl;
    Matrix<poly> B=A;
    for (int i=1;i<=A.row;++i){
        B[i][i]=B[i][i]-poly("l");
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
    vector<Matrix<poly> >s;
    for (int i=0;i<v.v.size();++i){
        if (v.v[i].first.deg()==1){
            poly lambda=poly(poly_ele(-v.v[i].first[0]));
            out<<"对于特征值 $\\lambda="<<to_latex(lambda,0)<<"$ 我们有"<<endl<<endl;
            cout<<"特征值 lambda="<<lambda<<endl;
            cout<<"代数重数 n="<<v.v[i].second<<endl;//代数重数
            Matrix<poly> B=A-lambda*Matrix<poly>(A.row,A.col,1);
            vector<Matrix<poly> >baseS=baseSolution(B);
            baseS=Schmidt(baseS);//进行施密特正交化
            cout<<"几何重数 m="<<baseS.size()<<endl;//几何重数，几何重数不超过代数重数
            cout<<B<<endl;
            for (int i=0;i<baseS.size();++i){
                cout<<baseS[i]<<endl;
                s.push_back(baseS[i]);
                out<<to_latex(baseS[i])<<endl<<endl;
            }
        }
        else if (v.v[i].first.deg()==2){
            poly lambda_1,lambda_2;
            frac a=v.v[i].first[2],b=v.v[i].first[1],c=v.v[i].first[0];
            frac delta=b*b-4*a*c;
            lambda_1=poly_ele(sqrtNum(-b/(2*a),1/(2*a),delta));
            lambda_2=poly_ele(sqrtNum(-b/(2*a),-1/(2*a),delta));

            out<<"对于特征值 $\\lambda="<<to_latex(lambda_1,0)<<"$ , 我们有"<<endl<<endl;
            cout<<"特征值 lambda="<<lambda_1<<endl;
            cout<<"代数重数 n="<<v.v[i].second<<endl;//代数重数
            Matrix<poly> B=A-lambda_1*Matrix<poly>(A.row,A.col,1);
            vector<Matrix<poly> >baseS=baseSolution(B);
            cout<<"几何重数 m="<<baseS.size()<<endl;//几何重数，几何重数不超过代数重数
            cout<<B<<endl;
            for (int i=0;i<baseS.size();++i){
                cout<<baseS[i]<<endl;
                s.push_back(baseS[i]);
                out<<to_latex(baseS[i])<<endl<<endl;
            }

            out<<"对于特征值 $\\lambda="<<to_latex(lambda_2,0)<<"$ , 我们有"<<endl<<endl;
            cout<<"特征值 lambda="<<lambda_2<<endl;
            cout<<"代数重数 n="<<v.v[i].second<<endl;//代数重数
            B=A-lambda_2*Matrix<poly>(A.row,A.col,1);
            baseS=baseSolution(B);
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
        Matrix<poly> P=s[0];
        cout<<"矩阵可以相似对角化，将这些向量组合在一起，"<<endl<<endl;
        out<<"矩阵可以相似对角化，将这些向量组合在一起，"<<endl<<endl;
        for (int i=1;i<s.size();++i){
            P=addH(P,s[i]);
        }
        cout<<P.message("P")<<endl;
        cout<<((P^-1)*A*P).message("P^{-1}AP")<<endl;
        out<<to_latex(P.message("P"))<<endl<<endl;
        out<<to_latex(((P^-1)*A*P).message("P^{-1}AP"))<<endl<<endl;
        cout<<"矩阵是对称阵，继续进行正交化"<<endl<<endl;
        out<<"矩阵是对称阵，继续进行正交化"<<endl<<endl;
        vector<Matrix<poly> >v=breakAsVector(P,'C');
        for (int i=0;i<v.size();++i){
            v[i]=identilize(v[i]).first;
        }
        Matrix<poly> Q=addH(v);
        //Q是一个正交矩阵
        cout<<Q.message("Q")<<endl;
        cout<<((Q.transpose())*A*Q).message("Q^{-1}AQ")<<endl;
        Lambda=(Q.transpose())*A*Q;
        out<<to_latex(Q.message("Q"))<<endl<<endl;
        out<<to_latex(((Q.transpose())*A*Q).message("Q^{-1}AQ"))<<endl<<endl;
        return Q;
    }
    else{
        cout<<"矩阵不可相似对角化"<<endl;
        out<<"矩阵不可相似对角化"<<endl<<endl;
        assert(0);
    }
}
int main(){
    out.open("test.tex");
    Matrix<poly> A;
    cin>>A;
    int m=A.row,n=A.col;
    out<<begin_latex()<<endl<<endl;
    Matrix<poly> U=diagonalize(A*A.transpose());
    Matrix<poly> V=diagonalize(A.transpose()*A);
    // Matrix<poly> Sigma=U.transpose()*A*V.transpose();
    Matrix<poly> Sigma=Lambda.resize(m,n);
    for (int i=1;i<=min(m,n);++i){
        Sigma[i][i]=Sqrt(Sigma[i][i]);
    }
    cout<<U.message("U")<<endl;
    cout<<Sigma.message("Sigma")<<endl;
    cout<<V.message("V")<<endl;
    int k=min(n,m);
    for (int i=1;i<=min(n,m);++i){
        if (Sigma[i][i]==0){k=i-1;break;}
    }
    U.resize(m,k);
    Sigma.resize(k,k);
    V.resize(k,n);
    cout<<U.message("New U")<<endl;
    cout<<Sigma.message("New Sigma")<<endl;
    cout<<V.message("New V")<<endl;
    cout<<(U*Sigma*V).message("SVD")<<endl;
    out<<end_latex()<<endl<<endl;
    out.close();
}