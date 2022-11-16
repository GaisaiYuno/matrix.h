#include "poly_ele.h"
#include <vector>
struct _poly{//不含乘除法
    std::vector<poly_ele>v;
    _poly(int x){
        v.clear();
        v.push_back(poly_ele(x));
    }
    _poly(){
        v.clear();
    }
    poly_ele &operator[](int i){
        return v[i];
    }
    bool insert(poly_ele x){
        if (x.coef==(frac)(0)){
            return true;
        }
        bool found=false;
        int j=0;
        for (std::vector<poly_ele>::iterator i=v.begin();i!=v.end();i++,j++){
            if (equal(x,*i)){
                found=true;
                v[j]=v[j]+x;
                if (v[j].coef==frac(0)){
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
                new_ele.coef=new_ele.coef*(frac)(sign);
                insert(new_ele);
            }
            if (s[i]=='+'||s[i]=='-'){
                lastSign=i;sign=(s[i]=='+')?1:-1;
            }
        }
        if (lastSign==-1){
            poly_ele new_ele;
            new_ele.init(s,len);
            // std::cout<<new_ele<<std::endl;
            insert(new_ele);
        }else{
            poly_ele new_ele;
            new_ele.init(s+lastSign+1,len-lastSign-1);
            new_ele.coef=new_ele.coef*(frac)(sign);
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
bool operator == (_poly A,_poly B){
    return (A-B).v.size()==0;
}
std::ostream& operator << (std::ostream &out,const _poly &p){
    // std::cout<<"outing _poly"<<p.v.size()<<std::endl;
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
std::istream& operator >> (std::istream &in,_poly &p){
    std::string s;
    in>>s;
    p=_poly(s.c_str());
    return in;
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
        pe.coef=frac(1);
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
    }
    poly(_poly nx,_poly ny){
        x=nx,y=ny;
        simp();
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
