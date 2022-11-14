#include "matrix.h"
#include <algorithm>
Matrix A1(3,3),A2(3,3),A3(3,3);
Matrix solve(Matrix alpha,Matrix beta){
	Matrix ret(3,1);
	ret[1][1]=(alpha.transpose()*A1*beta)[1][1];
	ret[2][1]=(alpha.transpose()*A2*beta)[1][1];
	ret[3][1]=(alpha.transpose()*A3*beta)[1][1];
	return ret;
}
int main(){
	A1[1][1]=1,A1[2][2]=0.25,A1[1][2]=A1[2][1]=0.5;
	A2[1][2]=A2[2][3]=A2[2][1]=A2[3][2]=0.5,A2[1][3]=A2[3][1]=1,A2[2][2]=0.5;
	A3[3][3]=1,A3[2][2]=0.25,A3[2][3]=A3[3][2]=0.5;
	//Plan 1
	Matrix start(3,1);
	start[1][1]=start[2][1]=start[3][1]=1.0/3.0;
	for (int i=1;i<=10;++i){
		Matrix alpha(3,1);
		alpha[1][1]=1;
		Matrix beta(3,1);
		beta=start;
		start=solve(alpha,beta);
		start.Output();
	}
	//plan 2
	start[1][1]=start[2][1]=start[3][1]=1.0/3.0;
	for (int i=1;i<=10;++i){
		Matrix alpha(3,1);
		alpha[2][1]=1;
		Matrix beta(3,1);
		beta=start;
		start=solve(alpha,beta);
		start.Output();
	}
	//plan 3
	start[1][1]=start[2][1]=start[3][1]=1.0/3.0;
	for (int i=1;i<=10;++i){
		Matrix a(3,1),b(3,1),c(3,1);
		a[1][1]=start[1][1],b[2][1]=start[2][1],c[3][1]=start[3][1];
		start=solve(a,a)+solve(b,b)+solve(c,c);
		start=(1.00/start.sum('C',1))*start;
		start.Output();
	}
}
