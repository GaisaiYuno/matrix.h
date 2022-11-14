#include <cassert>
#include <iostream>
#include <vector>
#include <cstring>
struct Matrix{
    std::string Message;
    std::vector<std::vector<Num> >M;
    int row,col;//行数、列数
    Matrix(int rows,int cols){
        row=rows,col=cols;
        M.resize(row+1);
        for (int i=1;i<=row;++i){
            M[i].resize(col+1,(Num)(0));
        }
        Message="OK";
    }
    void init(int rows,int cols){
        row=rows,col=cols;
        M.resize(row+1);
        for (int i=1;i<=row;++i){
            M[i].resize(col+1,(Num)(0));
        }
        Message="OK";
    }
    Matrix(){
        row=col=0;
    }
    void Input(){
        std::cout<<"Please enter the row and col of the matrix"<<std::endl;
        std::cin>>row>>col;
        assert(row>=1 && col >=1);
        std::cout<<"Please enter the matrix"<<std::endl;
        init(row,col);
        for (int i=1;i<=row;++i){
            for (int j=1;j<=col;++j){
                std::cin>>M[i][j];
            }
        }
    }
    void Output(){
    	std::cout<<"--------------"<<std::endl;
        for (int i=1;i<=row;++i){
            for (int j=1;j<=col;++j){
                std::cout<<M[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
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
	    return B;
	}
};
Num myabs(Num x){
	if (x<Num(0)) return Num(0)-x;
	else return x;
}
Matrix Inverse(Matrix A){//求逆矩阵
    assert(A.row==A.col);
    int n=A.row;
    Matrix B(A.row,A.col);
    B.identityMatrix();
    for (int i=1;i<=n;++i){
        int r=i;
        for (int j=i+1;j<=n;++j){
            if (myabs(A[j][i])>myabs(A[r][i])) r=j;
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
    B.Message="OK";
    return B;
}
//化成简化的阶梯型矩阵，可选是否在前面形成一个单位矩阵 
Matrix Gauss(Matrix A,bool swapRow=false){
	int n=A.row;
	for (int i=1;i<=n;++i){
		int r=i;
		for (int j=i+1;j<=n;++j){
			if (myabs(A[j][i])>myabs(A[r][i])) r=j;
		}
		A.swap('R',r,i);
		if (A[i][i]==(Num)(0)){
			continue;
		}
        Num inv=(Num)(Num(0)-((Num)(1))/A[i][i]);
        for (int j=1;j<=n;++j){
            if (j==i) continue;
            Num t=A[j][i]*inv;
            A.addtimes('R',i,t,j);
        }
	}
	for (int i=1;i<=n;++i){
		A.times('R',i,(Num)(1)/A[i][i]);
	}
	A.Message="OK";
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
