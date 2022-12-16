#include "poly_ele.h"
#include "fraction.h"
#define Num frac
#define Matrix __Matrix
#include "matrix.h"
#include <vector>
struct _poly{//不含除法
    std::vector<poly_ele>v;
    _poly(int x){
        v.clear();
        v.push_back(poly_ele(x));
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
    bool qu(char &symb,frac &maxExpo){//单元有理
        maxExpo=0;
        bool hasAlpha[26];
        memset(hasAlpha,0,sizeof(hasAlpha));
        for (int i=0;i<v.size();++i){
            for (int j=0;j<26;++j){
                hasAlpha[j]|=(v[i].expo[j]!=0);
                if (v[i].expo[j].y!=1) return false;
                maxExpo=std::max(maxExpo,v[i].expo[j]);
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
            if (p.v[i].coef.x==(0)) continue;
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
            if (p.v[i].coef.x==(0)) continue;
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
    std::vector<frac>v;
    int begin;
    upoly(){
        symb='x';
        v.clear();
        begin=0;
    }
    upoly(std::vector<frac>w){
        symb='x';
        v=w;
        begin=0;
    }
    upoly(std::vector<frac>w,int bg){
        symb='x';
        v=w;
        begin=bg;
    }
    upoly(frac f){
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
    frac delta(){
        assert(deg()==2);
        return v[1]*v[1]-4*v[0]*v[2];
    }
    void insert(int expo,frac coef){
        if (v.size()<expo+1){
            v.resize(expo+1);
            v[expo]=coef;
        }
        else{
            v[expo]=v[expo]+coef;
        }
    }
    frac val(frac x){
        frac ans=0;
        for (int i=v.size()-1;i>=0;--i){
            ans=ans*x+v[i];
        }
        return ans;
    }
    frac &operator[](int i){
        return v[i];
    }
    void init_from_poly(_poly A){
        frac maxExpo=0;
        if (A.qu(symb,maxExpo)){
            v.resize(maxExpo.x+1,0);
            for (int i=0;i<A.v.size();++i){
                v[A.v[i].expo[symb-'a'].x]=A.v[i].coef.x;
            }
        }
        else{
            assert(0);
        }
        simp();
    }
    void init(const char *s,int maxlen=0x7fffffff){
        init_from_poly(_poly(s,maxlen));
    }
    upoly(const char *s,int maxlen=0x7fffffff){
        init(s,maxlen);
    }
};
upoly Integral(upoly x){
    std::vector<frac>v;
    v.push_back(0);
    for (int i=0;i<x.v.size();++i){
        v.push_back(x.v[i]*frac(1,i+1));
    }
    return upoly(v,x.begin-1);
}
upoly Deriv(upoly x){
    std::vector<frac>v;
    for (int i=1;i<x.v.size();++i){
        v.push_back(x.v[i]*frac(i));
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
    C.v.resize(A.v.size()+B.v.size()-1);
    for (int i=0;i<A.v.size();++i){
        for (int j=0;j<B.v.size();++j){
            C[i+j]=C[i+j]+A[i]*B[j];
        }
    }
    C.symb=A.symb;
    C.simp();
    return C;
}
upoly operator * (frac lambda,upoly A){
    for (int i=0;i<A.v.size();++i){
        A[i]=A[i]*lambda;
    }
    return A;
}
upoly operator - (upoly A){
    return (frac)(-1)*A;
}
upoly operator / (upoly A,upoly B){
    assert(A.symb==B.symb);
    upoly ret;
    ret.symb=A.symb;
    while (A.deg()>=B.deg()){
        frac lambda=A[A.v.size()-1]/B[B.v.size()-1];
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
        bool flag=true;
        for (int i=100;i>=-100;--i){
            for (int j=1;j<=100;++j){
                if (A.val(frac(i,j))==0){
                    factor.symb=A.symb;
                    factor.v.resize(2);
                    factor[1]=1;
                    factor[0]=frac(-i,j);
                    flag=false;
                    break;
                }
            }
            if (!flag) break;
        }
        if (flag){
            ret.insert(A,1);
            break;
        }
        else{
            int cnt=0;
            while ((A%factor).v.size()==0){
                A=A/factor;
                cnt++;
            }
            ret.insert(factor,cnt);
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
upoly to_upoly(__Matrix M){
    upoly ret;
    int cnt=0;
    for (int i=1;i<=M.row;++i){
        for (int j=1;j<=M.col;++j){
            ret.insert(cnt++,M[i][j]);
        }
    }
    return ret;
}
__Matrix to_vector(upoly x,int sz=-1){
    if (sz==-1){
        return __Matrix('C',x.v);
    }
    else{
        __Matrix ret=__Matrix('C',x.v);
        ret.resize(sz,1);
        return ret;
    }
}
std::vector<upoly> solve_diff(std::vector<upoly>p,int rk=1){//输入的项加和为0，默认微分方程的阶为1
    int n=0x7fffffff;
    for (int i=0;i<p.size();++i){
        //std::cout<<p[i]<<std::endl;
        n=std::min(n,p[i].deg());
    }
    __Matrix M(n,n+rk);
    for (int i=0;i<p.size();++i){
        for (int j=0;j<=n;++j){//枚举x^j
            if (j+1+p[i].begin<=M.col && j+1<=M.row){
                M[j+1][j+1+p[i].begin]=M[j+1][j+1+p[i].begin]+p[i][j];
            }
        }
        std::cout<<M<<std::endl;
    }
    std::vector<__Matrix>baseS=baseSolution(M);
    std::vector<upoly>ret;
    for (int i=0;i<baseS.size();++i){
        std::cout<<baseS[i]<<std::endl;
        frac coef=1;
        for (int j=1;j<=baseS[i].row;++j){
            if (baseS[i][j][1]!=0){
                coef=baseS[i][j][1];
                break;
            }
        }
        ret.push_back(to_upoly((1/coef)*baseS[i]));
    }
    return ret;
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
    std::vector<__Matrix>v;
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
    __Matrix ans=(addH(v)^-1)*to_vector(x,z.deg());
    decomp ret;
    int cnt=0;
    for (int i=0;i<y.v.size();++i){
        int d=y.v[i].first.deg();
        for (int j=1;j<=y.v[i].second;++j){
            if (d==1){
                ret.insert(upoly(std::vector<frac>{ans[++cnt][1]}),y.v[i].first,j);
            }
            else if (d==2){
                frac B=ans[++cnt][1];
                frac D=ans[++cnt][1];
                ret.insert(upoly(std::vector<frac>{D,B}),y.v[i].first,j);
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
        t.v.push_back(frac(1,fac));
        fac=fac*i;
    }
    return F(t,p);
}
upoly Ln(upoly p){//Ln(p)，转化为(p-1)+1
    upoly t;
    t.v.push_back(0);
    int sign=1;
    for (int i=1;i<=10;++i){
        t.v.push_back(frac(1,sign*i));
        sign=sign*-1;
    }
    return F(t,p-upoly(1));
}
upoly Sin(upoly p){
    upoly t;
    long long fac=1;
    int sign=1;
    for (int i=0;i<=10;++i){
        if (i!=0) fac=fac*i;
        if (i&1){
            t.v.push_back(frac(1,sign*fac));
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
            t.v.push_back(frac(1,sign*fac));
            sign=sign*-1;
        }
        else{
            t.v.push_back(0);
        }
    }
    return F(t,p);
}
upoly Tan(upoly p){
    upoly t("x+1/3x^3+2/15x^5+17/315x^7");
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
upoly Pow(upoly p,frac alpha){//转化为(1+(x-1))^alpha
    upoly t;
    t.v.push_back(1);
    frac x=alpha,y=1;
    for (int i=1;i<=10;++i){
        t.v.push_back(x/y);
        x=x*(alpha-i),y=y*frac(i+1);
    }
    return F(t,p-upoly(1));
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
frac Limit(upoly a,upoly b){//计算a/b当x->0时的极限
    a=EquivInf(a);
    b=EquivInf(b);
    if (a.deg()==b.deg()) return (a/b)[0];
    else if (a.deg()<b.deg()){
        std::cout<<"Not Exist"<<std::endl;
        return frac(0x7fffffff,1);
    }
    else{
        return frac(0);
    }
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
    void simp(){
        //最低次项，提出来
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
                // std::cout<<x<<" "<<y<<std::endl;
                upoly _x,_y;
                _x.init_from_poly(x),_y.init_from_poly(y);
                upoly g=gcd(_x,_y);
                if (g.deg()>1){
                    _x=_x/g,_y=_y/g;
                    x=convert(_x),y=convert(_y);
                }
                // std::cout<<"G"<<g<<std::endl;
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
    poly(const char *s,int maxlen=0x7fffffff){//多项式除法，以中间的 | 为分界符
        init(s,maxlen);
    }
};

poly operator + (poly A,poly B){
    return poly(A.x*B.y+A.y*B.x,A.y*B.y);
}
poly operator - (poly A,poly B){
    return poly(A.x*B.y-A.y*B.x,A.y*B.y);
}
poly operator * (poly A,poly B){
    if (B.x==A.y) return poly(A.x,B.y);
    if (A.x==B.y) return poly(B.x,A.y);
    if (B.x==(_poly)("0")-A.y) return poly((_poly)("0")-A.x,B.y);
    if (A.x==(_poly)("0")-B.y) return poly((_poly)("0")-B.x,A.y);
    return poly(A.x*B.x,A.y*B.y);
}
poly operator / (poly A,poly B){
    // assert(!(B.x==_poly(0)));
    return poly(A.x*B.y,A.y*B.x);
}
bool operator == (poly A,poly B){
    return (A-B).x==_poly(0);
}
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
    return poly(poly_ele(sqrtNum(1)/(a*a)))*(poly(poly_ele(sqrtNum(frac(2*n-3,2*n-2))))*int_x2a2(n-1,a)+poly(_poly("x"),2*(n-1)*((_poly("x^2")+_poly(a*a))^(n-1))));
}
#undef Num
#undef Matrix
#undef _MATRIX_