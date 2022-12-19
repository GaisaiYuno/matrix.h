#define Num sqrtNum
#include "sqrt_field.h"
#include "euclid.h"
using namespace std;
// Num F(Num x){
//     return x*x*x;
// }
// Num G(Num x){
//     return x*x;
// }
int main(){
    // Matrix A=Matrix('R',vector<Num>{(Num)(1),(Num)(2),(Num)(3)});
    // Matrix B=Matrix('R',vector<Num>{(Num)(1),(Num)(3),(Num)(3)});
    // Cauchy_Schwarz(A,B);
    // Matrix _F=Discrete(F,(Num)(1),(Num)("3/2"),(Num)("1/10"));
    // Matrix _G=Discrete(G,(Num)(1),(Num)("3/2"),(Num)("1/10"));
    // Cauchy_Schwarz(_F,_G);
    // Matrix A=Matrix('R',vector<sqrtNum>{2,3,-1});
    // Matrix B=Matrix('R',vector<sqrtNum>{1,-3,-7});
    // cout<<(A&B)<<endl<<angle(A,B);
    
    // Matrix A=Matrix('R',vector<sqrtNum>{4,2,0});
    // Matrix B=Matrix('R',vector<sqrtNum>{1,1,1});
    // cout<<proj(A,B)<<proj_vec(A,B);

    // Matrix A=Matrix('R',vector<sqrtNum>{1,0,1});
    // Matrix B=Matrix('R',vector<sqrtNum>{-1,-1,0});
    // cout<<proj(A,B)<<proj_vec(A,B);

    // Matrix A=Matrix('R',vector<sqrtNum>{"1/3\\3","1/3\\3","1/3\\3"});
    // Matrix B=Matrix('R',vector<sqrtNum>{-3,7,0});
    // cout<<A<<endl;
    // cout<<cross(A,B)<<endl;

    // Matrix A=Matrix('R',vector<sqrtNum>{5,2,0});
    // Matrix B=Matrix('R',vector<sqrtNum>{2,5,0});
    // Matrix C=Matrix('R',vector<sqrtNum>{1,2,4});

    // cout<<length(cross(B-A,C-A))/2<<endl;


    Matrix A=Matrix('R',vector<sqrtNum>{1,4,5});
    Matrix B=Matrix('R',vector<sqrtNum>{2,-1,1});
    Matrix C=Matrix('R',vector<sqrtNum>{5,2,7});

    cout<<Determinant(addV(vector<Matrix>{A,B,C}));
}