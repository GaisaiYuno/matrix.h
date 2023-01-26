#include "conv.h"
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<Matrix<double> >points;
    while (n--){
        Matrix<double>pt(1,2);
        cin>>pt(1)>>pt(2);
        points.push_back(pt);
    }
    vector<Matrix<double> >hull=Convex2D(points);
    for (auto pt:hull) cout<<pt;
}
/*
8
0 3
1 1
2 2
4 4
0 0
1 2
3 1
3 3
*/