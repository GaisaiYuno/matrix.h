#define Num double 
#include "matrix.h"
#include <algorithm>
int main(){
    Matrix A(5,5);
    A[1][2]=1,A[1][3]=1;
    A[2][3]=1,A[2][4]=1,A[2][5]=1;
    A[4][1]=1,A[4][3]=1,A[4][5]=1;
    A[5][1]=1,A[5][3]=1;
    Matrix B=A*A;
    A.Output(),(A*A).Output();
    std::vector<std::pair<int,std::pair<int,int> > >rk;
    for (int i=1;i<=5;++i){
    	rk.push_back(std::make_pair(-A.sum('R',i),std::make_pair(-B.sum('R',i),i)));
	}
	std::sort(rk.begin(),rk.end());
	for (int i=0;i<(int)rk.size();++i){
		std::cout<<rk[i].second.second<<" ";
	}
}
