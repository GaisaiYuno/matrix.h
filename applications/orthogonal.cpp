#include "sqrt_field.h"
#define Num sqrtNum
#include "euclid.h"
using namespace std;
int main(){
    ofstream out;
    out.open("test2.tex");
    out<<begin_latex()<<endl;
    Matrix A;
    cin>>A;
    out<<to_latex(A)<<endl;
    vector<Matrix>v=breakAsVector(A,'C');
    for (int i=0;i<v.size();++i){
        v[i]=identilize(v[i]).first;
    }
    A=addH(v);
    cout<<A<<endl;
    cout<<to_latex(A)<<endl;
    out<<"Orthogonal Matrix\n\n"<<to_latex(A)<<endl;
    out<<end_latex()<<endl;
}