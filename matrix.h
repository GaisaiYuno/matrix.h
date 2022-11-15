#include <cassert>
#include <iostream>
#include <vector>
#include <cstring>
struct Matrix{
    std::string Message;
    std::vector<std::vector<Num> >M;
    int row,col;//行数、列数
    Matrix(int rows,int cols,int value=0){
        row=rows,col=cols;
        M.resize(row+1);
        for (int i=1;i<=row;++i){
            M[i].resize(col+1,(Num)(0));
        }
        if (value==1 && row==col){
            for (int i=1;i<=row;++i){
                M[i][i]=(Num)(1);
            }
        }
        if (row==1) Message="Row Vector";
        else if (col==1) Message="Column Vector";
        else Message="Matrix";
    }
    void init(int rows,int cols){
        row=rows,col=cols;
        M.resize(row+1);
        for (int i=1;i<=row;++i){
            M[i].resize(col+1,(Num)(0));
        }
        Message="OK";
    }
    Matrix(int rows,int cols,std::vector<Num>v){
        row=rows,col=cols;
        for (int i=1;i<=row;++i){
            for (int j=1;j<=col;++j){
                M[i][j]=v[(i-1)*col+j-1];
            }
        }
    }
    Matrix(){
        row=col=0;
    }
    std::vector<Num>&operator[](int i){
        return M[i];
    }
    void identityMatrix(){
        assert(row==col);
        for (int i=1;i<=row;++i){
            M[i][i]=1;
        }
    }
    void diag(std::vector<Num>V){
        Matrix((int)V.size(),(int)V.size());
        for (int i=0;i<(int)V.size();++i){
            M[i+1][i+1]=V[i];
        }
    }
    //矩阵的初等行、列变换，type='R'行，type='C'列
    void swap(char type,int x,int y){
        if (type=='R'){
            assert(1<=x && x<=row && 1<=y && y<=row);
            for (int i=1;i<=col;++i){
                std::swap(M[x][i],M[y][i]);
            }
        }
        else if (type=='C'){
            assert(1<=x && x<=col && 1<=y && y<=col);
            for (int i=1;i<=row;++i){
                std::swap(M[i][x],M[i][y]);
            }
        }
        else {
            assert(0);
        }
    }
    void times(char type,int x,Num t){
        if (type=='R'){
            assert(1<=x && x<=row);
            for (int i=1;i<=col;++i){
                M[x][i]=t*M[x][i];
            }
        }
        else if (type=='C'){
            assert(1<=x && x<=col);
            for (int i=1;i<=row;++i){
                M[i][x]=t*M[i][x];
            }
        }
        else {
            assert(0);
        }
    }
    void addtimes(char type,int x,Num t,int y){//x行/列的t倍加到y上
        if (type=='R'){
            assert(1<=x && x<=row && 1<=y && y<=row);
            for (int i=1;i<=col;++i){
                M[y][i]=M[y][i]+t*M[x][i];
            }
        }
        else if (type=='C'){
            assert(1<=x && x<=col && 1<=y && y<=col);
            for (int i=1;i<=row;++i){
                M[i][y]=M[i][y]+t*M[i][x];
            }
        }
        else {
            assert(0);
        }
    }
    Num sum(char type,int x){
        if (type=='R'){
            Num s=0;
            for (int i=1;i<=col;++i){
                s=s+M[x][i];
            }
            return s;
        }
        else if (type=='C'){
            Num s=0;
            for (int i=1;i<=row;++i){
                s=s+M[i][x];
            }
            return s;
        }
        else {
            assert(0);
        }
        return 0;
    }
    Matrix transpose(){//矩阵的转置
        Matrix B(col,row);
        for (int i=1;i<=B.row;++i){
            for (int j=1;j<=B.col;++j){
                B[i][j]=M[j][i];
            }
        }
        B.Message="Matrix Transposed";
        return B;
    }
};
std::istream& operator >> (std::istream &in,Matrix &A){
    int row,col;
    std::cout<<"Please enter the row and col of the matrix"<<std::endl;
    std::cin>>row>>col;
    assert(row>=1 && col >=1);
    std::cout<<"Please enter the matrix"<<std::endl;
    A.init(row,col);
    for (int i=1;i<=row;++i){
        for (int j=1;j<=col;++j){
            std::cin>>A[i][j];
        }
    }
    A.Message="This is a matrix";
    return in;
}
std::ostream& operator << (std::ostream &out,const Matrix &A){
    std::cout<<A.Message<<std::endl;
    std::cout<<A.row<<" by "<<A.col<<std::endl;
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            std::cout<<A.M[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
	return out;
}
bool operator == (Matrix A,Matrix B){
    return A.M==B.M;
}

Matrix Inverse(Matrix A){//求逆矩阵
    assert(A.row==A.col);
    int n=A.row,m=A.col;
    Matrix B(A.row,A.col);
    B.identityMatrix();
    for (int i=1;i<=std::min(n,m);++i){
        int r=i;
        for (int j=i;j<=n;++j){
            if (!(A[j][i]==(Num)(0))) r=j;
        }
        A.swap('R',i,r),B.swap('R',i,r);
        if (A[i][i]==(Num)(0)){
            B.Message="Not full rank!";
            return B;
        }
        Num inv=(Num)(Num(0)-((Num)(1))/A[i][i]);
        for (int j=1;j<=n;++j){
            if (j==i) continue;
            Num t=A[j][i]*inv;
            A.addtimes('R',i,t,j);
            B.addtimes('R',i,t,j);
        }
    }
    for (int i=1;i<=n;++i){
        Num inv=((Num)(1))/A[i][i];
        A.times('R',i,inv);
        B.times('R',i,inv);
    }
    B.Message="Matrix Inversed";
    return B;
}
//化成简化的阶梯型矩阵，可选是否在前面形成一个单位矩阵，即是否交换列
Matrix Gauss(Matrix A,bool swapCol=false){
    int n=A.row,m=A.col;
    for (int i=1;i<=std::min(n,m);++i){
        int r=i;
        for (int j=i;j<=n;++j){
            if (!(A[j][i]==(Num)(0))) r=j;
        }
        A.swap('R',r,i);
        if (A[i][i]==(Num)(0)){
            continue;
        }
        Num inv=(Num)(Num(0)-((Num)(1))/A[i][i]);
        // std::cout<<A[i][i]<<" "<<inv<<std::endl;
        for (int j=1;j<=n;++j){
            if (j==i) continue;
            Num t=A[j][i]*inv;
            A.addtimes('R',i,t,j);
        }
    }
    // std::cout<<A<<std::endl;
    for (int i=1;i<=std::min(n,m);++i){
        if (!(A[i][i]==(Num)(0))){
            A.times('R',i,(Num)(1)/A[i][i]);
        }
    }
    if (swapCol==true){
        for (int i=1;i<=n;++i){
            for (int j=1;j<=m;++j){
                // std::cout<<A[i][j]<<" "<<(A[i][j]-(Num)(1))<<std::endl;
                if (A[i][j]==(Num)(1)){
                    A.swap('C',i,j);
                    break;
                }
            }
        }
    }
    A.Message="Matrix is in Gauss form";
    return A;
}
Num Determinant(Matrix A){
    int n=A.row,m=A.col;
    assert(n==m);
    Num sign=(Num)(1);
    for (int i=1;i<=std::min(n,m);++i){
        if (i>m){
            break;
        }
        int r=i;
        for (int j=i;j<=n;++j){
            if (!(A[j][i]==(Num)(0))) r=j;
        }
        A.swap('R',r,i);
        if (i!=r) sign=(Num)(0)-sign;
        if (A[i][i]==(Num)(0)){
            return (Num)(0);
        }
        Num inv=(Num)(Num(0)-((Num)(1))/A[i][i]);
        for (int j=1;j<=n;++j){
            if (j==i) continue;
            Num t=A[j][i]*inv;
            A.addtimes('R',i,t,j);
        }
    }
    for (int i=1;i<=n;++i){
        sign=sign*A[i][i];
    }
    return sign;
}
Matrix operator * (Matrix A,Matrix B){
    assert(A.col==B.row);
    Matrix C(A.row,B.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=B.col;++j){
            for (int k=1;k<=A.col;++k){
                C[i][j]=C[i][j]+A[i][k]*B[k][j];
            }
        }
    }
    return C;
}
Matrix operator * (Num lambda,Matrix A){
    Matrix B(A.row,A.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=B.col;++j){
            B[i][j]=lambda*A[i][j];
        }
    }
    return B;
}
Matrix operator + (Matrix A,Matrix B){
    assert(A.row==B.row && A.col==B.col);
    Matrix C(A.row,A.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    return C;
}
Matrix operator / (Num x,Matrix A){
    return x*Inverse(A);
}
Matrix operator / (Matrix A,Matrix B){
    return A*Inverse(B);
}
Matrix operator ^ (Matrix A,int k){
    assert(A.row==A.col);
    k--;
    Matrix base=A;
    while (k){
        if (k&1) base=base*A;
        A=A*A;
        k>>=1;
    }
    return base;
}
Num tr(Matrix A){
    assert(A.row==A.col);
    Num ans=0;
    for (int i=1;i<=A.row;++i){
        ans=ans+A[i][i];
    }
    return ans;
}
int rk(Matrix A){
    Matrix B=Gauss(A);
    int rk=0;
    for (int i=1;i<=B.row;++i){
        bool flag=false;
        for (int j=1;j<=B.col;++j){
            if (!(B[i][j]==(Num)(0))){
                flag=true;
                break;
            }
        }
        if (flag) rk++;
    }
    return rk;
}
//分裂成行向量和列向量
std::vector<Matrix> breakAsVector(Matrix A,char type){
    std::vector<Matrix> vectors;
    if (type=='C'){//列向量
        for (int i=1;i<=A.col;++i){
            Matrix tmp(A.row,1);
            for (int j=1;j<=A.row;++j){
                tmp[j][1]=A[j][i];
            }
            tmp.Message="eta"+std::to_string(i);
            vectors.push_back(tmp);
        }
    }
    else if (type=='R'){//行向量
        for (int i=1;i<=A.row;++i){
            Matrix tmp(1,A.col);
            for (int j=1;j<=A.col;++j){
                tmp[1][j]=A[i][j];
            }
            tmp.Message="eta"+std::to_string(i);
            vectors.push_back(tmp);
        }
    }
    return vectors;
}
Matrix addHorizontal(Matrix A,Matrix B){
    assert(A.row==B.row);
    Matrix C(A.row,A.col+B.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            C[i][j]=A[i][j];
        }
        for (int j=1;j<=B.col;++j){
            C[i][A.col+j]=B[i][j];
        }
    }
    return C;
}
Matrix addVertical(Matrix A,Matrix B){
    assert(A.col==B.col);
    Matrix C(A.row+B.row,A.col);
    for (int i=1;i<=A.col;++i){
        for (int j=1;j<=A.row;++j){
            C[j][i]=A[j][i];
        }
        for (int j=1;j<=B.row;++j){
            C[A.row+j][i]=B[j][i];
        }
    }
    return C;
}
std::vector<int> genVector(int l,int r){
    std::vector<int> ret;
    for (int i=l;i<=r;++i) ret.push_back(i);
    return ret;
}
Matrix subMatrix(Matrix A,std::vector<int>rowChoose,std::vector<int>colChoose){
    Matrix B(rowChoose.size(),colChoose.size());
    for (int i=0;i<rowChoose.size();++i){
        for (int j=0;j<colChoose.size();++j){
            B[i+1][j+1]=A[rowChoose[i]][colChoose[j]];
        }
    }
    return B;
}
bool isSwapable(Matrix A,Matrix B){
    return A*B==B*A;
}
//求出 A 的基础解系
std::vector<Matrix> baseSolution(Matrix A){
    Matrix B=Gauss(A,true);
    int n=A.col,r=rk(A);
    return breakAsVector(addVertical((Num)(-1)*(subMatrix(B,genVector(1,r),genVector(r+1,n))),Matrix(n-r,n-r,1)), 'C');
}