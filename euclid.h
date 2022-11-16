//欧氏空间
#include "matrix.h"
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
Matrix Discrete(Num (*F)(Num),Num l,Num r,Num step){
    std::vector<Num>v;
    for (Num i=l;i<=r;i=i+step){
        // std::cerr<<i<<std::endl;
        v.push_back(F(i));
    }
    return Matrix('R',v);
}
void Cauchy_Schwarz(Matrix A,Matrix B){
    std::cout<<(A&B)*(A&B)<<"<="<<(A&A)*(B&B)<<std::endl;
}