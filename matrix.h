#ifndef _MATRIX_
#define _MATRIX_
#include <cassert>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>

template<class T>
T myabs(T x){
    if (x>T(0)) return x;
    else return -x;
}
template<class T>
bool equals(const T &a,const T &b,const double eps=1e-6){
    if (typeid(T)==typeid(double)){
        return myabs(a-b)<=eps;
    }
    else if (typeid(T)==typeid(long double)){
        return myabs(a-b)<=eps;
    }
    else{
        return a==b;
    }
}
template<class Num>
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
        assert(v.size() == rows*cols);
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
    void addtimes(char type,int x,Num t,int y){
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
    template<class T>
    operator Matrix<T>(){
        Matrix<T>s;
        s.Message=Message;
        s.row=row,s.col=col;
        s.resize(row,col);
        for (int i=1;i<=row;++i){
            for (int j=1;j<=col;++j){
                s[i][j]=(T)(M[i][j]);
            }
        }
        return s;
    }
};

template<class Num>
std::istream& operator >> (std::istream &in,Matrix<Num> &A){
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
template<class Num>
std::ostream& operator << (std::ostream &out,const Matrix<Num> &A){
    std::cout<<A.Message<<std::endl;
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            std::cout<<A.M[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return out;
}
std::ostream& operator << (std::ostream &out,const Matrix<double> &A){
    std::cout<<A.Message<<std::endl;
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            if (equals(A.M[i][j],(double)(0))) std::cout<<"0 ";
            else std::cout<<std::setprecision(6)<<A.M[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return out;
}
std::ostream& operator << (std::ostream &out,const Matrix<long double> &A){
    std::cout<<A.Message<<std::endl;
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            if (equals(A.M[i][j],(long double)(0))) std::cout<<"0 ";
            else std::cout<<std::setprecision(6)<<A.M[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return out;
}
template<class Num>
std::string to_latex(const Matrix<Num> &A,std::string type="bmatrix",bool begin=true){
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
template<class Num>
Matrix<Num>addH(Matrix<Num> A,Matrix<Num> B){
    if (B.row==0 && B.col==0) return A;
    if (A.row==0 && A.col==0) return B;
    assert(A.row==B.row);
    Matrix<Num>C(A.row,A.col+B.col);
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
template<class Num>
Matrix<Num> addV(Matrix<Num> A,Matrix<Num> B){
    if (B.row==0 && B.col==0) return A;
    if (A.row==0 && A.col==0) return B;
    assert(A.col==B.col);
    Matrix<Num> C(A.row+B.row,A.col);
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
template<class Num>
Matrix<Num> addH(std::vector<Matrix<Num> >v){
    if (v.size()==0) return Matrix<Num>(0,0);
    Matrix ret=v[0];
    for (int i=1;i<v.size();++i) ret=addH(ret,v[i]);
    return ret;
}
template<class Num>
Matrix<Num> addV(std::vector<Matrix<Num> >v){
    if (v.size()==0) return Matrix<Num>(0,0);
    Matrix ret=v[0];
    for (int i=1;i<v.size();++i) ret=addV(ret,v[i]);
    return ret;
}
template<class Num>
Matrix<Num> addH(Matrix<Num> A,Matrix<Num> B,Matrix<Num> C){
    return addH(A,addH(B,C));
}
template<class Num>
Matrix<Num> addV(Matrix<Num> A,Matrix<Num> B,Matrix<Num> C){
    return addV(A,addV(B,C));
}
#ifndef UTILS
std::vector<int> genVector(int l,int r){
    std::vector<int> ret;
    for (int i=l;i<=r;++i) ret.push_back(i);
    return ret;
}
template<class Num>
Matrix<Num> diag(std::vector<Num>V){
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

template<class Num>
bool operator == (Matrix<Num> A,Matrix<Num> B){
    return A.M==B.M;
}
template<class Num>
bool operator != (Matrix<Num> A,Matrix<Num> B){
    return !(A.M==B.M);
}


template<class Num>
Matrix<Num> Inverse(Matrix<Num> A){//求逆矩阵
    assert(A.row==A.col);
    int n=A.row,m=A.col;
    Matrix<Num> B(A.row,A.col);
    B.identityMatrix();
    for (int i=1;i<=std::min(n,m);++i){
        int r=i;
        for (int j=i;j<=n;++j){
            if (!equals(A[j][i],(Num)(0))) r=j;
        }
        A.swap('R',i,r),B.swap('R',i,r);
        if (equals(A[i][i],(Num)(0))){
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

template<class Num>
Num Determinant(Matrix<Num> A){
    int n=A.row,m=A.col;
    assert(n==m);
    if (n<=7){
        Num ans=0;
        int per[11];
        for (int i=1;i<=n;++i) per[i]=i;
        do{
            int rev=1;
            for (int i=2;i<=n;++i){
                for (int j=1;j<=i-1;++j){
                    if (per[i]<per[j]) rev=-rev;
                }
            }
            Num sum;
            for (int i=1;i<=n;++i){
                if (i==1) sum=(Num)(rev)*A[i][per[i]];
                else sum=sum*A[i][per[i]];
            }
            ans=ans+sum;
        }while (std::next_permutation(per+1,per+1+n));
        return ans;
    }
    Num sign=(Num)(1);
    for (int i=1;i<=std::min(n,m)-1;++i){
        if (i>m){
            break;
        }
        int r=i;
        for (int j=n;j>=i;--j){
            if (!equals(A[j][i],(Num)(0))) r=j;
        }
        A.swap('R',r,i);
        if (i!=r) sign=(Num)(0)-sign;
        if (equals(A[i][i],(Num)(0))){
            return (Num)(0);
        }
        Num inv=(Num)(Num(0)-((Num)(1))/A[i][i]);
        for (int j=i+1;j<=n;++j){
            Num t=A[j][i]*inv;
            A.addtimes('R',i,t,j);
        }
    }
    for (int i=1;i<=n;++i){
        sign=sign*A[i][i];
    }
    return sign;
}
//化成简化的阶梯型矩阵
template<class Num>
Matrix<Num> Gauss(Matrix<Num> A){
    int n=A.row,m=A.col;
    int rk=1;
    for (int i=1;i<=std::min(n,m);++i){
        int r=rk;
        for (int j=n;j>=rk;--j){
            if (!equals(A[j][i],(Num)(0))) r=j;
        }
        A.swap('R',r,rk);
        if (equals(A[rk][i],(Num)(0))){
            continue;
        }
        Num inv=(Num)(Num(0)-((Num)(1))/A[rk][i]);
        for (int j=1;j<=n;++j){
            if (j==rk) continue;
            Num t=A[j][i]*inv;
            A.addtimes('R',rk,t,j);
        }
        ++rk;
    }
    for (int i=1;i<=std::min(n,m);++i){
        for (int j=1;j<=m;++j){
            if (!equals(A[i][j],(Num)(0))){
                A.times('R',i,(Num)(1)/A[i][j]);
                break;
            }
        }
    }
    A.Message="Matrix is in Gauss form";
    return A;
}
Matrix<double> Gauss(Matrix<double> A){
    int n=A.row,m=A.col;
    int rk=1;
    for (int i=1;i<=std::min(n,m);++i){
        int r=rk;
        for (int j=n;j>=rk;--j){
            if (myabs(A[j][i])>myabs(A[r][i])) r=j;
        }
        A.swap('R',r,rk);
        if (equals(A[rk][i],(double)(0))){
            continue;
        }
        double inv=(double)(double(0)-((double)(1))/A[rk][i]);
        for (int j=1;j<=n;++j){
            if (j==rk) continue;
            double t=A[j][i]*inv;
            A.addtimes('R',rk,t,j);
        }
        ++rk;
    }
    for (int i=1;i<=std::min(n,m);++i){
        for (int j=1;j<=m;++j){
            if (!equals(A[i][j],(double)(0))){
                A.times('R',i,(double)(1)/A[i][j]);
                break;
            }
        }
    }
    A.Message="Matrix is in Gauss form";
    return A;
}
Matrix<long double> Gauss(Matrix<long double> A){
    int n=A.row,m=A.col;
    int rk=1;
    for (int i=1;i<=std::min(n,m);++i){
        int r=rk;
        for (int j=n;j>=rk;--j){
            if (myabs(A[j][i])>myabs(A[r][i])) r=j;
        }
        A.swap('R',r,rk);
        if (equals(A[rk][i],(long double)(0))){
            continue;
        }
        long double inv=(long double)((long double)(0)-((long double)(1))/A[rk][i]);
        for (int j=1;j<=n;++j){
            if (j==rk) continue;
            long double t=A[j][i]*inv;
            A.addtimes('R',rk,t,j);
        }
        ++rk;
    }
    for (int i=1;i<=std::min(n,m);++i){
        for (int j=1;j<=m;++j){
            if (!equals(A[i][j],(long double)(0))){
                A.times('R',i,(long double)(1)/A[i][j]);
                break;
            }
        }
    }
    A.Message="Matrix is in Gauss form";
    return A;
}

template<class Num>
Matrix<Num> operator * (Matrix<Num> A,Matrix<Num> B){
    assert(A.col==B.row);
    Matrix<Num> C(A.row,B.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=B.col;++j){
            for (int k=1;k<=A.col;++k){
                C[i][j]=C[i][j]+A[i][k]*B[k][j];
            }
        }
    }
    return C;
}
template<class Num>
bool isSwapable(Matrix<Num> A,Matrix<Num> B){
    return A*B==B*A;
}
template<class lam,class Num>
Matrix<Num> operator * (lam lambda,Matrix<Num> A){
    Matrix<Num> B(A.row,A.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=B.col;++j){
            B[i][j]=(Num)(lambda)*A[i][j];
        }
    }
    return B;
}
template<class Num>
Matrix<Num> operator + (Matrix<Num> A,Matrix<Num> B){
    assert(A.row==B.row && A.col==B.col);
    Matrix<Num> C(A.row,A.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    return C;
}
template<class Num>
Matrix<Num> operator - (Matrix<Num> A,Matrix<Num> B){
    assert(A.row==B.row && A.col==B.col);
    Matrix<Num> C(A.row,A.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            C[i][j]=A[i][j]-B[i][j];
        }
    }
    return C;
}
template<class Num>
Matrix<Num> operator - (Matrix<Num> A){
    Matrix<Num> C(A.row,A.col);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            C[i][j]=(Num)(0)-A[i][j];
        }
    }
    return C;
}
template<class Num>
Matrix<Num> operator / (Num x,Matrix<Num> A){
    return x*Inverse(A);
}
template<class Num>
Matrix<Num> operator / (Matrix<Num> A,Num x){
    return (Num(1)/x)*A;
}
template<class Num>
Matrix<Num> operator / (Matrix<Num> A,Matrix<Num> B){
    return A*Inverse(B);
}
template<class Num>
Matrix<Num> operator ^ (Matrix<Num> A,int k){
    assert(A.row==A.col);
	if (k==0){
		return Matrix<Num>(A.row,A.col,1);
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
template<class Num>
Num tr(Matrix<Num> A){
    assert(A.row==A.col);
    Num ans=0;
    for (int i=1;i<=A.row;++i){
        ans=ans+A[i][i];
    }
    return ans;
}
template<class Num>
int rk(Matrix<Num> A){
    Matrix<Num> B=Gauss(A);
    int rk=0;
    for (int i=1;i<=B.row;++i){
        bool flag=false;
        for (int j=1;j<=B.col;++j){
            if (!equals(B[i][j],(Num)(0))){
                flag=true;
                break;
            }
        }
        if (flag) rk++;
    }
    return rk;
}
//分裂成行向量和列向量
template<class Num>
std::vector<Matrix<Num> > breakAsVector(Matrix<Num> A,char type){
    std::vector<Matrix<Num> > vectors;
    if (type=='C'){//列向量
        for (int i=1;i<=A.col;++i){
            Matrix<Num> tmp(A.row,1);
            for (int j=1;j<=A.row;++j){
                tmp[j][1]=A[j][i];
            }
            tmp.Message="\\eta_"+std::to_string(i);
            vectors.push_back(tmp);
        }
    }
    else if (type=='R'){//行向量
        for (int i=1;i<=A.row;++i){
            Matrix<Num> tmp(1,A.col);
            for (int j=1;j<=A.col;++j){
                tmp[1][j]=A[i][j];
            }
            tmp.Message="\\eta_"+std::to_string(i);
            vectors.push_back(tmp);
        }
    }
    return vectors;
}
template<class Num>
Matrix<Num> subMatrix(Matrix<Num> A,std::vector<int>rowChoose,std::vector<int>colChoose){
    Matrix<Num> B(rowChoose.size(),colChoose.size());
    for (int i=0;i<rowChoose.size();++i){
        for (int j=0;j<colChoose.size();++j){
            B[i+1][j+1]=A[rowChoose[i]][colChoose[j]];
        }
    }
    return B;
}
template<class Num>
Matrix<Num> subMatrix(Matrix<Num> A,int rlb,int rub,int clb,int cub){
    Matrix<Num> B(rub-rlb+1,cub-clb+1);
    for (int i=rlb;i<=rub;++i){
        for (int j=clb;j<=cub;++j){
            B[i-rlb+1][j-clb+1]=A[i][j];
        }
    }
    return B;
}
//求出 A 的基础解系
template<class Num>
std::vector<Matrix<Num> > baseSolution(Matrix<Num> A){
    Matrix B=Gauss(A);
    std::vector<std::pair<int,int> >swapID;
    for (int i=1;i<=B.row;++i){
        for (int j=1;j<=B.col;++j){
            if (equals(B[i][j],(Num)(1))){
                B.swap('C',i,j);
                swapID.push_back(std::make_pair(i,j));
                break;
            }
        }
    }
    int n=A.col,r=rk(A);
    Matrix ret=addV((Num)(-1)*(subMatrix(B,1,r,r+1,n)),Matrix<Num>(n-r,n-r,1));
    for (int i=swapID.size()-1;i>=0;--i){
        ret.swap('R',swapID[i].first,swapID[i].second);
    }
    return breakAsVector(ret, 'C');
}
template<class Num>
std::vector<Matrix<Num> > baseSolution(Matrix<Num> A,Matrix<Num> b){
    A=addH(A,b);
    Matrix<Num> B=Gauss(A,false);
    std::vector<std::pair<int,int> >swapID;
    for (int i=1;i<=B.row;++i){
        for (int j=1;j<=B.col-1;++j){
            if (equals(B[i][j],(Num)(1))){
                B.swap('C',i,j);
                swapID.push_back(std::make_pair(i,j));
                break;
            }
        }
    }
    int n=A.col-1,r=rk(A);
    Matrix ret=addV((Num)(-1)*(subMatrix(B,1,r,r+1,n)),Matrix<Num>(n-r,n-r,1));
    for (int i=swapID.size()-1;i>=0;--i){
        ret.swap('R',swapID[i].first,swapID[i].second);
    }
    std::vector<Matrix<Num> > baseS=breakAsVector(ret, 'C');
    Matrix gama=addV(subMatrix(B,1,r,A.col,A.col),Matrix<Num>(n-r,1));
    for (int i=swapID.size()-1;i>=0;--i){
        gama.swap('R',swapID[i].first,swapID[i].second);
    }
    gama.Message="\\gama";
    baseS.push_back(gama);
    return baseS;
}

#endif
