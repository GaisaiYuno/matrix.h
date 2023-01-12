#include "poly.h"
#include "euclid.h"
using namespace std;
int main(){
    Matrix<poly>a1=Matrix<poly>('C',vector<poly>{"1/3","-2/3","2/3"});
    auto baseExpan=baseExpansion(vector<Matrix<poly> >{a1});
    for (auto m:baseExpan){
        cout<<m;
    }
}