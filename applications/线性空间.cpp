#include "poly.h"
#include "matrix.h"
using namespace std;
struct Base{
    Matrix<poly> B;
    Base(){}
    Base(Matrix<poly> _B){
        assert(Determinant(_B)!=0);
        B=_B;
    }
};
struct Trans{
    Base B;
    Matrix<poly> A;
    Trans(){}
    Trans(Matrix<poly> _A){
        A=_A;
        B.B=Matrix<poly>(A.row,A.col,1);
    }
    void TransBase(Base C){
        Matrix<poly> P=(B.B^(-1))*C.B;
        A=(P^(-1))*A*P;
    }
};
int main(){
    Matrix<poly> P=Matrix<poly>(4,4,vector<poly>{1,0,4,0,0,1,0,4,2,0,1,0,0,2,0,1});
    Trans A(P);
    Base P2=Matrix<poly>(4,4,vector<poly>{0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0});
    A.TransBase(P2);
    cout<<A.A<<endl;
}