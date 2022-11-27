#include <iostream>
#include "poly.h"
using namespace std;
int main(){
    upoly p,q;
    cin>>p>>q;
    // cout<<p<<endl<<q<<endl;
    // cout<<p.deg()<<" "<<q.deg()<<endl;
    // cout<<p-q<<endl;
    // cout<<p+q<<endl;
    // cout<<p*q<<endl;
    cout<<p/q<<" "<<p%q<<endl;
    cout<<gcd(p,q);
}
/*
1+2x+x^2 
2+3x+x^3

1+2x
2+3x
*/