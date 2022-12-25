#include "poly.h"
using namespace std;
int main(){
    poly p;
    cin>>p;
    solvedResults.push_back(make_pair('s',poly("x^2|x^2+1")));//sin^2
    solvedResults.push_back(make_pair('c',poly("1|x^2+1")));//cos^2
    solvedResults.push_back(make_pair('h',poly("x|x^2+1")));//hybrid cos sin
    solvedResults.push_back(make_pair('t',poly("x")));
    cout<<"substitute x=tan theta"<<endl;
    poly ans=substitute(p)*poly("x^2+1");
    cout<<ans<<endl;
    cout<<Factorization(upoly(ans.y))<<endl;
}
/*
1|9s+12h+4c
*/