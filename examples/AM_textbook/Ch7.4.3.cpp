#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    //7.23
    Matrix Pl1=Matrix('R',vector<poly>{4,-3,12,15});
    Matrix P=Matrix('R',vector<poly>{2,-1,0});
    cout<<dist(P,Pl1);
    //7.24
    Matrix A=Matrix('R',vector<poly>{"1","0","2","1"});
    Matrix B=Matrix('R',vector<poly>{"1","-1","-1","1"});
    Matrix C=Matrix('R',vector<poly>{"l","1"});
    cout<<C*addV(A,B)<<endl;
    Matrix v1=(C*addV(A,B)).resize(1,3);
    Matrix v2=Matrix('R',vector<poly>{"1","1","2"});
    cout<<(v1&v2)<<endl;
    poly ret=(v1&v2)*(v1&v2)-poly("1/4")*(v1&v1)*(v2&v2);
    cout<<ret<<endl;
    cout<<Factorization(ret.x)<<endl;
}