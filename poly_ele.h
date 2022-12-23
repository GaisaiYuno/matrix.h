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
struct poly_ele{//一个多项式的元素，形如 2/3a^3b^3/2
    sqrtNum coef;
    frac expo[26];
    poly_ele(){
        coef=(sqrtNum)(0);
        for (int i=0;i<26;++i){
            expo[i]=(frac)(0);
        }
    }
    poly_ele(int x){
        coef=(sqrtNum)(x);
        for (int i=0;i<26;++i){
            expo[i]=(frac)(0);
        }
    }
    poly_ele(sqrtNum x){
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
                if (i==0) coef.init("1");
                else coef.init(s,i);
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
            coef.init(s,len);
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
    poly_ele(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
    poly_ele inv(){
        poly_ele ret;
        ret.coef=sqrtNum(1)/coef;
        for (int i=0;i<26;++i){
            ret.expo[i]=frac(0)-expo[i];
        }
        return ret;
    }
    poly_ele minus(){
        poly_ele ret;
        ret.coef=sqrtNum(0)-coef;
        for (int i=0;i<26;++i){
            ret.expo[i]=expo[i];
        }
        return ret;
    }
};
bool equal(poly_ele A,poly_ele B){
    for (int i=0;i<26;++i){
        if (A.expo[i]!=B.expo[i]) return false;
    }
    return true;
}
bool operator == (poly_ele A,poly_ele B){
    return A.coef == B.coef && equal(A,B);
}
poly_ele operator * (poly_ele A,poly_ele B){
    poly_ele res;
    res.coef=A.coef*B.coef;
    for (int i=0;i<26;++i){
        res.expo[i]=A.expo[i]+B.expo[i];
    }
    return res;
}
poly_ele operator / (poly_ele A,poly_ele B){
    return A*(B.inv());
}
poly_ele operator + (poly_ele A,poly_ele B){
    for (int i=0;i<26;++i){
        assert(A.expo[i]==B.expo[i]);
    }
    A.coef=A.coef+B.coef;
    return A;
}
poly_ele operator - (poly_ele A,poly_ele B){
    for (int i=0;i<26;++i){
        assert(A.expo[i]==B.expo[i]);
    }
    A.coef=A.coef-B.coef;
    return A;
}
std::ostream& operator << (std::ostream &out,const poly_ele &pe){
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
std::istream& operator >> (std::istream &in,poly_ele &f){
    std::string s;
    in>>s;
    f=poly_ele(s.c_str());
    return in;
}
std::string to_latex(const poly_ele &pe,bool begin=true){
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
            if (pe.coef==(sqrtNum)(1)) ret=ret+"";
            else if (pe.coef==(sqrtNum)(-1)) ret=ret+"-";
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