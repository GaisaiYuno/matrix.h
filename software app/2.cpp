#include "matrix.h"
#include <algorithm>
int main(){
    Matrix A(7,6);
	A.Input();//实在不想手敲了。
	/*
	1 1 0 1 0 0
	1 0 1 1 0 0
	1 1 1 1 0 0
	1 1 0 1 0 0
	1 1 0 1 0 0
	1 0 0 0 1 0
	0 0 0 0 1 1
	*/
	Matrix alpha(6,1);
	alpha[1][1]=1,alpha[4][1]=1,alpha[2][1]=1;
	for (int i=1;i<=7;++i){
		if (alpha.sum('C',1)==(A*alpha).sum('R',i)){
			std::cout<<i<<" matches"<<std::endl;
		}
	}
}
