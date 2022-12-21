#include "matrix.h"
#include <algorithm>
int main(){
    Matrix A(2,2);
    A[1][1]=1,A[1][2]=1,A[2][1]=1;
    Matrix Base(2,2);
	Base.identityMatrix();
	for (int i=1;i<=10;++i){
		Base=Base*A;
		Base.Output();
	} 
}
