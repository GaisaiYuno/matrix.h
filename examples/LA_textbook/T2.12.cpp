#include "poly.h"
using namespace std;
int main(){
    Matrix<poly> A(2,2,vector<poly>{2,1,-1,2});
    Matrix<poly> B(2,2,vector<poly>{"a","b","c","d"});
    Matrix<poly> E(2,2,1);
    Matrix<poly> ans=B*A-B-2*E;
    solve(vector{ans[1][1],ans[1][2],ans[2][1],ans[2][2]});
    outputResult();
}