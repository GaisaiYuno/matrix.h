#include <cassert>
// ��Ҫȡģ�ͼ������ͷ�ļ�
struct modNum{
    long long x,mod;
    // ��дģ���������İ�
    long long inv(){
        long long res=1,k=mod-2,b=x;
        while(k){
            if(k&1) res=1LL*res*b%mod;
            b=1LL*b*b%mod;
            k>>=1;
        }
        return res;
    }
};
modNum operator - (modNum A,modNum B){
    assert(A.mod==B.mod);
    return modNum{((A.x-B.x)%A.mod+A.mod)%A.mod,A.mod};
}
modNum operator + (modNum A,modNum B){
    assert(A.mod==B.mod);
    return modNum{(A.x+B.x)%A.mod,A.mod};
}
modNum operator * (modNum A,modNum B){
    assert(A.mod==B.mod);
    return modNum{(1LL*A.x*B.x)%A.mod,A.mod};
}
modNum operator / (modNum A,modNum B){
    assert(A.mod==B.mod);
    return modNum{(1LL*A.x*B.inv())%A.mod,A.mod};
}
modNum operator / (long long A,modNum B){
    return modNum{(1LL*A*B.inv())%B.mod,B.mod};
}
