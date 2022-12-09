#include "poly.h"
using namespace std;
frac lambda;
poly simplify(poly ret){
    lambda=ret.x[0].coef/ret.y[0].coef;
    ret.x=ret.x-lambda*_poly("t")*ret.y;
    ret.simp();
    return ret;
}
int main(){
    upoly x;
    cpoly y;
    cin>>x>>y;
    upoly _y=to_upoly(y);
    upoly z=x/_y;
    cout<<Integral(z)<<endl;
    x=x%_y;
    decomp dc=Decomposit(x,y);
    for (int i=0;i<dc.v.size();++i){
        upoly x=dc.v[i].first,y=dc.v[i].second.first;
        int k=dc.v[i].second.second;
        int d=y.deg();
        if (d==1){
            if (k==1){
                cout<<x[0]<<"ln|"<<y<<"|"<<endl;
            }
            else{
                cout<<x[0]*frac(1,-k+1)<<"("<<y<<")"<<"^"<<-(k-1)<<endl;
            }
        }
        else if (d==2){
            frac s=y[2];
            x=(1/s)*x,y=(1/s)*y;
            frac B=x[1],D=x[0];
            frac p=y[1],q=y[0];
            frac dt=y.delta();
            if (k==1){
                cout<<B/2<<"ln("<<y<<")+("<<(2*D-B*p)<<")/\\"<<-dt<<"arctan((2x+"<<p<<")/\\"<<-dt<<")"<<endl;
            }
            else{
                cout<<"好丑陋，嘤嘤嘤：";
                if ((int)sqrt(-dt.x)*(int)sqrt(-dt.x)==-dt.x){
                    int m=(int)(sqrt(-dt.x));
                    frac a=frac(m,2);
                    poly r=simplify(int_x2a2(k,a));
                    cout<<B/2<<"ln("<<y<<")+("<<(2*D-B*p)<<")/\\"<<-dt<<"[("<<r<<")+"<<lambda<<"*"<<1/a<<"arctan(x/"<<a<<")"<<"]"<<endl;
                }
                else{
                    cout<<"根号开不尽我更不会算了喵喵喵~"<<endl;
                }
            }
        }
    }
    cout<<"C"<<endl;//别忘了常数
}
/*
25x
2
x-1 2
x^2+2x+2 1


1
2
x-1 1
x^2-2x+2 1

1
1
x^2+1 2
*/