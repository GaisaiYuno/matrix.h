#include "matrix.h"
namespace strassen{
    int upper(int x){
        if ((x&(-x))==x) return x;
        int l=1;
        while (x) x>>=1,l<<=1;
        return l;
    }
    Matrix strassen_mul(Matrix A,Matrix B){
        // std::cout<<A<<" "<<B<<std::endl;
        static int original_row,original_col;
        if (A.row==1 && A.col==1 && B.row==1 && B.col==1){
            return Matrix(A[1][1]*B[1][1]);
        }
        bool resized=false;
        if (A.col!=B.row){
            assert(0);
        }
        else if (A.row!=A.col || B.row!=B.col || upper(A.row)!=A.row){
            int sz=upper(std::max(std::max(A.row,A.col),std::max(B.row,B.col)));
            original_row=A.row,original_col=B.col;
            A.resize(sz,sz);
            B.resize(sz,sz);
            resized=true;
        }
        int n=A.row;

        Matrix A11=subMatrix(A,1,n>>1,1,n>>1);
        Matrix A12=subMatrix(A,1,n>>1,(n>>1)+1,n);
        Matrix A21=subMatrix(A,1+(n>>1),n,1,n>>1);
        Matrix A22=subMatrix(A,1+(n>>1),n,1+(n>>1),n);

        Matrix B11=subMatrix(B,1,n>>1,1,n>>1);
        Matrix B12=subMatrix(B,1,n>>1,(n>>1)+1,n);
        Matrix B21=subMatrix(B,1+(n>>1),n,1,n>>1);
        Matrix B22=subMatrix(B,1+(n>>1),n,1+(n>>1),n);

        Matrix S1=B12-B22;
        Matrix S2=A11+A12;
        Matrix S3=A21+A22;
        Matrix S4=B21-B11;
        Matrix S5=A11+A22;
        Matrix S6=B11+B22;
        Matrix S7=A12-A22;
        Matrix S8=B21+B22;
        Matrix S9=A11-A21;
        Matrix S10=B11+B12;

        Matrix P1=strassen_mul(A11,S1);
        Matrix P2=strassen_mul(S2,B22);
        Matrix P3=strassen_mul(S3,B11);
        Matrix P4=strassen_mul(A22,S4);
        Matrix P5=strassen_mul(S5,S6);
        Matrix P6=strassen_mul(S7,S8);
        Matrix P7=strassen_mul(S9,S10);

        //只用7次运算，相比八次。

        Matrix C11=P5+P4-P2+P6;
        Matrix C12=P1+P2;
        Matrix C21=P3+P4;
        Matrix C22=P5+P1-P3-P7;

        Matrix ans=addH(addV(C11,C21),addV(C12,C22));
        if (resized){
            ans.resize(original_row,original_col);
        }
        return ans;
    }
    Matrix strassen_inverse(Matrix A){
        static int original_row,original_col;
        if (A.row==1 && A.col==1){
            return Matrix((Num)(1)/A[1][1]);
        }
        bool resized=false;
        if (A.col!=A.row){
            assert(0);
        }
        else if (upper(A.row)!=A.row){
            int sz=upper(A.row);
            original_row=A.row,original_col=A.col;
            A.resize(sz,sz);
            resized=true;
        }
        int n=A.row;

        Matrix A11=subMatrix(A,1,n>>1,1,n>>1);
        Matrix A12=subMatrix(A,1,n>>1,(n>>1)+1,n);
        Matrix A21=subMatrix(A,1+(n>>1),n,1,n>>1);
        Matrix A22=subMatrix(A,1+(n>>1),n,1+(n>>1),n);

        Matrix P1=strassen_inverse(A11);
        Matrix P2=strassen_mul(A21,P1);
        Matrix P3=strassen_mul(P1,A12);
        Matrix P4=strassen_mul(A21,P3);
        Matrix P5=P4-A22;
        Matrix P6=strassen_inverse(P5);
        Matrix P7=strassen_mul(P3,strassen_mul(P6,P2));

        Matrix C11=P1-P7;
        Matrix C12=strassen_mul(P3,P6);
        Matrix C21=strassen_mul(P6,P2);
        Matrix C22=(Num)(-1)*P6;

        Matrix ans=addH(addV(C11,C21),addV(C12,C22));
        if (resized){
            ans.resize(original_row,original_col);
        }
        return ans;
    }
    Num strassen_det(Matrix A){
        static int original_row,original_col;
        if (A.row==1 && A.col==1){
            return A[1][1];
        }
        bool resized=false;
        if (A.col!=A.row){
            assert(0);
        }
        else if (upper(A.row)!=A.row){
            int sz=upper(A.row);
            original_row=A.row,original_col=A.col;
            A.resize(sz,sz);
            resized=true;
        }
        int n=A.row;
        Matrix A11=subMatrix(A,1,n>>1,1,n>>1);
        Matrix A12=subMatrix(A,1,n>>1,(n>>1)+1,n);
        Matrix A21=subMatrix(A,1+(n>>1),n,1,n>>1);
        Matrix A22=subMatrix(A,1+(n>>1),n,1+(n>>1),n);
        return strassen_det(A11)*strassen_det(A22-strassen_mul(A21,strassen_mul(strassen_inverse(A11),A12)));
    }
}