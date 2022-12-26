#include "poly.h"
#define Num poly
#include "euclid.h"
using namespace std;
int main(){
    Line C=distLine(
        make_pair(
            Matrix('R',vector<poly>{-1,0,1}),
            Matrix('R',vector<poly>{1,1,2})
        ),
        make_pair(
            Matrix('R',vector<poly>{0,-1,2}),
            Matrix('R',vector<poly>{1,3,4})
        )
    );
    output(C);
    cout<<length(C.second)<<endl;
}