#ifndef COMPLEX
#define COMPLEX
#include "fraction.h"
#include "sqrt_field.h"
template<class Num>
class Complex{
    Num a,b;
    public:
    Complex(){
        a=0,b=0;
    }
    Complex(Num _a){
        a=_a,b=0;
    }
    Complex(Num _a,Num _b){
        a=_a,b=_b;
    }
    Complex conjunction(){
        return Complex(a,-b);
    }
    Num real(){
        return a;
    }
    Num imag(){
        return b;
    }
    void init(const char *s,int maxlen=0x7fffffff){
        int i_index=-1,lst_sgn_index=-1;
        int len=std::min((int)(strlen(s)),maxlen);
        for (int i=0;i<len;++i){
            if (s[i]=='i') i_index=i;
            if (s[i]=='+'||s[i]=='-') lst_sgn_index=i;
        }
        if (lst_sgn_index==-1||lst_sgn_index==0){
            
        }
    }
};
#endif