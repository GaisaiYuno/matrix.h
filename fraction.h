#ifndef FRACTION
#define FRACTION
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cassert>
#include <cmath>
long long toInterger(const char *s,int length){
    long long f=1,x=0;
    for (int i=0;i<length;++i){
        if (s[i]=='-') f=-f;
        else if ('0'<=s[i] && s[i]<='9'){
            x=x*10+s[i]-'0';
        }
    }
    return x*f;
}
long long getPowFactor(long long x){
    for (long long i=sqrt(x);i>=1;--i){
        if (x%(i*i)==0) return i;
    }
    return 1;
}
struct sqrtNum;
struct frac{
    long long x,y;
    void simp(){
        long long gcd=std::__gcd(x,y);
        x/=gcd,y/=gcd;
        if (y<0) x=-x,y=-y;
    }
    frac(){
        x=0,y=1;
    }
    frac(long long n){
        x=n,y=1;
    }
    frac(int n){
        x=(long long)n,y=1;
    }
    frac(long long nx,long long ny){
        x=nx,y=ny;
        simp();
    }
    void init(const char *s,int maxlen=0x7fffffff){
        int len=std::min((int)std::strlen(s),maxlen);
        for (int i=0;i<len;++i){
            if (s[i]=='/'){
                x=toInterger(s,i),y=toInterger(s+i+1,len-i-1);
                simp();
                return ;
            }
        }
        x=toInterger(s,len),y=1;
    }
    frac(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
    frac inv(){
        return frac(y,x);
    }
    std::string to_string(){
        if (x==0 && y==0) return "0";
        if (y==1) return std::to_string(x);
        return std::to_string(x)+"/"+std::to_string(y);
    }
};
frac operator + (frac A,frac B){
    return frac(A.x*B.y+A.y*B.x,A.y*B.y);
}
frac operator - (frac A,frac B){
    return frac(A.x*B.y-A.y*B.x,A.y*B.y);
}
frac operator - (frac A){
    return frac(-A.x,A.y);
}
frac operator * (frac A,frac B){
    return frac(A.x*B.x,A.y*B.y);
}
frac operator * (long long A,frac B){
    return frac(A*B.x,B.y);
}
frac operator / (frac A,frac B){
    assert(B.x!=0);
    return frac(A.x*B.y,A.y*B.x);
}
bool operator < (frac A,frac B){
    return (A-B).x<0;
}
bool operator > (frac A,frac B){
    return (A-B).x>0;
}
bool operator <= (frac A,frac B){
    return (A-B).x<=0;
}
bool operator >= (frac A,frac B){
    return (A-B).x>=0;
}
bool operator == (frac A,frac B){
    return (A-B).x==0;
}
bool operator != (frac A,frac B){
    return (A-B).x!=0;
}
std::istream& operator >> (std::istream &in,frac &f){
    std::string s;
    in>>s;
    f.init(s.c_str());
    return in;
}
std::ostream& operator << (std::ostream &out,const frac &f){
    if (f.x==0 && f.y==0) out<<0;
    else {
        if (f.y==1) out<<f.x;
        else out<<f.x<<"/"<<f.y;
    }
    return out;
}
std::string to_latex(const frac &f,bool begin=true){
    std::string ret="";
    if (begin) ret+="$";
    if (f.y!=1){
        if (f.x<0) ret="-\\frac{"+std::to_string(-f.x)+"}{"+std::to_string(f.y)+"}";
        else ret="\\frac{"+std::to_string(f.x)+"}{"+std::to_string(f.y)+"}";
    }
    else ret=std::to_string(f.x);
    if (begin) ret+="$";
    return ret;
}
#endif