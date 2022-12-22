#ifndef _MATRIX_
#define _MATRIX_
#include <cassert>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
struct Matrix{
    std::string Message;
    std::vector<std::vector<Num> >M;
    int row,col;//行数、列数
    Matrix(Num x){
        row=1,col=1;
        M.resize(1+1);
        M[1].resize(1+1,x);
        Message="Single Element";
    }
    Matrix(char type,std::vector<Num>v){
        int n=v.size();
        if (type=='R'){
            M.resize(1+1);
            M[1].resize(n+1);
            for (int i=1;i<=n;++i){
                M[1][i]=v[i-1];
            }
            row=1,col=n;
            Message="Row Vector";
        }
        else if (type=='C'){
            M.resize(1+n);
            for (int i=1;i<=n;++i){
                M[i].resize(1+1);
                M[i][1]=v[i-1];
            }
            row=n,col=1;
            Message="Column Vector";
        }
        else{
            assert(0);
        }
    }
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
        if (row==1 && col==1) Message="Single Element";
        else if (row==1) Message="Row Vector";
        else if (col==1) Message="Column Vector";
        else Message="Matrix";
    }
    void init(int rows,int cols){
        row=rows,col=cols;
        M.resize(row+1);
        for (int i=1;i<=row;++i){
            M[i].resize(col+1,(Num)(0));
        }
        Message="Matrix";
    }
    Matrix & message(std::string m){
        Message=m;
        return *this;
    }
    Matrix(int rows,int cols,std::vector<Num>v){
        init(rows,cols);
        row=rows,col=cols;
        int cnt=0;
        for (int i=1;i<=row;++i){
            for (int j=1;j<=col;++j){
                M[i][j]=v[cnt++];
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
    void genRand(){
        srand(time(NULL));
        for (int i=1;i<=row;++i){
            for (int j=1;j<=col;++j){
                M[i][j]=Num(rand()%10);
            }
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
    Matrix& resize(int nrow,int ncol){
        row=nrow,col=ncol;
        M.resize(row+1);
        for (int i=1;i<=row;++i){
            M[i].resize(col+1);
        }
        return *this;
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
    static char name='A';
    A.Message=name;
    name++;
    return in;
}
std::ostream& operator << (std::ostream &out,const Matrix &A){
    std::cout<<A.Message<<std::endl;
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            std::cout<<A.M[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return out;
}
std::string to_latex(const Matrix &A,std::string type="bmatrix",bool begin=true){
    std::string ret="";
    if (begin) ret+="$";
    ret+=A.Message+"=";
    ret+="\\begin{"+type+"}\n";
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            ret+=to_latex(A.M[i][j],0);
            if (j!=A.col) ret+=" &";
            else ret+="\\\\\n";
        }
    }
    ret+="\\end{"+type+"}\n";
    if (begin) ret+="$";
    return ret;
}
#ifndef UTILS
std::vector<int> genVector(int l,int r){
    std::vector<int> ret;
    for (int i=l;i<=r;++i) ret.push_back(i);
    return ret;
}
Matrix diag(std::vector<Num>V){
    Matrix A=Matrix((int)V.size(),(int)V.size());
    for (int i=0;i<(int)V.size();++i){
        A[i+1][i+1]=V[i];
    }
    return A;
}
std::string begin_latex(){
    return "\\documentclass{article}\n\\usepackage{ctex,amsmath,xparse}\n\\begin{document}\n";
}
std::string end_latex(){
    return "\\end{document}\n";
}
#endif
#define UTILS
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
Num Determinant(Matrix A){
    int n=A.row,m=A.col;
    assert(n==m);
    if (n==3){
        return A[1][1]*A[2][2]*A[3][3]+A[1][2]*A[2][3]*A[3][1]+A[2][1]*A[3][2]*A[1][3]-A[1][3]*A[2][2]*A[3][1]-A[1][1]*A[2][3]*A[3][2]-A[1][2]*A[2][1]*A[3][3];
    }
    Num sign=(Num)(1);
    for (int i=1;i<=std::min(n,m)-1;++i){
        if (i>m){
            break;
        }
        int r=i;
        for (int j=n;j>=i;--j){
            if (!(A[j][i]==(Num)(0))) r=j;
        }
        A.swap('R',r,i);
        if (i!=r) sign=(Num)(0)-sign;
        if (A[i][i]==(Num)(0)){
            return (Num)(0);
        }
        Num inv=(Num)(Num(0)-((Num)(1))/A[i][i]);
        // std::cout<<"inv:"<<inv<<std::endl;
        for (int j=i+1;j<=n;++j){
            Num t=A[j][i]*inv;
            // std::cout<<"two num"<<A[j][i]<<" "<<inv<<std::endl;
            // std::cout<<"t:"<<t<<std::endl;
            A.addtimes('R',i,t,j);
        }
        // std::cout<<A<<std::endl;
    }
    for (int i=1;i<=n;++i){
        sign=sign*A[i][i];
    }
    return sign;
}
//化成简化的阶梯型矩阵，可选是否在前面形成一个单位矩阵，即是否交换列
Matrix Gauss(Matrix A,bool swapCol=false){
    int n=A.row,m=A.col;
    int rk=1;
    for (int i=1;i<=std::min(n,m);++i){
        int r=rk;
        for (int j=n;j>=rk;--j){
            if (!(A[j][i]==(Num)(0))) r=j;
        }
        A.swap('R',r,rk);
        if (A[rk][i]==(Num)(0)){
            continue;
        }
        Num inv=(Num)(Num(0)-((Num)(1))/A[rk][i]);
        for (int j=1;j<=n;++j){
            if (j==rk) continue;
            Num t=A[j][i]*inv;
            A.addtimes('R',rk,t,j);
        }
        //std::cout<<A<<std::endl;
        ++rk;
    }
    for (int i=1;i<=std::min(n,m);++i){
        for (int j=1;j<=m;++j){
            if (!(A[i][j]==(Num)(0))){
                A.times('R',i,(Num)(1)/A[i][j]);
                break;
            }
        }
    }
    if (swapCol==true){
        for (int i=1;i<=n;++i){
            for (int j=1;j<=m;++j){
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
bool isSwapable(Matrix A,Matrix B){
    return A*B==B*A;
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
Matrix operator - (Matrix A,Matrix B){
    assert(A.row==B.row && A.col==B.col);
    Matrix C(A.row,A.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            C[i][j]=A[i][j]-B[i][j];
        }
    }
    return C;
}
Matrix operator - (Matrix A){
    Matrix C(A.row,A.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            C[i][j]=(Num)(0)-A[i][j];
        }
    }
    return C;
}
Matrix operator / (Num x,Matrix A){
    return x*Inverse(A);
}
Matrix operator / (Matrix A,Num x){
    return (Num(1)/x)*A;
}
Matrix operator / (Matrix A,Matrix B){
    return A*Inverse(B);
}
Matrix operator ^ (Matrix A,int k){
    assert(A.row==A.col);
	if (k==0){
		return Matrix(A.row,A.col,1);
	}
	if (k<0){
		return Inverse(A)^(-k);
	}
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
            tmp.Message="\\eta_"+std::to_string(i);
            vectors.push_back(tmp);
        }
    }
    else if (type=='R'){//行向量
        for (int i=1;i<=A.row;++i){
            Matrix tmp(1,A.col);
            for (int j=1;j<=A.col;++j){
                tmp[1][j]=A[i][j];
            }
            tmp.Message="\\eta_"+std::to_string(i);
            vectors.push_back(tmp);
        }
    }
    return vectors;
}
Matrix addH(Matrix A,Matrix B){
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
Matrix addV(Matrix A,Matrix B){
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
Matrix addH(std::vector<Matrix>v){
    Matrix ret=v[0];
    for (int i=1;i<v.size();++i) ret=addH(ret,v[i]);
    return ret;
}
Matrix addV(std::vector<Matrix>v){
    Matrix ret=v[0];
    for (int i=1;i<v.size();++i) ret=addV(ret,v[i]);
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
Matrix subMatrix(Matrix A,int rlb,int rub,int clb,int cub){
    Matrix B(rub-rlb+1,cub-clb+1);
    for (int i=rlb;i<=rub;++i){
        for (int j=clb;j<=cub;++j){
            B[i-rlb+1][j-clb+1]=A[i][j];
        }
    }
    return B;
}
//求出 A 的基础解系
std::vector<Matrix> baseSolution(Matrix A){
    Matrix B=Gauss(A,false);
    std::vector<std::pair<int,int> >swapID;
    for (int i=1;i<=B.row;++i){
        for (int j=1;j<=B.col;++j){
            if (B[i][j]==(Num)(1)){
                B.swap('C',i,j);
                swapID.push_back(std::make_pair(i,j));
                break;
            }
        }
    }
    int n=A.col,r=rk(A);
    Matrix ret=addV((Num)(-1)*(subMatrix(B,1,r,r+1,n)),Matrix(n-r,n-r,1));
    for (int i=swapID.size()-1;i>=0;--i){
        ret.swap('R',swapID[i].first,swapID[i].second);
    }
    return breakAsVector(ret, 'C');
}
std::vector<Matrix> baseSolution(Matrix A,Matrix b){
    A=addH(A,b);
    Matrix B=Gauss(A,false);
    std::vector<std::pair<int,int> >swapID;
    for (int i=1;i<=B.row;++i){
        for (int j=1;j<=B.col-1;++j){
            if (B[i][j]==(Num)(1)){
                B.swap('C',i,j);
                swapID.push_back(std::make_pair(i,j));
                break;
            }
        }
    }
    int n=A.col-1,r=rk(A);
    Matrix ret=addV((Num)(-1)*(subMatrix(B,1,r,r+1,n)),Matrix(n-r,n-r,1));
    for (int i=swapID.size()-1;i>=0;--i){
        ret.swap('R',swapID[i].first,swapID[i].second);
    }
    std::vector<Matrix> baseS=breakAsVector(ret, 'C');
    Matrix gama=addV(subMatrix(B,1,r,A.col,A.col),Matrix(n-r,1));
    for (int i=swapID.size()-1;i>=0;--i){
        gama.swap('R',swapID[i].first,swapID[i].second);
    }
    gama.Message="\\gama";
    baseS.push_back(gama);
    return baseS;
}
#endif