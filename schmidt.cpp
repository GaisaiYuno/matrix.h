#define Num frac
#include "fraction.h"
#include "euclid.h"
using namespace std;
int main(){
    vector<Matrix>sch=Schmidt(vector<Matrix>{Matrix('R',vector<Num>{1,2,3}),Matrix('R',vector<Num>{1,0,0}),Matrix('R',vector<Num>{0,1,0})});
    for (int i=0;i<sch.size();++i) cout<<sch[i]<<endl;
}
/*
1 1 2 1 2
1 2 3 4 5
2 3 5 5 7
*/