/*
应该含有的元素：
- 多项式变量名，a-z
- 多项式系数，是分数 frac
- 多项式指数，是分数 frac

输入的方式
a 单个变量，代表1a^1
2a 代表 2a^1
a^2 代表 1a^2
中间 +,- 分割
*/
#ifndef POLY_ELE
#define POLY_ELE
#include "fraction.h"
#include "sqrt_field.h"
template<class Num>
struct poly_ele{//一个多项式的元素，形如 2/3a^3b^3/2
    Num coef;
    frac expo[26];
    poly_ele(){
        coef=(Num)(0);
        for (int i=0;i<26;++i){
            expo[i]=(frac)(0);
        }
    }
    poly_ele(Num x){
        coef=x;
        for (int i=0;i<26;++i){
            expo[i]=(frac)(0);
        }
    }
    bool con(){
        for (int i=0;i<26;++i){
            if (expo[i]!=(frac)(0)) return false;
        }
        return true;
    }
    void init(const char *s,int maxlen=0x7fffffff){
        int len=std::min((int)(strlen(s)),maxlen);
        int lastAlphabet=-1;
        for (int i=0;i<len;++i){
            if (lastAlphabet==-1 && 'a'<=s[i] && s[i]<='z'){//前面的系数
                if (i==0) coef=Num(1);
                else coef=toConstVal<Num>(s,i);
                lastAlphabet=i;
            }
            if ('a'<=s[i] && s[i]<='z' && lastAlphabet!=-1){
                int index=s[lastAlphabet]-'a';
                if (lastAlphabet+1==i){
                    expo[index].init("1");
                }
                else{
                    expo[index].init(s+lastAlphabet+1,i-lastAlphabet-1);
                }
                lastAlphabet=i;
            }
        }
        if (lastAlphabet==-1){
            coef=toConstVal<Num>(s,len);
        }
        else{
            int index=s[lastAlphabet]-'a';
            if (lastAlphabet==len-1){
                expo[index].init("1");
            }
            else{
                expo[index].init(s+lastAlphabet+1,len-lastAlphabet-1);
            }
        }
    }
    std::string symb(){
        std::string ret="";
        for (int i=0;i<26;++i){
            if (expo[i]!=(frac)(0)){
                ret+=char('a'+i);
                if (!(expo[i]==frac(1))){
                    ret+="^"+expo[i].to_string();
                }
            }
        }
        return ret;
    }
    bool single(){
        int cnt=0;
        for (int i=0;i<26;++i){
            if (expo[i]==0 || expo[i]==1){
                if (expo[i]==1) ++cnt;
            }
            else{
                return false;
            }
        }
        return cnt==0||cnt==1;
    }
    poly_ele(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
    poly_ele inv(){
        poly_ele ret;
        ret.coef=Num(1)/coef;
        for (int i=0;i<26;++i){
            ret.expo[i]=frac(0)-expo[i];
        }
        return ret;
    }
    poly_ele minus(){
        poly_ele ret;
        ret.coef=Num(0)-coef;
        for (int i=0;i<26;++i){
            ret.expo[i]=expo[i];
        }
        return ret;
    }
};
template<class Num>
bool equal(poly_ele<Num> A,poly_ele<Num> B){
    for (int i=0;i<26;++i){
        if (A.expo[i]!=B.expo[i]) return false;
    }
    return true;
}
template<class Num>
bool operator == (poly_ele<Num> A,poly_ele<Num> B){
    return A.coef == B.coef && equal(A,B);
}
template<class Num>
poly_ele<Num> operator * (poly_ele<Num> A,poly_ele<Num> B){
    poly_ele<Num> res;
    res.coef=A.coef*B.coef;
    for (int i=0;i<26;++i){
        res.expo[i]=A.expo[i]+B.expo[i];
    }
    return res;
}
template<class lam,class Num>
poly_ele<Num> operator * (lam lambda,poly_ele<Num> B){
    B.coef=(Num)(lambda)*B.coef;
    return B;
}
template<class Num>
poly_ele<Num> operator / (poly_ele<Num> A,poly_ele<Num> B){
    return A*(B.inv());
}
template<class Num>
poly_ele<Num> operator + (poly_ele<Num> A,poly_ele<Num> B){
    for (int i=0;i<26;++i){
        assert(A.expo[i]==B.expo[i]);
    }
    A.coef=A.coef+B.coef;
    return A;
}
template<class Num>
poly_ele<Num> operator - (poly_ele<Num> A,poly_ele<Num> B){
    for (int i=0;i<26;++i){
        assert(A.expo[i]==B.expo[i]);
    }
    A.coef=A.coef-B.coef;
    return A;
}
template<class Num>
std::ostream& operator << (std::ostream &out,const poly_ele<Num> &pe){
    bool flag=false;
    for (int i=0;i<26;++i){
        if (pe.expo[i]!=(frac)(0)){
            flag=true;
        }
    }
    if (flag){
        if (pe.coef==(Num)(1)) out<<"";
        else if (pe.coef==(Num)(-1)) out<<"-";
        else out<<pe.coef;
    }
    else {
        out<<pe.coef;
    }
    for (int i=0;i<26;++i){
        if (pe.expo[i]!=(frac)(0)){
            out<<char('a'+i);
            if (pe.expo[i]!=frac(1)){
                out<<"^"<<pe.expo[i];
            }
        }
    }
    return out;
}
std::ostream& operator << (std::ostream &out,const poly_ele<sqrtNum> &pe){
    bool flag=false;
    for (int i=0;i<26;++i){
        if (pe.expo[i]!=(frac)(0)){
            flag=true;
        }
    }
    if (flag){
        if (pe.coef.M==-1){
            if (pe.coef==(sqrtNum)(1)) out<<"";
            else if (pe.coef==(sqrtNum)(-1)) out<<"-";
            else out<<pe.coef;
        }
        else{
            out<<"("<<pe.coef<<")";
        }
    }
    else {
        out<<pe.coef;
    }
    for (int i=0;i<26;++i){
        if (pe.expo[i]!=(frac)(0)){
            out<<char('a'+i);
            if (!(pe.expo[i]==frac(1))){
                out<<"^"<<pe.expo[i];
            }
        }
    }
    return out;
}
template<class Num>
std::istream& operator >> (std::istream &in,poly_ele<Num> &f){
    std::string s;
    in>>s;
    f=poly_ele(s.c_str());
    return in;
}
template<class Num>
std::string to_latex(const poly_ele<Num> &pe,bool begin=true){
    bool flag=false;
    for (int i=0;i<26;++i){
        if (pe.expo[i]!=(frac)(0)){
            flag=true;
        }
    }
    std::string ret="";
    if (begin) ret+="$";
    if (flag){
        if (pe.coef.M==-1){
            if (pe.coef==(Num)(1)) ret=ret+"";
            else if (pe.coef==(Num)(-1)) ret=ret+"-";
            else ret=ret+to_latex(pe.coef,0);
        }
        else{
            ret=ret+"("+to_latex(pe.coef,0)+")";
        }
    }
    else {
        ret=ret+to_latex(pe.coef,0);
    }
    for (int i=0;i<26;++i){
        if (pe.expo[i]!=(frac)(0)){
            ret=ret+char('a'+i);
            if (pe.expo[i]!=frac(1)){
                ret=ret+"^"+to_latex(pe.expo[i],0);
            }
        }
    }
    if (begin) ret+="$";
    return ret;
}
#endif