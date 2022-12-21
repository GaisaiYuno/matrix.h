//欧氏空间
// #ifndef MATRIX
// #else
// #define MATRIX
#include "matrix.h"
// #endif
Num operator & (Matrix A,Matrix B){
    assert(A.row==B.row && A.col==B.col);
    Matrix C(A.row,A.col);
    Num ret=(Num)(0);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            ret=ret+A[i][j]*B[i][j];
        }
    }
    return ret;
}
Matrix Discrete(Num (*F)(frac),frac l,frac r,frac step){
    std::vector<Num>v;
    for (frac i=l;i<=r;i=i+step){
        v.push_back(F(i));
    }
    return Matrix('R',v);
}
void Cauchy_Schwarz(Matrix A,Matrix B){
    std::cout<<(A&B)*(A&B)<<"<="<<(A&A)*(B&B)<<std::endl;
}
std::vector<Matrix> Schmidt(std::vector<Matrix>alpha){
    int s=alpha.size();
    std::vector<Matrix>beta;
    for (int i=1;i<=s;++i){
        Matrix beta_i=alpha[i-1];
        for (int j=1;j<=i-1;++j){
            Num lambda=(alpha[i-1]&beta[j-1])/(beta[j-1]&beta[j-1]);
            beta_i=beta_i-lambda*beta[j-1];
        }
        beta_i.Message="\\beta_"+std::to_string(i);
        beta.push_back(beta_i);
    }
    return beta;
}
bool isOrthogonalMatrix(Matrix A){
    assert(A.row==A.col);
    return A*A.transpose()==Matrix(A.row,A.col,1);
}


#ifndef SQRT_FIELD

#else
std::string Arccos(Num x){
    if (x==Num("0")) return "\\pi/2";
    if (x==Num("1/2")) return "\\pi/3";
    if (x==Num("1/2\3")) return "\\pi/6";
    if (x==Num("1")) return "0";
    // std::cout<<x<<std::endl;
    // std::cout<<x.x<<" "<<x.y<<std::endl;
    return "arccos("+to_latex(x.eval(),0)+")";
}
Num length(Matrix A){
    return Num(sqrtNum(0,1,(A&A).eval().x));
}
Num angle(Matrix A,Matrix B){
    return (A&B)/(length(A)*length(B));
}
std::pair<Matrix,Matrix> identilize(Matrix v){
    return std::make_pair((Num(1)/length(v))*v,(Num(-1)/length(v))*v);
}
Matrix proj(Matrix A,Matrix B){
    return (A&B)/length(A);
}
Matrix proj_vec(Matrix A,Matrix B){
    return proj(A,B)*identilize(A).first;
}
Matrix Nvec(Matrix A){
    A.resize(1,3);
    return A;
}
Matrix cross(Matrix A,Matrix B){
    if (A.row>A.col && B.row>B.col) return cross(A.transpose(),B.transpose()).transpose();
    assert(A.row==1 && A.col==3 && B.row==1 && B.col==3);
    Matrix ret(1,3);
    ret[1][1]=A[1][2]*B[1][3]-A[1][3]*B[1][2];
    ret[1][2]=-A[1][1]*B[1][3]+A[1][3]*B[1][1];
    ret[1][3]=A[1][1]*B[1][2]-A[1][2]*B[1][1];
    return ret;
}
Matrix Plane(Matrix V,Matrix P){
    Matrix ret=V;
    ret.resize(1,4);
    ret[1][4]=(V&P);
    return ret;
}
Matrix Plane(Matrix A,Matrix B,Matrix C){
    Matrix ret=cross(B-A,C-A);
    ret.resize(1,4);
    ret[1][4]=Determinant(addV(std::vector<Matrix>{-A,B-A,C-A}));
    return ret;
}
Matrix toIntercept(Matrix pl){
    assert(!(pl[1][4]==(Num)(0)));
    return Matrix('R',std::vector<Num>{-pl[1][1]/pl[1][4],-pl[1][2]/pl[1][4],-pl[1][3]/pl[1][4]});
}
std::pair<Matrix,Matrix> toLine(Matrix A,Matrix B){
    Matrix S=addV(A,B);
    std::vector<Matrix>baseS=baseSolution(subMatrix(S,1,2,1,3),-subMatrix(S,1,2,4,4));
    return std::make_pair(baseS.back().transpose(),baseS.front().transpose());
}
Num dist(Matrix P,Matrix A){
    // std::cout<<(P&Nvec(A))+A[1][4]<<std::endl;
    // std::cout<<(A&A)<<std::endl;
    return abs((P&Nvec(A))+A[1][4])/length(Nvec(A));
}
void output(Matrix P){
    std::cout<<P[1][1]<<"X+"<<P[1][2]<<"Y+"<<P[1][3]<<"Z+"<<P[1][4]<<"=0"<<std::endl;
}
void output(Matrix R0,Matrix S){
    std::cout<<"(X-"<<R0[1][1]<<")/"<<S[1][1]<<"=(Y-"<<R0[1][2]<<")/"<<S[1][2]<<"=(Z-"<<R0[1][3]<<")/"<<S[1][3]<<std::endl;
}
Matrix houseHolder(Matrix v){
    v=identilize(v).first;
    int n=v.row;
    return Matrix(n,n,1)-(Num(2)*v*v.transpose());
}
#endif