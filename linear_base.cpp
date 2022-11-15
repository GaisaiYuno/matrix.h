#define Num poly
#include "poly.h"
#include "matrix.h"
using namespace std;
int main(){
	// poly p=poly("1");
	// cout<<p<<endl;
	// _poly _p=_poly("1");
	// cout<<_p<<endl;
	// poly_ele _pe=poly_ele("1");
	// cout<<_pe<<endl;
	// poly p=poly("-15x^3z^5+20x^5z^3+6xz^7-4xy^4z^3-12x^3y^2z^3-2xy^2z^5-15x^7z-10x^3y^4z+28x^5y^2z+6x^9z^-1+28x^5y^4z^-1-22x^7y^2z^-1-12x^3y^6z^-1-x^-1z^9+x^-1y^4z^5+2x^-1y^2z^7+x^-1y^8z-4x^-1y^6z^3-2xy^8z^-1-4xy^6z-x^11z^-3-15x^7y^4z^-3+6x^9y^2z^-3+20x^5y^6z^-3-15x^3y^8z^-3+6xy^10z^-3-x^-1y^12z^-3+2x^-1y^10z^-1|4xz^3-6x^3z+4xy^2z+4x^5z^-1-8x^3y^2z^-1+4xy^4z^-1-x^7z^-3+4x^5y^2z^-3-6x^3y^4z^-3-x^-1z^5+2x^-1y^4z+4xy^6z^-3-x^-1y^8z^-3");
	// cout<<p<<endl;
	// cout<<p-poly("x^4+y^4+z^4-2x^2y^2-2x^2z^2-2y^2z^2")<<endl;
	// cout<<poly("a^3b^4c^5+a^3b^6c^6|a^3b^2c^5+a^3b^6c^6");
	Matrix A;
	cin>>A;
	cout<<A<<endl;
	cout<<Gauss(A)<<endl;
	cout<<Determinant(A)<<endl;
	cout<<Inverse(A)<<endl;
	// vector<Matrix>baseS=baseSolution(A);
	// for (int i=0;i<baseS.size();++i){
	// 	cout<<baseS[i]<<endl;
	// }
	// cout<<Gauss(A);
	// cout<<Gauss(A,true);
	// cout<<rk(A)<<endl;
	// vector<Matrix>vectorC=breakAsVector(A,'C');
	// vector<Matrix>vectorR=breakAsVector(A,'R');
	// for (int i=0;i<vectorC.size();++i){
	// 	cout<<vectorC[i]<<endl;
	// }
	// for (int i=0;i<vectorR.size();++i){
	// 	cout<<vectorR[i]<<endl;
	// }
}
/*
3 5 6 -4
1 2 4 -3
4 5 -2 3
3 8 24 -19
d a a a
a x a a
a a x a
a a a x

x y x+y 
y x+y x 
x+y x y

1 0
1/a 1

2 1 4
4 2 5
k -3 -4
-2 -1 3

1 a a^2 a^3
0 1 a a^2
0 0 1 a
0 0 0 1
*/