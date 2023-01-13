#include "poly.h"
using namespace std;
int main(){
    upoly<double> a(vector<double>{-8,45,-83,61,-17,1});
    auto res=solve(a);
    for (auto x:res) cout<<x<<endl;
    for (auto x:res) cout<<F(a,x)<<endl;
}