
#include "poly_ele.h"
#include "fraction.h"
#include "matrix.h"
#include <vector>

#ifndef POLY_H
#define POLY_H
struct _poly{//不含除法
    std::vector<poly_ele>v;
    _poly(int x){
        v.clear();
        v.push_back(poly_ele(x));
    }
    _poly(poly_ele x){
        v.clear();
        v.push_back(x);
    }
    _poly(sqrtNum x){
        v.clear();
        v.push_back(poly_ele(x));
    }
    _poly(){
        v.clear();
    }
    poly_ele &operator[](int i){
        return v[i];
    }
    poly_ele &operator[](std::string s){
        for (auto it=v.begin();it!=v.end();++it){
            if ((*it).symb()==s) return *it;
        }
        static poly_ele p=poly_ele(0);
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
    bool insert(poly_ele x){
        if (x.coef==(sqrtNum)(0)){
            return true;
        }
        bool found=false;
        int j=0;
        for (std::vector<poly_ele>::iterator i=v.begin();i!=v.end();i++,j++){
            if (equal(x,*i)){
                found=true;
                v[j]=v[j]+x;
                if (v[j].coef==sqrtNum(0)){
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
                poly_ele new_ele;
                new_ele.init(s,i);
                insert(new_ele);
            }
            if (lastSign!=-1 &&(s[i]=='+' || s[i]=='-')){
                poly_ele new_ele;
                new_ele.init(s+lastSign+1,i-lastSign-1);
                new_ele.coef=new_ele.coef*(sqrtNum)(sign);
                insert(new_ele);
            }
            if (s[i]=='+'||s[i]=='-'){
                lastSign=i;sign=(s[i]=='+')?1:-1;
            }
        }
        if (lastSign==-1){
            poly_ele new_ele;
            new_ele.init(s,len);
            insert(new_ele);
        }else{
            poly_ele new_ele;
            new_ele.init(s+lastSign+1,len-lastSign-1);
            new_ele.coef=new_ele.coef*(sqrtNum)(sign);
            insert(new_ele);
        }
    }
    _poly(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
    sqrtNum eval(){
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
_poly operator + (_poly A,_poly B){
    for (int i=0;i<B.v.size();++i){
        A.insert(B[i]);
    }
    return A;
}
_poly operator - (_poly A,_poly B){
    for (int i=0;i<B.v.size();++i){
        A.insert(B[i].minus());
    }
    return A;
}
_poly operator * (_poly A,_poly B){
    _poly C;
    for (int i=0;i<A.v.size();++i){
        for (int j=0;j<B.v.size();++j){
            C.insert(A[i]*B[j]);
        }
    }
    return C;
}
_poly operator ^ (_poly a,int k){
    if (k==0) return _poly(1);
    _poly ret=a;
    for (int i=1;i<=k-1;++i) ret=ret*a;
    return ret;
}
bool operator == (_poly A,_poly B){
    return (A-B).v.size()==0;
}
std::ostream& operator << (std::ostream &out,const _poly &p){
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
std::istream& operator >> (std::istream &in,_poly &p){
    std::string s;
    in>>s;
    p=_poly(s.c_str());
    return in;
}
std::string to_latex(const _poly &p,bool begin=true){
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


//单元有理多项式，写为 a0+a1x+a2x^2+... 的形式
struct upoly{
    //规定只有0的多项式度数为-1
    char symb;
    std::vector<sqrtNum>v;
    int begin;
    upoly(){
        symb='x';
        v.clear();
        begin=0;
    }
    upoly(std::vector<sqrtNum>w){
        symb='x';
        v=w;
        begin=0;
    }
    upoly(std::vector<sqrtNum>w,int bg){
        symb='x';
        v=w;
        begin=bg;
    }
    upoly(sqrtNum f){
        symb='x';
        v.clear(),v.push_back(f);
        begin=0;
    }
    void simp(){
        for (int i=v.size()-1;i>=0;--i){
            if (!(v[i]==0)){
                v.resize(i+1);
                return ;
            }
        }
        v.resize(0);
        // v.resize()
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
    sqrtNum delta(){
        assert(deg()==2);
        return v[1]*v[1]-4*v[0]*v[2];
    }
    void insert(int expo,sqrtNum coef){
        if (v.size()<expo+1){
            v.resize(expo+1);
            v[expo]=coef;
        }
        else{
            v[expo]=v[expo]+coef;
        }
    }
    sqrtNum val(sqrtNum x){
        sqrtNum ans=0;
        for (int i=v.size()-1;i>=0;--i){
            ans=ans*x+v[i];
        }
        return ans;
    }
    sqrtNum &operator[](int i){
        return v[i];
    }
    void init_from_poly(_poly A){
        frac maxExpo=0;
        if (A.qu(symb,maxExpo)){
            assert(maxExpo.y==1);
            v.resize(maxExpo.x+1,0);
            for (int i=0;i<A.v.size();++i){
                v[A.v[i].expo[symb-'a'].x]=A.v[i].coef.x;
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
    upoly(_poly x){
        init_from_poly(x);
    }
};
upoly Integral(upoly x){
    std::vector<sqrtNum>v;
    v.push_back(0);
    for (int i=0;i<x.v.size();++i){
        v.push_back(x.v[i]*sqrtNum(1,i+1));
    }
    return upoly(v,x.begin-1);
}
upoly Deriv(upoly x){
    std::vector<sqrtNum>v;
    if (x.v.size()==0){
        v.push_back(0);
        return upoly(v,x.begin+1);
    }
    for (int i=1;i<x.v.size();++i){
        v.push_back(x.v[i]*sqrtNum(i));
    }
    return upoly(v,x.begin+1);
}
_poly convert(upoly A){
    _poly ret;
    for (int i=A.v.size()-1;i>=0;--i){
        poly_ele t;
        t.coef=sqrtNum(A.v[i]);
        t.expo[A.symb-'a']=i;
        ret.insert(t);
    }
    return ret;
}
std::string to_latex(const upoly &p,bool begin=true){
    std::string ret="";
    if (begin) ret+="$";
    ret+=to_latex(convert(p),0);
    if (begin) ret+="$";
    return ret;
}
upoly shift(int delta,const upoly &A){
    upoly B;
    B.v.resize(A.v.size()+delta,0);
    for (int i=0;i<A.v.size();++i){
        if (i+delta>=0) B[i+delta]=A.v[i];
    }
    B.symb=A.symb;
    B.begin=A.begin-delta;
    return B;
}
std::ostream& operator << (std::ostream &out,const upoly &p){
    _poly _p=convert(p);
    out<<_p;
    return out;
}
std::istream& operator >> (std::istream &in,upoly &p){
    std::string s;
    in>>s;
    p.init_from_poly(_poly(s.c_str()));
    return in;
}
upoly operator + (upoly A,upoly B){
    assert(A.symb==B.symb);
    upoly C;
    C.v.resize(std::max(A.v.size(),B.v.size()));
    for (int i=0;i<A.v.size();++i) C[i]=C[i]+A[i];
    for (int i=0;i<B.v.size();++i) C[i]=C[i]+B[i];
    C.symb=A.symb;
    C.simp();
    return C;
}
upoly operator - (upoly A,upoly B){
    assert(A.symb==B.symb);
    upoly C;
    C.v.resize(std::max(A.v.size(),B.v.size()));
    for (int i=0;i<A.v.size();++i) C[i]=C[i]+A[i];
    for (int i=0;i<B.v.size();++i) C[i]=C[i]-B[i];
    C.symb=A.symb;
    C.simp();
    return C;
}
upoly operator * (upoly A,upoly B){
    assert(A.symb==B.symb);
    upoly C;
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
upoly operator * (sqrtNum lambda,upoly A){
    for (int i=0;i<A.v.size();++i){
        A[i]=A[i]*lambda;
    }
    return A;
}
upoly operator - (upoly A){
    return (sqrtNum)(-1)*A;
}
upoly operator / (upoly A,upoly B){
    assert(A.symb==B.symb);
    upoly ret;
    ret.symb=A.symb;
    while (A.deg()>=B.deg()){
        sqrtNum lambda=A[A.v.size()-1]/B[B.v.size()-1];
        ret.insert(A.deg()-B.deg(),lambda);
        A=A-lambda*shift(A.deg()-B.deg(),B);
    }
    return ret;
}
upoly operator % (upoly A,upoly B){
    return A-B*(A/B);
}
upoly gcd(upoly A,upoly B){
    if (B.is_zero()) return A;
    return gcd(B,A%B);
}
upoly F(upoly x,upoly a){
    upoly ans;
    for (int i=x.v.size()-1;i>=0;--i){
        ans=ans*a+x.v[i];
    }
    return ans;
}
upoly operator ^ (upoly a,int k){
    upoly ret=a;
    for (int i=1;i<=k-1;++i) ret=ret*a;
    return ret;
}
bool comp(std::pair<upoly,int>A,std::pair<upoly,int>B){
    return A.first[1]<B.first[1];
}
struct cpoly{
    std::vector<std::pair<upoly,int> >v;
    void insert(upoly x,int expo){
        v.push_back(std::make_pair(x,expo));
    }
    void sort(){
        std::sort(v.begin(),v.end(),comp);
    }
    auto sol(){
        std::vector<sqrtNum>solution;
        for (int i=0;i<v.size();++i){
            if (v[i].first.deg()==1){
                solution.push_back(-v[i].first[0]/v[i].first[1]);
            }
            else if (v[i].first.deg()==2){
                sqrtNum a=v[i].first[2],b=v[i].first[1],c=v[i].first[0];
                sqrtNum delta=b*b-4*a*c;
                solution.push_back(sqrtNum(-b/(2*a),1/(2*a),delta));
                solution.push_back(sqrtNum(-b/(2*a),-1/(2*a),delta));
            }
        }
        return solution;
    }
};
std::ostream& operator << (std::ostream &out,const cpoly &p){
    for (int i=0;i<p.v.size();++i){
        out<<"("<<p.v[i].first<<")";
        if (p.v[i].second!=1){
            out<<"^"<<p.v[i].second;
        }
    }
    return out;
}
std::istream& operator >> (std::istream &in,cpoly &p){
    int num;
    in>>num;
    while (num--){
        upoly t;
        int expo;
        in>>t>>expo;
        p.insert(t,expo);
    }
    return in;
}
std::string to_latex(const cpoly &p,bool begin=true){
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
//对A进行因式分解
cpoly Factorization(upoly A){
    cpoly ret;
    while (A.deg()){
        upoly factor;
        bool flag1=true,flag2=true;
        for (int i=100;i>=-100;--i){
            for (int j=1;j<=100;++j){
                if (A.val(sqrtNum(i,j))==0){
                    factor.symb=A.symb;
                    factor.v.resize(2);
                    factor[1]=1;
                    factor[0]=sqrtNum(-i,j);
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
                            sqrtNum p(ip,jp),q(iq,jq);
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
upoly to_upoly(cpoly x){
    upoly ret;
    ret.insert(0,1);
    for (int i=0;i<x.v.size();++i){
        for (int j=1;j<=x.v[i].second;++j){
            ret=ret*x.v[i].first;
        }
    }
    return ret;
}
upoly to_upoly(Matrix<sqrtNum> M){
    upoly ret;
    int cnt=0;
    for (int i=1;i<=M.row;++i){
        for (int j=1;j<=M.col;++j){
            ret.insert(cnt++,M[i][j]);
        }
    }
    return ret;
}
auto to_vector(upoly x,int sz=-1){
    if (sz==-1){
        return Matrix<sqrtNum>('C',x.v);
    }
    else{
        auto ret=Matrix<sqrtNum>('C',x.v);
        ret.resize(sz,1);
        return ret;
    }
}
struct decomp{
    std::vector< std::pair<upoly,std::pair<upoly,int> > >v;
    decomp(){
        v.clear();
    }
    void insert(upoly x,upoly y,int expo){
        v.push_back(std::make_pair(x,std::make_pair(y,expo)));
    }
};
std::ostream& operator << (std::ostream &out,const decomp &p){
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
decomp Decomposit(upoly x,cpoly y){
    upoly z=to_upoly(y);
    std::vector<Matrix<sqrtNum> >v;
    cpoly temp=y;
    for (int i=0;i<y.v.size();++i){
        int d=y.v[i].first.deg();
        for (int j=1;j<=y.v[i].second;++j){
            temp.v[i].second=y.v[i].second-j;
            if (d==1){
                v.push_back(to_vector(to_upoly(temp),z.deg()));
            }
            else if (d==2){
                v.push_back(to_vector(shift(1,to_upoly(temp)),z.deg()));
                v.push_back(to_vector(to_upoly(temp),z.deg()));
            }
            else{
                assert(0);
            }
            temp.v[i].second=y.v[i].second;
        }
    }
    Matrix<sqrtNum>ans=(addH(v)^-1)*to_vector(x,z.deg());
    decomp ret;
    int cnt=0;
    for (int i=0;i<y.v.size();++i){
        int d=y.v[i].first.deg();
        for (int j=1;j<=y.v[i].second;++j){
            if (d==1){
                ret.insert(upoly(std::vector<sqrtNum>{ans[++cnt][1]}),y.v[i].first,j);
            }
            else if (d==2){
                sqrtNum B=ans[++cnt][1];
                sqrtNum D=ans[++cnt][1];
                ret.insert(upoly(std::vector<sqrtNum>{D,B}),y.v[i].first,j);
            }
        }
    }
    return ret;
}

//一些泰勒公式
upoly Exp(upoly p){
    upoly t;
    long long fac=1;
    for (int i=1;i<=10;++i){
        t.v.push_back(sqrtNum(1,fac));
        fac=fac*i;
    }
    return F(t,p);
}
upoly Ln(upoly p){//Ln(p)，转化为(p-1)+1
    upoly t;
    t.v.push_back(0);
    int sign=1;
    for (int i=1;i<=10;++i){
        t.v.push_back(sqrtNum(1,sign*i));
        sign=sign*-1;
    }
    return F(t,p-upoly("1"));
}
upoly Sin(upoly p){
    upoly t;
    long long fac=1;
    int sign=1;
    for (int i=0;i<=10;++i){
        if (i!=0) fac=fac*i;
        if (i&1){
            t.v.push_back(sqrtNum(1,sign*fac));
            sign=sign*-1;
        }
        else{
            t.v.push_back(0);
        }
    }
    return F(t,p);
}
upoly Cos(upoly p){
    upoly t;
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
upoly Tan(upoly p){
    upoly t("x+1/3x^3+2/15x^5+17/315x^7+62/2835x^9+1382/155925x^11");
    return F(t,p);
}
upoly Arctan(upoly p){
    upoly t("x-1/3x^3+1/5x^5-1/7x^7");
    return F(t,p);
}
upoly Arcsin(upoly p){
    upoly t("x+1/6x^3+3/40x^5");
    return F(t,p);
}
upoly Pow(upoly p,sqrtNum alpha){//转化为(1+(x-1))^alpha
    upoly t;
    t.v.push_back(1);
    sqrtNum x=alpha,y=1;
    for (int i=1;i<=10;++i){
        t.v.push_back(x/y);
        x=x*(alpha-i),y=y*sqrtNum(i+1);
    }
    return F(t,p-upoly("1"));
}
upoly Pow(upoly a,upoly x){
    return Exp(Ln(a)*x);
}
upoly EquivInf(upoly x){
    upoly ret;
    for (int i=0;i<x.v.size();++i){
        if (x.v[i]!=0){
            ret.v.resize(i+1);
            ret.v[i]=x.v[i];
            return ret;
        }
    }
    return ret;
}
auto Limit(upoly a,upoly b){//计算a/b当x->0时的极限
    a=EquivInf(a);
    b=EquivInf(b);
    if (a.deg()==b.deg()) return (a/b)[0];
    else if (a.deg()<b.deg()){
        std::cout<<"Not Exist"<<std::endl;
        return sqrtNum(0x7fffffff,1);
    }
    else{
        return sqrtNum(0);
    }
}
auto definiteInt(upoly x,sqrtNum l,sqrtNum r){
    upoly ix=Integral(x);
    return F(ix,r)-F(ix,l);
}
auto definiteInt(upoly x,upoly l,upoly r){
    upoly ix=Integral(x);
    return F(ix,r)-F(ix,l);
}
auto variableLimit(upoly x,upoly l,upoly r){
    return Integral(F(x,r)*Deriv(r)-F(x,l)*Deriv(l));
}


struct poly{//含除法
    _poly x,y;
    poly(){
        x.v.clear(),y.v.clear();
        x.insert(poly_ele(0));
        y.insert(poly_ele(1));
    }
    poly(int n){
        x.v.clear(),y.v.clear();
        x.insert(poly_ele(n));
        y.insert(poly_ele(1));
    }
    poly(poly_ele n){
        x.v.clear(),y.v.clear();
        x.insert(n);
        y.insert(poly_ele(1));
    }
    poly(sqrtNum n){
        x.v.clear(),y.v.clear();
        x.insert(poly_ele(n));
        y.insert(poly_ele(1));
    }
    void simp(){
        // //最低次项，提出来
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
        poly_ele pe;
        pe.coef=sqrtNum(1);
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
            x.insert(_pe),y.insert(poly_ele(1));
        }
        char cx,cy;
        frac fx,fy;
        if (x.qu(cx,fx) && y.qu(cy,fy)){
            if (cx==cy){
                static upoly _x,_y;
                _x.init_from_poly(x),_y.init_from_poly(y);
                upoly g=gcd(_x,_y);
                if (g.deg()>1){
                    _x=_x/g,_y=_y/g;
                    sqrtNum t=_y[_y.deg()];
                    _x=_x/t,_y=_y/t;
                    x=convert(_x),y=convert(_y);
                }
            }
        }
    }
    poly(_poly nx,_poly ny){
        x=nx,y=ny;
        simp();
    }
    poly(_poly nx){
        x=nx,y=1;
    }
    void init(const char *s,int maxlen=0x7fffffff){//多项式除法，以中间的 | 为分界符
        int len=std::min((int)std::strlen(s),maxlen);
        for (int i=0;i<len;++i){
            if (s[i]=='|'){
                x=_poly(s,i),y=_poly(s+i+1,len-i-1);
                simp();
                return ;
            }
        }
        x=_poly(s,len),y=_poly(1);
        simp();
    }
    poly(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
    sqrtNum eval(){
        return x.eval()/y.eval();
    }
    bool isconst(){
        return x.isconst() && y.isconst();
    }
};
std::vector<std::pair<char,poly> >solvedResults;

int trig_add,trig_minus,trig_mul,trig_div;
std::istream& operator >> (std::istream &in,poly &f){
    std::string s;
    in>>s;
    f.init(s.c_str());
    return in;
}
std::ostream& operator << (std::ostream &out,const poly &f){
    if (f.x==_poly(0)) out<<0;
    else if (f.x==f.y) out<<1;
    else {
        if (f.y==_poly(1)) out<<f.x;
        else out<<f.x<<"|"<<f.y;
    }
    return out;
}
poly operator + (poly A,poly B){
    trig_add++;
    return poly(A.x*B.y+A.y*B.x,A.y*B.y);
}
poly operator - (poly A,poly B){
    trig_minus++;
    return poly(A.x*B.y-A.y*B.x,A.y*B.y);
}
poly operator - (poly A){
    return poly(0)-poly(A);
}
poly abs(poly A){
    if (A.eval()>sqrtNum(0)) return A;
    else return -A;
}
poly operator * (poly A,poly B){
    // std::cout<<A<<" "<<B<<std::endl;
    trig_mul++;
    if (A.x==0 || B.x==0) return poly(0);
    if (B.x==A.y) return poly(A.x,B.y);
    if (A.x==B.y) return poly(B.x,A.y);
    if (B.x==(_poly)("0")-A.y) return poly((_poly)("0")-A.x,B.y);
    if (A.x==(_poly)("0")-B.y) return poly((_poly)("0")-B.x,A.y);
    poly tmp=poly(A.x,B.y);
    if (tmp.y==1) return poly(tmp.x*B.x,A.y);
    if (tmp.x==1) return poly(B.x,A.y*tmp.y);
    tmp=poly(B.x,A.y);
    if (tmp.y==1) return poly(tmp.x*A.x,B.y);
    if (tmp.x==1) return poly(A.x,B.y*tmp.y);
    // std::cout<<"returning "<<poly(A.x*B.x,A.y*B.y)<<std::endl;
    return poly(A.x*B.x,A.y*B.y);
}
poly operator / (poly A,poly B){
    trig_div++;
    if (B.isconst()) return poly(A.x*(sqrtNum(1)/B.eval()),A.y);
    return poly(A.x*B.y,A.y*B.x);
}
bool operator == (poly A,poly B){
    return (A-B).x==_poly(0);
}
bool operator != (poly A,poly B){
    return !(A==B);
}
poly operator ^ (poly a,int k){
    if (k==0) return poly(1);
    poly ret=a;
    for (int i=1;i<=k-1;++i) ret=ret*a;
    return ret;
}
poly substitute(_poly p){
    poly sub[26];
    for (int i=0;i<26;++i){
        poly_ele x(1);
        x.coef=sqrtNum(1);
        x.expo[i]=1;
        sub[i]=x;
    }
    for (auto res:solvedResults){
        sub[res.first-'a']=res.second;
    }
    poly ret;
    for (auto pe:p.v){
        poly mul(1);
        for (int i=0;i<26;++i){
            frac expo=pe.expo[i];
            assert(expo.y==1);
            mul=mul*(sub[i]^expo.x);
        }
        mul=mul*poly(poly_ele(pe.coef));
        ret=ret+mul;
    }
    return ret;
}
poly substitute(poly p){
    return substitute(p.x)/substitute(p.y);
}
Matrix<poly> substitute(Matrix<poly> M){
    for (int i=1;i<=M.row;++i){
        for (int j=1;j<=M.col;++j){
            M[i][j]=substitute(M[i][j]);
        }
    }
    return M;
}

std::string to_latex(const poly &f,bool begin=true){
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

poly int_x2a2(int n,sqrtNum a){
    if (n==1){
        return _poly("t");
    }
    return poly(poly_ele(sqrtNum(1)/(a*a)))*(poly(poly_ele(sqrtNum(2*n-3,2*n-2)))*int_x2a2(n-1,a)+poly(_poly("x"),2*(n-1)*((_poly("x^2")+_poly(a*a))^(n-1))));
}
// poly substitute(poly p){
//     return poly(substitute(p.x),substitute(p.y));
// }

cpoly Factorization(poly x){
    return Factorization(upoly(x.x));
}

void outputResult(){
    for (int i=0;i<solvedResults.size();++i){
        std::cout<<solvedResults[i].first<<"="<<solvedResults[i].second<<std::endl;
    }
}
/*
使用 m,n,o,p... 代表未知参量
*/
void solve(std::vector<poly>p){
    static int id[26],alpha[27];
    int cnt=0;
    memset(id,0,sizeof(id));
    for (int i=0;i<p.size();++i){
        auto v=&p[i].x.v;
        for (int j=0;j<v->size();++j){
            assert((*v)[j].single());
            auto s=(*v)[j].symb();
            if (s.length()==0) continue;
            if (!id[s[0]-'a']){
                id[s[0]-'a']=++cnt;
                alpha[cnt]=s[0]-'a';
            }
        }
    }
    Matrix<sqrtNum> M(p.size(),cnt),b(p.size(),1);
    for (int i=0;i<p.size();++i){
        auto v=&p[i].x.v;
        for (int j=0;j<v->size();++j){
            auto s=(*v)[j].symb();
            if (s.length()==0){
                b[i+1][1]=-(*v)[j].coef;
            }
            else {
                M[i+1][id[s[0]-'a']]=(*v)[j].coef;
            }
        }
    }
    solvedResults.resize(cnt);
    auto baseS=baseSolution(M,b);
    for (int i=0;i<cnt;++i){
        solvedResults[i].first=alpha[i+1]+'a';
    }
    for (int i=0;i<cnt;++i){
        solvedResults[i].second=solvedResults[i].second+(baseS.back()[i+1][1]);
    }
    for (int i=0;i<baseS.size()-1;++i){
        for (int j=0;j<cnt;++j){
            poly_ele pe(baseS[i][j+1][1]);
            pe.expo['m'+i-'a']=1;
            solvedResults[j].second=solvedResults[j].second+poly(pe);
        }
    }
}
sqrtNum Sqrt(poly p){
    return Sqrt(p.eval());
}
#endif