#define Num sqrtNum
#include "sqrt_field.h"
#include "euclid.h"
using namespace std;
void printAngle(Matrix a,Matrix b){
    cout<<"arccos("<<angle(a,b)<<")"<<endl;
}
int main(){
    Matrix a1=Matrix('C',vector<sqrtNum>{1,1,1,2});
    Matrix a2=Matrix('C',vector<sqrtNum>{2,1,3,2});
    Matrix b1=Matrix('C',vector<sqrtNum>{3,1,-1,0});
    Matrix b2=Matrix('C',vector<sqrtNum>{1,2,-2,1});
    cout<<(a1&b1)<<" "<<(a2&b2)<<endl;
    cout<<length(a1)<<" "<<length(b1)<<" "<<length(a1-b1)<<" "<<length(a2-b2)<<endl;
    printAngle(a1,b1);
    printAngle(a2,b2);
}