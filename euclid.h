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
Num length(Matrix A){
    return Num(0,1,(A&A).x);
}
Num angle(Matrix A,Matrix B){
    return (A&B)/(length(A)*length(B));
}
std::pair<Matrix,Matrix> identilize(Matrix v){
    return std::make_pair((Num(1)/length(v))*v,(Num(-1)/length(v))*v);
}
Matrix houseHolder(Matrix v){
    v=identilize(v).first;
    int n=v.row;
    return Matrix(n,n,1)-(Num(2)*v*v.transpose());
}
#endif