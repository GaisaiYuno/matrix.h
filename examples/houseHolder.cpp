#define Num sqrtNum
#include "sqrt_field.h"
#include "euclid.h"
using namespace std;
int main(){
    //HouseHolder变换，求Omega确定的点关于v确定的平面的对称点
    Matrix Omega('C',vector<Num>{1,0,0});
    Matrix v('C',vector<Num>{1,1,1});
    cout<<houseHolder(v)<<endl;
    cout<<houseHolder(v)*Omega<<endl;
    //求出v关于u确定的直线的对称点
    Matrix u('C',vector<Num>{1,1,-1});
    //先通过Schmidt变换得出两个正交的向量，确定了u,v所在的平面，
    vector<Matrix>S=Schmidt(vector<Matrix>{u,v});
    cout<<houseHolder(S[1])*v<<endl;
}