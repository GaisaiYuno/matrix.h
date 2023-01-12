#ifndef SQRT_FIELD
#define SQRT_FIELD
#include "fraction.h"
#define ALL_MOD -1
struct sqrtNum{
    //形式是 x+y sqrt(M)
    frac M;
    frac x,y;
    sqrtNum(){
        x=0;y=0;
        M=ALL_MOD;
    }
    void simp(){
        if (M==ALL_MOD) return ;
        if (M==0){
            y=0;
            M=ALL_MOD;
            return ;
        }
        if (M.y!=1){
            M.x*=M.y;
            y=y/M.y;
            M.y=1;
        }
        long long m=getPowFactor(M.x),n=getPowFactor(M.y);
        M=M/frac(m*m,n*n);
        y=y*frac(m,n);
        if (M==1){
            x=x+y,y=0;
            M=ALL_MOD;
        }
    }
    frac to_frac(){
        assert(M==ALL_MOD);
        return x;
    }
    sqrtNum(sqrtNum nx,sqrtNum ny,sqrtNum nM){
        x=nx.to_frac(),y=ny.to_frac(),M=nM.to_frac();
        if (y==0) M=ALL_MOD;
        simp();
    }
    sqrtNum(int nx){
        x=nx,y=0,M=ALL_MOD;
    }
    sqrtNum(long long nx,long long ny){
        x=frac(nx,ny),y=0,M=ALL_MOD;
    }
    sqrtNum(frac nx,frac ny,frac nM){
        x=nx,y=ny,M=nM;
        if (y==0) M=ALL_MOD;
        simp();
    }
    sqrtNum(frac nx){
        x=nx,y=0,M=ALL_MOD;
    }
    sqrtNum conjunction(){
        return sqrtNum(x,0-y,M);
    }
    void init(const char *s,int maxlen=0x7fffffff){
        //x
        //x+y\M
        //x-y\M
        //y\M
        //\M
        //x+\M
        //x-\M
        int signIndex=-1,slashIndex=-1,sign=1;
        int len=std::min((int)(strlen(s)),maxlen);
        for (int i=0;i<len;++i){
            if (s[i]=='+'||s[i]=='-') signIndex=i,sign=(s[i]=='+'?1:-1);
            if (s[i]=='\\') slashIndex=i;
        }
        if (slashIndex==-1 && (signIndex==-1 || signIndex==0)){
            x=frac(s,maxlen),y=0;
            M=ALL_MOD;
        }
        else if (slashIndex!=-1 && signIndex==-1){
            x=0,y.init(s,slashIndex);
            M.init(s+slashIndex+1,len-slashIndex);
            assert(M>(frac)(0));
        }
        else if (slashIndex!=-1 && signIndex!=-1){
            x.init(s,signIndex),y.init(s+signIndex+1,slashIndex-signIndex-1);
            M.init(s+slashIndex+1,len-slashIndex);
            assert(M>(frac)(0));
            y=y*frac(sign);
        }
        simp();
    }
    sqrtNum(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
};
frac::frac(sqrtNum A){
    assert(A.M==ALL_MOD);
    x=A.x.x;
    y=A.x.y;
}
std::ostream& operator << (std::ostream &,const sqrtNum &);
sqrtNum operator + (sqrtNum A,sqrtNum B){
    assert(A.M==ALL_MOD || B.M==ALL_MOD || A.M==B.M);
    return sqrtNum(A.x+B.x,A.y+B.y,std::max(A.M,B.M));
}
sqrtNum operator - (sqrtNum A,sqrtNum B){
    assert(A.M==ALL_MOD || B.M==ALL_MOD || A.M==B.M);
    return sqrtNum(A.x-B.x,A.y-B.y,std::max(A.M,B.M));
}
sqrtNum operator - (sqrtNum A){
    return sqrtNum(0)-sqrtNum(A);
}
sqrtNum operator * (frac lambda,sqrtNum A){
    return sqrtNum(lambda*A.x,lambda*A.y,A.M);
}
sqrtNum operator * (long long lambda,sqrtNum A){
    return sqrtNum(lambda*A.x,lambda*A.y,A.M);
}
sqrtNum operator * (sqrtNum A,sqrtNum B){
    if (A.x==0 && B.x==0){
        return sqrtNum(0,A.y*B.y,A.M*B.M);
    }
    assert(A.M==ALL_MOD || B.M==ALL_MOD || A.M==B.M);
    return sqrtNum(A.x*B.x+std::max(A.M,B.M)*A.y*B.y,A.x*B.y+A.y*B.x,std::max(A.M,B.M));
}
sqrtNum operator / (long long lambda,sqrtNum A){
    return lambda*sqrtNum(A.x/(A.x*A.x-A.y*A.y*A.M),A.M==ALL_MOD?0:(frac(0)-A.y)/(A.x*A.x-A.y*A.y*A.M),A.M);
}
sqrtNum operator / (frac lambda,sqrtNum A){
    return lambda*sqrtNum(A.x/(A.x*A.x-A.y*A.y*A.M),A.M==ALL_MOD?0:(frac(0)-A.y)/(A.x*A.x-A.y*A.y*A.M),A.M);
}
sqrtNum operator / (sqrtNum B,sqrtNum A){
    assert(A.M==ALL_MOD || B.M==ALL_MOD || A.M==B.M);
    return B*((frac)(1)/A);
}
sqrtNum Sqrt(frac A){
    return sqrtNum(0,1,A);
}
sqrtNum Sqrt(sqrtNum A){
    if (A.M==ALL_MOD) return Sqrt(A.x);
    assert(0);
}
bool operator == (sqrtNum A,sqrtNum B){
    return A.x==B.x && A.y==B.y && A.M==B.M;
}
bool operator != (sqrtNum A,sqrtNum B){
    return !(A==B);
}
int sgn(frac x){
    if (x>0) return 1;
    else if (x==0) return 0;
    return -1;
}
int Compare(sqrtNum A,sqrtNum B){
    assert(A.M==ALL_MOD || B.M==ALL_MOD || A.M==B.M);
    sqrtNum C=A-B;
    if (C.x==0 && C.y==0) return 0;
    else if (C.x==0) return C.y>0;
    else if (C.y==0) return C.x>0;
    if (C.x<0 && C.y<0) return -1;
    if (C.x>0 && C.y>0) return 1;
    if (C.x<0 && C.y>0){
        return sgn(C.x*C.x-C.M*C.y*C.y);
    }
    else {
        return -sgn(C.x*C.x-C.M*C.y*C.y);
    }
}
bool operator <= (sqrtNum A,sqrtNum B){
    return Compare(A,B)<=0;
}
bool operator < (sqrtNum A,sqrtNum B){
    return Compare(A,B)<0;
}
bool operator > (sqrtNum A,sqrtNum B){
    return Compare(A,B)>0;
}
std::istream& operator >> (std::istream &in,sqrtNum &A){
    //a+b\x
    //a-b\x
    std::string s;
    std::cin>>s;
    A=sqrtNum(s.c_str());
    return in;
}
std::ostream& operator << (std::ostream &out,const sqrtNum &A){
    bool pre=false,aft=A.M!=ALL_MOD;
    if (A.x!=frac(0)){
        out<<A.x,pre=true;
    }
    if (pre==true){
        if (A.y<0){
            if (!(A.y==frac(-1)&&aft)){
                out<<A.y;
            }
            else{
                out<<"-";
            }
        }
        else if (A.y>0){
            out<<'+';
            if (!(A.y==frac(1)&&aft)){
                out<<A.y;
            }
        }
        else if (A.y==0) out<<"";
    }
    else{
        if (A.y<0){
            if (!(A.y==frac(-1)&&aft)){
                out<<A.y;
            }
            else{
                out<<"-";
            }
        }
        else if (A.y>0){
            if (!(A.y==frac(1)&&aft)){
                out<<A.y;
            }
        }
        else if (A.y==0) out<<'0';
    }
    if (A.y!=0 && A.M!=ALL_MOD){
        out<<'\\'<<A.M;
    }
    return out;
}
std::string to_latex(const sqrtNum &A,bool begin=true){
    std::string ret="";
    if (begin) ret+="$";
    bool pre=false,aft=A.M!=ALL_MOD;
    if (A.x!=frac(0)){
        ret+=to_latex(A.x,0),pre=true;
    }
    if (pre==true){
        if (A.y<0){
            if (!(A.y==frac(-1)&&aft)){
                ret+=to_latex(A.y,0);
            }
            else{
                ret+="-";
            }
        }
        else if (A.y>0){
            ret+="+";
            if (!(A.y==frac(1)&&aft)){
                ret+=to_latex(A.y,0);
            }
        }
    }
    else{
        if (A.y<0){
            if (!(A.y==frac(-1)&&aft)){
                ret+=to_latex(A.y,0);
            }
            else{
                ret+="-";
            }
        }
        else if (A.y>0){
            if (!(A.y==frac(1)&&aft)){
                ret+=to_latex(A.y,0);
            }
        }
        else if (A.y==0) ret+="0";
    }
    if (A.y!=0 && A.M!=ALL_MOD){
        ret+="\\sqrt{"+to_latex(A.M,0)+"}";
    }
    if (begin) ret+="$";
    return ret;
}
#endif