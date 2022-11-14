#include <algorithm>
#include <cstring>
#include <iostream>
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
struct frac{
	long long x,y;
	void simp(){
		long long gcd=std::__gcd(x,y);
		x/=gcd,y/=gcd;
		if (y<0) x=-x,y=-y;
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
	frac(const char *s){
		int len=std::strlen(s);
		for (int i=0;i<len;++i){
			if (s[i]=='/'){
				x=toInterger(s,i),y=toInterger(s+i+1,len-i);
				// std::cout<<x<<" "<<y<<std::endl;
				simp();
				return ;
			}
		}
		x=toInterger(s,len),y=1;
	}
	frac inv(){
		return frac(y,x);
	}
	void init(const char *s){
		int len=std::strlen(s);
		for (int i=0;i<len;++i){
			if (s[i]=='/'){
				x=toInterger(s,i),y=toInterger(s+i+1,len-i);
				simp();
				return ;
			}
		}
		x=toInterger(s,len),y=1;
	}
};
frac operator + (frac A,frac B){
	return frac((A.x*B.y+A.y*B.x),A.y*B.y);
}
frac operator - (frac A,frac B){
	return frac((A.x*B.y-A.y*B.x),A.y*B.y);
}
frac operator * (frac A,frac B){
	return frac(A.x*B.x,A.y*B.y);
}
frac operator / (frac A,frac B){
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
std::istream& operator >> (std::istream &in,frac &f){
	std::string s;
	in>>s;
	f.init(s.c_str());
	return in;
}
std::ostream& operator << (std::ostream &out,const frac &f){
	if (f.y==1) out<<f.x;
	else out<<f.x<<"/"<<f.y;
	return out;
}
