#include "fraction.h"

#define Num frac
#define Matrix SMatrix
#include "matrix.h"
#undef Matrix
#undef Num

#define Num SMatrix
#include "matrix.h"

using namespace std;
int main(){
    Matrix M;
    cin>>M;
    cout<<M;
}