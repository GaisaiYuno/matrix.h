#define Num sqrtNum
#include "sqrt_field.h"
#include "euclid.h"
using namespace std;
int main(){
    vector<Matrix>sch=Schmidt(
        vector<Matrix>{
            Matrix('C',vector<Num>{sqrtNum("-2/3"),sqrtNum("-1/3"),sqrtNum("1"),sqrtNum("0")}),
            Matrix('C',vector<Num>{sqrtNum("-2/3"),sqrtNum("-1/3"),sqrtNum("0"),sqrtNum("1")}),
        }
    );
    for (int i=0;i<sch.size();++i) cout<<identilize(sch[i]).first<<endl;
    cout<<"--------------------------"<<endl;
    sch=Schmidt(
        vector<Matrix>{
            Matrix('C',vector<Num>{sqrtNum("-2/3"),sqrtNum("-1/3"),sqrtNum("1"),sqrtNum("0")}),
            Matrix('C',vector<Num>{sqrtNum("-2/3"),sqrtNum("-1/3"),sqrtNum("0"),sqrtNum("1")}),
            Matrix('C',vector<Num>{sqrtNum("1"),sqrtNum("0"),sqrtNum("0"),sqrtNum("0")}),
            Matrix('C',vector<Num>{sqrtNum("0"),sqrtNum("1"),sqrtNum("0"),sqrtNum("0")}),
        }
    );
    for (int i=0;i<sch.size();++i) cout<<identilize(sch[i]).first<<endl;
}
/*
1 1 2 1 2
1 2 3 4 5
2 3 5 5 7
*/