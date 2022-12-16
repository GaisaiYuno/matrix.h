#include "poly.h"
#define Num frac
#include "matrix.h"
using namespace std;
int main(){
    upoly y=upoly(vector<frac>{1,1,1,1,1,1,1,1,1,1},0);
    //vector<upoly> ans=solve_diff(vector<upoly>{upoly("x^2")*Deriv(y),Deriv(y),-upoly("x")*y},1);
    // vector<upoly> ans=solve_diff(vector<upoly>{Deriv(Deriv(y)),2*Deriv(y),-3*y},2);
    vector<upoly> ans=solve_diff(vector<upoly>{Deriv(Deriv(y)),2*Deriv(y),2*y},2);
    for (int i=0;i<ans.size();++i){
        cout<<"C"<<i+1<<"*("<<ans[i]<<")"<<endl;
    }
}