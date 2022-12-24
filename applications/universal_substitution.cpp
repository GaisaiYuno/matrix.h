#include "poly.h"
using namespace std;
int main(){
    poly p;
    cin>>p;
    solvedResults.push_back(make_pair('s',poly("2x","1+x^2")));
    solvedResults.push_back(make_pair('c',poly("1-x^2","1+x^2")));
    solvedResults.push_back(make_pair('t',poly("2x","1-x^2")));
    cout<<"substitute x=2arctan theta"<<endl;
    poly ans=substitute(p)*poly("2|1+x^2");
    cout<<ans<<endl;
    cout<<Factorization(upoly(ans.y))<<endl;
}
/*
1|3+5c
c^3-3c|1+s^2+s^4
1|9s^2+6cs+4c^2
*/