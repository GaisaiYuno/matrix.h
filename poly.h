#ifndef POLY_H
#define POLY_H
#include "poly_ele.h"
#include "matrix.h"
#include <vector>
template<class Num>
struct upoly;
template<class Num>
struct _poly{//不含除法
    std::vector<poly_ele<Num> >v;
    _poly(poly_ele<Num> x){
        v.clear();
        v.push_back(x);
    }
    _poly(Num x){
        v.clear();
        v.push_back(poly_ele(x));
    }
    _poly(){
        v.clear();
    }
    _poly(upoly<Num>);
    poly_ele<Num> &operator[](int i){
        return v[i];
    }
    poly_ele<Num> &operator[](std::string s){
        for (auto it=v.begin();it!=v.end();++it){
            if ((*it).symb()==s) return *it;
        }
        static poly_ele<Num> p=poly_ele(0);
        return p;
    }
    bool qu(char &symb,frac &maxExpo){//单元有理
        maxExpo=0;
        bool hasAlpha[26];
        memset(hasAlpha,0,sizeof(hasAlpha));
        for (int i=0;i<v.size();++i){
            for (int j=0;j<26;++j){
                hasAlpha[j]|=(v[i].expo[j]!=0);
                if (v[i].expo[j].y!=1) return false;
                maxExpo=std::max(maxExpo,v[i].expo[j]);
                if (v[i].expo[j]<0) return false;
            }
        }
        int cnt=0;
        for (int j=0;j<26;++j){
            cnt+=hasAlpha[j];
            if (hasAlpha[j]==1) symb='a'+j;
        }
        if (cnt==0){
            symb='x';
        }
        return cnt==1 || cnt==0;
    }
    bool insert(poly_ele<Num> x){
        if (x.coef==(Num)(0)){
            return true;
        }
        bool found=false;
        int j=0;
        for (auto i=v.begin();i!=v.end();i++,j++){
            if (equal(x,*i)){
                found=true;
                v[j]=v[j]+x;
                if (v[j].coef==Num(0)){
                    v.erase(i);
                }
                break;
            }
        }
        if (!found) v.push_back(x);
        return found;
    }
    void init(const char *s,int maxlen=0x7fffffff){
        int len=std::min((int)(strlen(s)),maxlen);
        int lastSign=-1,sign=1;
        for (int i=0;i<len;++i){
            if (lastSign==-1 && (s[i]=='+' || s[i]=='-')){
                if (i==0){
                    lastSign=i;sign=(s[i]=='+')?1:-1;
                    continue;
                }
                poly_ele<Num> new_ele;
                new_ele.init(s,i);
                insert(new_ele);
            }
            if (lastSign!=-1 &&(s[i]=='+' || s[i]=='-')){
                poly_ele<Num> new_ele;
                new_ele.init(s+lastSign+1,i-lastSign-1);
                new_ele.coef=new_ele.coef*(Num)(sign);
                insert(new_ele);
            }
            if (s[i]=='+'||s[i]=='-'){
                lastSign=i;sign=(s[i]=='+')?1:-1;
            }
        }
        if (lastSign==-1){
            poly_ele<Num> new_ele;
            new_ele.init(s,len);
            insert(new_ele);
        }else{
            poly_ele<Num> new_ele;
            new_ele.init(s+lastSign+1,len-lastSign-1);
            new_ele.coef=new_ele.coef*(Num)(sign);
            insert(new_ele);
        }
    }
    _poly(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
    Num eval(){
        if (v.size()==0){
            return 0;
        }
        else if (v.size()==1){
            for (int i=0;i<26;++i){
                assert(v[0].expo[i]==0);
            }
            return v[0].coef;
        }
        else{
            assert(0);
        }
    }
    bool isconst(){
        if (v.size()==0){
            return true;
        }
        else if (v.size()==1){
            for (int i=0;i<26;++i){
                if (v[0].expo[i]!=0){
                    return false;
                }
            }
            return true;
        }
        else{
            return false;
        }
    }
};
template<class Num>
_poly<Num> operator + (_poly<Num> A,_poly<Num> B){
    for (int i=0;i<B.v.size();++i){
        A.insert(B[i]);
    }
    return A;
}
template<class Num>
_poly<Num> operator - (_poly<Num> A,_poly<Num> B){
    for (int i=0;i<B.v.size();++i){
        A.insert(B[i].minus());
    }
    return A;
}
template<class Num>
_poly<Num> operator * (_poly<Num> A,_poly<Num> B){
    _poly<Num> C;
    for (int i=0;i<A.v.size();++i){
        for (int j=0;j<B.v.size();++j){
            C.insert(A[i]*B[j]);
        }
    }
    return C;
}
template<class Num>
_poly<Num> operator ^ (_poly<Num> a,int k){
    if (k==0) return _poly<Num>(1);
    _poly<Num> ret=a;
    for (int i=1;i<=k-1;++i) ret=ret*a;
    return ret;
}
template<class Num>
bool operator == (_poly<Num> A,_poly<Num> B){
    return (A-B).v.size()==0;
}

std::ostream& operator << (std::ostream &out,const _poly<sqrtNum> &p){
    if (p.v.size()==0){
        out<<"0";
    }
    for (int i=0;i<p.v.size();++i){
        if (p.v[i].coef.M==-1){
            if (p.v[i].coef.x==(0)) continue;
            if (i!=0 && p.v[i].coef.x>(frac)(0)) out<<"+";
            out<<p.v[i];
        }
        else{
            if (p.v[i].coef.x==(0) && p.v[i].coef.y==(0)) continue;
            if (i!=0) out<<"+";
            out<<p.v[i];
        }
    }
    return out;
}
std::ostream& operator << (std::ostream &out,const _poly<frac> &p){
    if (p.v.size()==0){
        out<<"0";
    }
    for (int i=0;i<p.v.size();++i){
        if (i!=0 && p.v[i].coef>(frac)(0)) out<<"+";
        if (p.v[i].coef==(frac)(0)) continue;
        out<<p.v[i];
    }
    return out;
}
std::ostream& operator << (std::ostream &out,const _poly<double> &p){
    if (p.v.size()==0){
        out<<"0";
    }
    for (int i=0;i<p.v.size();++i){
        if (i!=0 && p.v[i].coef>(double)(0)) out<<"+";
        if (p.v[i].coef==(double)(0)) continue;
        out<<p.v[i];
    }
    return out;
}

template<class Num>
std::istream& operator >> (std::istream &in,_poly<Num> &p){
    std::string s;
    in>>s;
    p=_poly(s.c_str());
    return in;
}
template<class Num>
std::string to_latex(const _poly<Num> &p,bool begin=true){
    std::string ret="";
    if (begin) ret+="$";
    if (p.v.size()==0){
        ret+="0";
    }
    for (int i=0;i<p.v.size();++i){
        if (p.v[i].coef.M==-1){
            if (p.v[i].coef.x==(0)) continue;
            if (i!=0 && p.v[i].coef.x>(frac)(0)) ret+="+";
            ret+=to_latex(p.v[i],0);
        }
        else{
            if (p.v[i].coef.x==(0) && p.v[i].coef.y==(0)) continue;
            if (i!=0) ret+="+";
            ret+=to_latex(p.v[i],0);
        }
    }
    if (begin) ret+="$";
    return ret;
}

template<class Num>
struct cpoly;
//单元有理多项式，写为 a0+a1x+a2x^2+... 的形式

template<class Num>
struct upoly{
    //规定只有0的多项式度数为-1
    char symb;
    std::vector<Num>v;
    int begin;
    upoly(){
        symb='x';
        v.clear();
        begin=0;
    }
    upoly(std::vector<Num>w){
        symb='x';
        v=w;
        begin=0;
    }
    upoly(std::vector<Num>w,int bg){
        symb='x';
        v=w;
        begin=bg;
    }
    upoly(Num f){
        symb='x';
        v.clear(),v.push_back(f);
        begin=0;
    }
    upoly(cpoly<Num>);
    upoly(Matrix<Num>);
    void simp(){
        for (int i=v.size()-1;i>=0;--i){
            if (!(v[i]==0)){
                v.resize(i+1);
                return ;
            }
        }
        v.resize(0);
    }
    bool is_zero(){
        for (int i=0;i<v.size();++i){
            if (v[i]!=0) return false;
        }
        return true;
    }
    int deg(){//多项式的度
        simp();
        return v.size()-1;
    }
    Num delta(){
        assert(deg()==2);
        return v[1]*v[1]-4*v[0]*v[2];
    }
    void insert(int expo,Num coef){
        if (v.size()<expo+1){
            v.resize(expo+1);
            v[expo]=coef;
        }
        else{
            v[expo]=v[expo]+coef;
        }
    }
    Num val(Num x){
        Num ans=0;
        for (int i=v.size()-1;i>=0;--i){
            ans=ans*x+v[i];
        }
        return ans;
    }
    Num &operator[](int i){
        return v[i];
    }
    void init_from_poly(_poly<Num> A){
        frac maxExpo=0;
        if (A.qu(symb,maxExpo)){
            assert(maxExpo.y==1);
            v.resize(maxExpo.x+1,0);
            for (int i=0;i<A.v.size();++i){
                v[A.v[i].expo[symb-'a'].x]=(Num)(A.v[i].coef);
            }
            simp();
        }
        else{
            assert(0);
        }
    }
    void init(const char *s,int maxlen=0x7fffffff){
        init_from_poly(_poly(s,maxlen));
    }
    upoly(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
    upoly(_poly<Num> x){
        init_from_poly(x);
    }
};
template<class Num>
upoly<Num> Integral(upoly<Num> x){
    std::vector<Num>v;
    v.push_back(0);
    for (int i=0;i<x.v.size();++i){
        v.push_back(x.v[i]/Num(i+1));
    }
    return upoly(v,x.begin-1);
}
template<class Num>
upoly<Num> Deriv(upoly<Num> x){
    std::vector<Num>v;
    if (x.v.size()==0){
        v.push_back(0);
        return upoly(v,x.begin+1);
    }
    for (int i=1;i<x.v.size();++i){
        v.push_back(x.v[i]*Num(i));
    }
    return upoly(v,x.begin+1);
}
template<class Num>
_poly<Num>::_poly(upoly<Num> A){
    _poly<Num> ret;
    for (int i=A.v.size()-1;i>=0;--i){
        poly_ele<Num> t;
        t.coef=Num(A.v[i]);
        t.expo[A.symb-'a']=i;
        ret.insert(t);
    }
    v=ret.v;
}
template<class Num>
std::string to_latex(const upoly<Num> &p,bool begin=true){
    std::string ret="";
    if (begin) ret+="$";
    ret+=to_latex(_poly(p),0);
    if (begin) ret+="$";
    return ret;
}
template<class Num>
upoly<Num> operator << (const upoly<Num> &A,int delta){
    upoly<Num> B;
    B.v.resize(A.v.size()+delta,0);
    for (int i=0;i<A.v.size();++i){
        if (i+delta>=0) B[i+delta]=A.v[i];
    }
    B.symb=A.symb;
    B.begin=A.begin-delta;
    return B;
}
template<class Num>
std::ostream& operator << (std::ostream &out,const upoly<Num> &p){
    out<<_poly(p);
    return out;
}
template<class Num>
std::istream& operator >> (std::istream &in,upoly<Num> &p){
    std::string s;
    in>>s;
    p.init_from_poly(_poly<Num>(s.c_str()));
    return in;
}
template<class Num>
upoly<Num> operator + (upoly<Num> A,upoly<Num> B){
    assert(A.symb==B.symb);
    upoly<Num> C;
    C.v.resize(std::max(A.v.size(),B.v.size()));
    for (int i=0;i<A.v.size();++i) C[i]=C[i]+A[i];
    for (int i=0;i<B.v.size();++i) C[i]=C[i]+B[i];
    C.symb=A.symb;
    C.simp();
    return C;
}
template<class Num>
upoly<Num> operator - (upoly<Num> A,upoly<Num> B){
    assert(A.symb==B.symb);
    upoly<Num> C;
    C.v.resize(std::max(A.v.size(),B.v.size()));
    for (int i=0;i<A.v.size();++i) C[i]=C[i]+A[i];
    for (int i=0;i<B.v.size();++i) C[i]=C[i]-B[i];
    C.symb=A.symb;
    C.simp();
    return C;
}
template<class Num>
upoly<Num> operator * (upoly<Num> A,upoly<Num> B){
    assert(A.symb==B.symb);
    upoly<Num> C;
    C.v.resize(std::max((int)(A.v.size()+B.v.size()-1),0));
    for (int i=0;i<A.v.size();++i){
        for (int j=0;j<B.v.size();++j){
            C[i+j]=C[i+j]+A[i]*B[j];
        }
    }
    C.symb=A.symb;
    C.simp();
    return C;
}
template<class lam,class Num>
upoly<Num> operator * (lam lambda,upoly<Num> A){
    for (int i=0;i<A.v.size();++i){
        A[i]=A[i]*lambda;
    }
    return A;
}
template<class Num>
upoly<Num> operator - (upoly<Num> A){
    return (sqrtNum)(-1)*A;
}
template<class Num>
upoly<Num> operator / (upoly<Num> A,upoly<Num> B){
    assert(A.symb==B.symb);
    upoly<Num> ret;
    ret.symb=A.symb;
    while (A.deg()>=B.deg()){
        Num lambda=A[A.v.size()-1]/B[B.v.size()-1];
        ret.insert(A.deg()-B.deg(),lambda);
        A=A-lambda*(B<<(A.deg()-B.deg()));
    }
    return ret;
}
template<class Num>
upoly<Num> operator % (upoly<Num> A,upoly<Num> B){
    return A-B*(A/B);
}
template<class Num>
upoly<Num> gcd(upoly<Num> A,upoly<Num> B){
    if (B.is_zero()) return A;
    return gcd(B,A%B);
}
template<class Num>
upoly<Num> F(upoly<Num> x,upoly<Num> a){
    upoly<Num> ans;
    for (int i=x.v.size()-1;i>=0;--i){
        ans=ans*a+x.v[i];
    }
    return ans;
}
template<class Num>
upoly<Num> operator ^ (upoly<Num> a,int k){
    upoly ret=a;
    for (int i=1;i<=k-1;++i) ret=ret*a;
    return ret;
}
template<class Num>
struct cpoly{
    std::vector<std::pair<upoly<Num>,int> >v;
    void insert(upoly<Num> x,int expo){
        v.push_back(std::make_pair(x,expo));
    }
    auto sol(){
        std::vector<Num>solution;
        for (int i=0;i<v.size();++i){
            if (v[i].first.deg()==1){
                solution.push_back(-v[i].first[0]/v[i].first[1]);
            }
            else if (v[i].first.deg()==2){
                Num a=v[i].first[2],b=v[i].first[1],c=v[i].first[0];
                Num delta=b*b-4*a*c;
                solution.push_back(sqrtNum(-b/(2*a),1/(2*a),delta));
                solution.push_back(sqrtNum(-b/(2*a),-1/(2*a),delta));
            }
        }
        return solution;
    }
};
template<class Num>
std::ostream& operator << (std::ostream &out,const cpoly<Num> &p){
    for (int i=0;i<p.v.size();++i){
        out<<"("<<p.v[i].first<<")";
        if (p.v[i].second!=1){
            out<<"^"<<p.v[i].second;
        }
    }
    return out;
}
template<class Num>
std::istream& operator >> (std::istream &in,cpoly<Num> &p){
    int num;
    in>>num;
    while (num--){
        upoly<Num> t;
        int expo;
        in>>t>>expo;
        p.insert(t,expo);
    }
    return in;
}
template<class Num>
std::string to_latex(const cpoly<Num> &p,bool begin=true){
    std::string ret="";
    if (begin) ret+="$";
    for (int i=0;i<p.v.size();++i){
        ret+="("+to_latex(p.v[i].first,0)+")";
        if (p.v[i].second!=1){
            ret+="^"+std::to_string(p.v[i].second);
        }
    }
    if (begin) ret+="$";
    return ret;
}
template<class Num>
cpoly<Num> Factorization(upoly<Num> A){
    cpoly<Num> ret;
    while (A.deg()){
        upoly<Num> factor;
        bool flag1=true,flag2=true;
        for (int i=100;i>=-100;--i){
            for (int j=1;j<=100;++j){
                if (A.val(Num(i)/Num(j))==0){
                    factor.symb=A.symb;
                    factor.v.resize(2);
                    factor[1]=1;
                    factor[0]=Num(-i)/Num(j);
                    flag1=false;
                    break;
                }
            }
            if (!flag1) break;
        }
        if (flag1){
            for (int ip=10;ip>=-10;--ip){
                for (int jp=1;jp<=10;++jp){
                    for (int iq=10;iq>=-10;--iq){
                        for (int jq=1;jq<=10;++jq){
                            Num p=Num(ip)/Num(jp),q=Num(iq)/Num(jq);
                            factor.symb=A.symb;
                            factor.v.resize(3);
                            factor[2]=1;
                            factor[1]=p;
                            factor[0]=q;
                            if ((A%factor).deg()==-1){
                                flag2=false;
                                break;
                            }
                        }
                        if (!flag2) break;
                    }
                    if (!flag2) break;
                }
                if (!flag2) break;
            }
        }
        if (!flag1 || !flag2){
            int cnt=0;
            while ((A%factor).v.size()==0){
                A=A/factor;
                cnt++;
            }
            ret.insert(factor,cnt);
        }
        else{
            ret.insert(A,1);
            break;
        }
    }
    return ret;
}
template<class Num>
upoly<Num>::upoly(cpoly<Num> x){
    upoly<Num> ret;
    ret.insert(0,Num(1));
    for (int i=0;i<x.v.size();++i){
        for (int j=1;j<=x.v[i].second;++j){
            ret=ret*x.v[i].first;
        }
    }
    v=ret.v;
}
template<class Num>
upoly<Num>::upoly(Matrix<Num> M){
    int cnt=0;
    for (int i=1;i<=M.row;++i){
        for (int j=1;j<=M.col;++j){
            insert(cnt++,M[i][j]);
        }
    }
}
template<class Num>
auto to_vector(upoly<Num> x,int sz=-1){
    if (sz==-1){
        return Matrix<Num>('C',x.v);
    }
    else{
        auto ret=Matrix<Num>('C',x.v);
        ret.resize(sz,1);
        return ret;
    }
}
template<class Num>
struct decomp{
    std::vector< std::pair<upoly<Num>,std::pair<upoly<Num>,int> > >v;
    decomp(){
        v.clear();
    }
    void insert(upoly<Num> x,upoly<Num> y,int expo){
        v.push_back(std::make_pair(x,std::make_pair(y,expo)));
    }
};
template<class Num>
std::ostream& operator << (std::ostream &out,const decomp<Num> &p){
    for (int i=0;i<p.v.size();++i){
        if (i!=0) out<<"+";
        out<<"("<<p.v[i].first<<")";
        out<<"|";
        out<<"("<<p.v[i].second.first<<")";
        if (p.v[i].second.second!=1){
            out<<"^"<<p.v[i].second.second;
        }
    }
    return out;
}
template<class Num>
decomp<Num> Decomposit(upoly<Num> x,cpoly<Num> y){
    upoly z=y;
    std::vector<Matrix<Num> >v;
    cpoly temp=y;
    for (int i=0;i<y.v.size();++i){
        int d=y.v[i].first.deg();
        for (int j=1;j<=y.v[i].second;++j){
            temp.v[i].second=y.v[i].second-j;
            if (d==1){
                v.push_back(to_vector(upoly(temp),z.deg()));
            }
            else if (d==2){
                v.push_back(to_vector(upoly(temp)<<1,z.deg()));
                v.push_back(to_vector(upoly(temp),z.deg()));
            }
            else{
                assert(0);
            }
            temp.v[i].second=y.v[i].second;
        }
    }
    Matrix<Num>ans=(addH(v)^-1)*to_vector(x,z.deg());
    decomp<Num> ret;
    int cnt=0;
    for (int i=0;i<y.v.size();++i){
        int d=y.v[i].first.deg();
        for (int j=1;j<=y.v[i].second;++j){
            if (d==1){
                ret.insert(upoly(std::vector<sqrtNum>{ans[++cnt][1]}),y.v[i].first,j);
            }
            else if (d==2){
                Num B=ans[++cnt][1];
                Num D=ans[++cnt][1];
                ret.insert(upoly(std::vector<sqrtNum>{D,B}),y.v[i].first,j);
            }
        }
    }
    return ret;
}

//一些泰勒公式
template<class Num>
upoly<Num> Exp(upoly<Num> p){
    upoly<Num> t;
    long long fac=1;
    for (int i=1;i<=10;++i){
        t.v.push_back(sqrtNum(1,fac));
        fac=fac*i;
    }
    return F(t,p);
}
template<class Num>
upoly<Num> Ln(upoly<Num> p){//Ln(p)，转化为(p-1)+1
    upoly<Num> t;
    t.v.push_back(0);
    int sign=1;
    for (int i=1;i<=10;++i){
        t.v.push_back(Num(1)/Num(sign*i));
        sign=sign*-1;
    }
    return F(t,p-upoly("1"));
}
template<class Num>
upoly<Num> Sin(upoly<Num> p){
    upoly<Num> t;
    long long fac=1;
    int sign=1;
    for (int i=0;i<=10;++i){
        if (i!=0) fac=fac*i;
        if (i&1){
            t.v.push_back(Num(1)/Num(sign*fac));
            sign=sign*-1;
        }
        else{
            t.v.push_back(0);
        }
    }
    return F(t,p);
}
template<class Num>
upoly<Num> Cos(upoly<Num> p){
    upoly<Num> t;
    long long fac=1;
    int sign=1;
    for (int i=0;i<=10;++i){
        if (i!=0) fac=fac*i;
        if (!(i&1)){
            t.v.push_back(sqrtNum(1,sign*fac));
            sign=sign*-1;
        }
        else{
            t.v.push_back(0);
        }
    }
    return F(t,p);
}
template<class Num>
upoly<Num> Tan(upoly<Num> p){
    upoly<Num> t("x+1/3x^3+2/15x^5+17/315x^7+62/2835x^9+1382/155925x^11");
    return F(t,p);
}
template<class Num>
upoly<Num> Arctan(upoly<Num> p){
    upoly<Num> t("x-1/3x^3+1/5x^5-1/7x^7");
    return F(t,p);
}
template<class Num>
upoly<Num> Arcsin(upoly<Num> p){
    upoly<Num> t("x+1/6x^3+3/40x^5");
    return F(t,p);
}
template<class Num>
upoly<Num> Pow(upoly<Num> p,Num alpha){//转化为(1+(x-1))^alpha
    upoly<Num> t;
    t.v.push_back(1);
    Num x=alpha,y=1;
    for (int i=1;i<=10;++i){
        t.v.push_back(x/y);
        x=x*(alpha-i),y=y*Num(i+1);
    }
    return F(t,p-upoly("1"));
}
template<class Num>
upoly<Num> Pow(upoly<Num> a,upoly<Num> x){
    return Exp(Ln(a)*x);
}
template<class Num>
upoly<Num> EquivInf(upoly<Num> x){
    upoly<Num> ret;
    for (int i=0;i<x.v.size();++i){
        if (x.v[i]!=0){
            ret.v.resize(i+1);
            ret.v[i]=x.v[i];
            return ret;
        }
    }
    return ret;
}
template<class Num>
auto Limit(upoly<Num> a,upoly<Num> b){//计算a/b当x->0时的极限
    a=EquivInf(a);
    b=EquivInf(b);
    if (a.deg()==b.deg()) return (a/b)[0];
    else if (a.deg()<b.deg()){
        std::cout<<"Not Exist"<<std::endl;
        return Num(0x7fffffff);
    }
    else{
        return Num(0);
    }
}
template<class Num>
auto definiteInt(upoly<Num> x,Num l,Num r){
    upoly<Num> ix=Integral(x);
    return F(ix,r)-F(ix,l);
}
template<class Num>
auto definiteInt(upoly<Num> x,upoly<Num> l,upoly<Num> r){
    upoly<Num> ix=Integral(x);
    return F(ix,r)-F(ix,l);
}
template<class Num>
auto variableLimit(upoly<Num> x,upoly<Num> l,upoly<Num> r){
    return Integral(F(x,r)*Deriv(r)-F(x,l)*Deriv(l));
}

template<class Num>
struct poly{//含除法
    _poly<Num> x,y;
    poly(){
        x.v.clear(),y.v.clear();
        x.insert(poly_ele(0));
        y.insert(poly_ele(1));
    }
    poly(Num n){
        x.v.clear(),y.v.clear();
        x.insert(poly_ele(n));
        y.insert(poly_ele((Num)(1)));
    }
    poly(int n){
        x.v.clear(),y.v.clear();
        x.insert(poly_ele((Num)(n)));
        y.insert(poly_ele((Num)(1)));
    }
    poly(poly_ele<Num> n){
        x.v.clear(),y.v.clear();
        x.insert(n);
        y.insert(poly_ele((Num)(1)));
    }
    void simp(){
        frac minexpo[26];
        for (int i=0;i<26;++i){
            minexpo[i]=frac(0x7fffffff);
        }
        for (int i=0;i<x.v.size();++i){
            for (int j=0;j<26;++j){
                minexpo[j]=std::min(minexpo[j],x.v[i].expo[j]);
            }
        }
        for (int i=0;i<y.v.size();++i){
            for (int j=0;j<26;++j){
                minexpo[j]=std::min(minexpo[j],y.v[i].expo[j]);
            }
        }
        poly_ele<Num> pe;
        pe.coef=Num(1);
        for (int i=0;i<26;++i){
            pe.expo[i]=minexpo[i];
        }
        for (int i=0;i<x.v.size();++i){
            x.v[i]=x.v[i]/pe;
        }
        for (int i=0;i<y.v.size();++i){
            y.v[i]=y.v[i]/pe;
        }
        if (x.v.size()>0 && y.v.size()>0 && x.v.size()==y.v.size()){
            poly_ele _pe=x.v[0]/y.v[0];
            for (int i=1;i<x.v.size();++i){
                if (!(x.v[i]/y.v[i]==_pe)){
                    return ;
                }
            }
            x.v.clear(),y.v.clear();
            x.insert(_pe),y.insert(poly_ele((Num)(1)));
        }
        char cx,cy;
        frac fx,fy;
        if (x.qu(cx,fx) && y.qu(cy,fy)){
            if (cx==cy){
                static upoly<Num> _x,_y;
                _x.init_from_poly(x),_y.init_from_poly(y);
                upoly g=gcd(_x,_y);
                if (g.deg()>1){
                    _x=_x/g,_y=_y/g;
                    Num t=_y[_y.deg()];
                    _x=_x/upoly(t),_y=_y/upoly(t);
                    x=_x,y=_y;
                }
            }
        }
    }
    poly(_poly<Num> nx,_poly<Num> ny){
        x=nx,y=ny;
        simp();
    }
    poly(_poly<Num> nx){
        x=nx,y=1;
    }
    void init(const char *s,int maxlen=0x7fffffff){//多项式除法，以中间的 | 为分界符
        int len=std::min((int)std::strlen(s),maxlen);
        for (int i=0;i<len;++i){
            if (s[i]=='|'){
                x=_poly<Num>(s,i),y=_poly<Num>(s+i+1,len-i-1);
                simp();
                return ;
            }
        }
        x=_poly<Num>(s,len),y=_poly<Num>(1);
        simp();
    }
    poly(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
    Num eval(){
        return x.eval()/y.eval();
    }
    bool isconst(){
        return x.isconst() && y.isconst();
    }
};
// std::vector<std::pair<char,poly<Num> > >solvedResults;

template<class Num>
std::istream& operator >> (std::istream &in,poly<Num> &f){
    std::string s;
    in>>s;
    f.init(s.c_str());
    return in;
}
template<class Num>
std::ostream& operator << (std::ostream &out,const poly<Num> &f){
    if (f.x==_poly((Num)(0))) out<<0;
    else if (f.x==f.y) out<<1;
    else {
        if (f.y==_poly((Num)(1))) out<<f.x;
        else out<<f.x<<"|"<<f.y;
    }
    return out;
}
template<class Num>
poly<Num> operator + (poly<Num> A,poly<Num> B){
    return poly<Num>(A.x*B.y+A.y*B.x,A.y*B.y);
}
template<class Num>
poly<Num> operator - (poly<Num> A,poly<Num> B){
    return poly<Num>(A.x*B.y-A.y*B.x,A.y*B.y);
}
template<class Num>
poly<Num> operator - (poly<Num> A){
    return poly<Num>(0)-poly<Num>(A);
}
template<class Num>
poly<Num> abs(poly<Num> A){
    if (A.eval()>Num(0)) return A;
    else return -A;
}
template<class Num>
poly<Num> operator * (poly<Num> A,poly<Num> B){
    if (A.x==_poly<Num>((Num)(0)) || B.x==_poly<Num>((Num)(0)) ) return poly<Num>((Num)(0));
    if (B.x==A.y) return poly<Num>(A.x,B.y);
    if (A.x==B.y) return poly<Num>(B.x,A.y);
    if (B.x==(_poly<Num>)("0")-A.y) return poly<Num>((_poly<Num>)("0")-A.x,B.y);
    if (A.x==(_poly<Num>)("0")-B.y) return poly<Num>((_poly<Num>)("0")-B.x,A.y);
    poly tmp=poly<Num>(A.x,B.y);
    if (tmp.y==_poly<Num>((Num)(1))) return poly<Num>(tmp.x*B.x,A.y);
    if (tmp.x==_poly<Num>((Num)(1))) return poly<Num>(B.x,A.y*tmp.y);
    tmp=poly<Num>(B.x,A.y);
    if (tmp.y==_poly<Num>((Num)(1))) return poly<Num>(tmp.x*A.x,B.y);
    if (tmp.x==_poly<Num>((Num)(1))) return poly<Num>(A.x,B.y*tmp.y);
    // std::cout<<"returning "<<poly(A.x*B.x,A.y*B.y)<<std::endl;
    return poly<Num>(A.x*B.x,A.y*B.y);
}
template<class Num>
poly<Num> operator / (poly<Num> A,poly<Num> B){
    if (B.isconst()) return poly<Num>(A.x*(Num(1)/B.eval()),A.y);
    return poly<Num>(A.x*B.y,A.y*B.x);
}
template<class Num>
bool operator == (poly<Num> A,poly<Num> B){
    return (A-B).x==_poly<Num>(0);
}
template<class Num>
bool operator != (poly<Num> A,poly<Num> B){
    return !(A==B);
}
template<class Num>
poly<Num> operator ^ (poly<Num> a,int k){
    if (k==0) return poly<Num>(1);
    poly<Num> ret=a;
    for (int i=1;i<=k-1;++i) ret=ret*a;
    return ret;
}
// template<class Num>
// poly<Num> substitute(_poly<Num> p){
//     poly sub[26];
//     for (int i=0;i<26;++i){
//         poly_ele x(1);
//         x.coef=sqrtNum(1);
//         x.expo[i]=1;
//         sub[i]=x;
//     }
//     for (auto res:solvedResults){
//         sub[res.first-'a']=res.second;
//     }
//     poly ret;
//     for (auto pe:p.v){
//         poly mul(1);
//         for (int i=0;i<26;++i){
//             frac expo=pe.expo[i];
//             assert(expo.y==1);
//             mul=mul*(sub[i]^expo.x);
//         }
//         mul=mul*poly(poly_ele(pe.coef));
//         ret=ret+mul;
//     }
//     return ret;
// }
// poly substitute(poly p){
//     return substitute(p.x)/substitute(p.y);
// }
// Matrix<poly> substitute(Matrix<poly> M){
//     for (int i=1;i<=M.row;++i){
//         for (int j=1;j<=M.col;++j){
//             M[i][j]=substitute(M[i][j]);
//         }
//     }
//     return M;
// }

template<class Num>
std::string to_latex(const poly<Num> &f,bool begin=true){
    std::string ret="";
    if (begin) ret+="$";
    if (f.x==_poly(0)) ret+="0";
    else if (f.x==f.y) ret+="1";
    else {
        if (f.y==_poly(1)) ret+=to_latex(f.x,0);
        else ret+="\\frac{"+to_latex(f.x,0)+"}{"+to_latex(f.y,0)+"}";
    }
    if (begin) ret+="$";
    return ret;
}

template<class Num>
poly<Num> int_x2a2(int n,Num a){
    if (n==1){
        return _poly("t");
    }
    return poly<Num>(poly_ele<Num>(Num(1)/(a*a)))*(poly<Num>(poly_ele<Num>(Num(2*n-3,2*n-2)))*int_x2a2(n-1,a)+poly<Num>(_poly<Num>("x"),2*(n-1)*((_poly<Num>("x^2")+_poly<Num>(a*a))^(n-1))));
}

template<class Num>
cpoly<Num> Factorization(poly<Num> x){
    return Factorization(upoly<Num>(x.x));
}

// void outputResult(){
//     for (int i=0;i<solvedResults.size();++i){
//         std::cout<<solvedResults[i].first<<"="<<solvedResults[i].second<<std::endl;
//     }
// }
/*
使用 m,n,o,p... 代表未知参量
*/
// void solve(std::vector<poly>p){
//     static int id[26],alpha[27];
//     int cnt=0;
//     memset(id,0,sizeof(id));
//     for (int i=0;i<p.size();++i){
//         auto v=&p[i].x.v;
//         for (int j=0;j<v->size();++j){
//             assert((*v)[j].single());
//             auto s=(*v)[j].symb();
//             if (s.length()==0) continue;
//             if (!id[s[0]-'a']){
//                 id[s[0]-'a']=++cnt;
//                 alpha[cnt]=s[0]-'a';
//             }
//         }
//     }
//     Matrix<sqrtNum> M(p.size(),cnt),b(p.size(),1);
//     for (int i=0;i<p.size();++i){
//         auto v=&p[i].x.v;
//         for (int j=0;j<v->size();++j){
//             auto s=(*v)[j].symb();
//             if (s.length()==0){
//                 b[i+1][1]=-(*v)[j].coef;
//             }
//             else {
//                 M[i+1][id[s[0]-'a']]=(*v)[j].coef;
//             }
//         }
//     }
//     solvedResults.resize(cnt);
//     auto baseS=baseSolution(M,b);
//     for (int i=0;i<cnt;++i){
//         solvedResults[i].first=alpha[i+1]+'a';
//     }
//     for (int i=0;i<cnt;++i){
//         solvedResults[i].second=solvedResults[i].second+(baseS.back()[i+1][1]);
//     }
//     for (int i=0;i<baseS.size()-1;++i){
//         for (int j=0;j<cnt;++j){
//             poly_ele pe(baseS[i][j+1][1]);
//             pe.expo['m'+i-'a']=1;
//             solvedResults[j].second=solvedResults[j].second+poly(pe);
//         }
//     }
// }

template<class Num>
Num sqrt(poly<Num> p){
    return sqrt(p.eval());
}
#endif