#include <fraction.h>
#define Num frac
#include <matrix.h>
using namespace std;
int main(){
    Matrix A,B;
    cin>>A>>B;
    cout<<(A^(-1))*B<<endl;
}