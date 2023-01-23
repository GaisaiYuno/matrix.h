//欧氏空间
#ifndef EUCLID_H
#define EUCLID_H
#include "matrix.h"
#include "poly.h"
template<class Num>
Num operator & (Matrix<Num> A,Matrix<Num> B){
    assert(A.row==B.row && A.col==B.col);
    Matrix<Num> C(A.row,A.col);
    Num ret=(Num)(0);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            ret=ret+A[i][j]*B[i][j];
        }
    }
    return ret;
}
template<class Num>
Matrix<Num> Discrete(Num (*F)(frac),frac l,frac r,frac step){
    std::vector<Num>v;
    for (frac i=l;i<=r;i=i+step){
        v.push_back(F(i));
    }
    return Matrix<Num>('R',v);
}
template<class Num>
void Cauchy_Schwarz(Matrix<Num> A,Matrix<Num> B){
    std::cout<<(A&B)*(A&B)<<"<="<<(A&A)*(B&B)<<std::endl;
}
template<class Num>
std::vector<Matrix<Num> > Schmidt(std::vector<Matrix<Num> >alpha){
    int s=alpha.size();
    std::vector<Matrix<Num> >beta;
    for (int i=1;i<=s;++i){
        Matrix<Num> beta_i=alpha[i-1];
        for (int j=1;j<=i-1;++j){
            Num lambda=(alpha[i-1]&beta[j-1])/(beta[j-1]&beta[j-1]);
            beta_i=beta_i-lambda*beta[j-1];
        }
        beta_i.Message="\\beta_"+std::to_string(i);
        beta.push_back(beta_i);
    }
    return beta;
}
template<class Num>
std::pair<Matrix<Num>,Matrix<Num> > QR(Matrix<Num>A){
    assert(A.row==A.col);
    Matrix<Num>R(A.row,A.col);
    auto alpha=breakAsVector(A,'C');
    int s=alpha.size();
    std::vector<Matrix<Num> >beta;
    for (int i=1;i<=s;++i){
        Matrix<Num> beta_i=alpha[i-1];
        for (int j=1;j<=i-1;++j){
            Num lambda=(alpha[i-1]&beta[j-1])/(beta[j-1]&beta[j-1]);
            beta_i=beta_i-lambda*beta[j-1];
            R[j][i]=lambda;
        }
        R[i][i]=1;
        beta.push_back(beta_i);
    }
    for (int i=1;i<=s;++i){
        Num l=length(beta[i-1]);
        beta[i-1]=(Num(1)/Num(l))*beta[i-1];
        R.times('R',i,l);
    }
    Matrix<Num>Q=addH(beta);
    return std::make_pair(Q.message("Q"),R.message("R"));
}
template<class Num>
std::pair<Matrix<Num>,Matrix<Num> > QR_HouseHolder(Matrix<Num>A){
    assert(A.row==A.col);
    int n=A.row;
    if (n==1){
        return std::make_pair(Matrix<Num>(1,1,1),A);
    }
    Matrix<Num>x=subMatrix(A,1,n,1,1);
    Num lx=length(x);
    Num beta=(Num)(1)/(Num)(lx*lx+lx*myabs(x[1][1]));
    Num sign=(Num)(x[1][1]>=0?1:-1);
    Num k=-sign*lx;
    x[1][1]-=k;
    Matrix<Num>H=Matrix<Num>(n,n,1)-beta*x*x.transpose();
    A=H*A;
    auto p=QR_HouseHolder(subMatrix(A,2,n,2,n));
    Matrix<Num>_Q(n,n);
    _Q[1][1]=1;
    for (int i=1;i<=n-1;++i){
        for (int j=1;j<=n-1;++j){
            _Q[i+1][j+1]=p.first[i][j];
        }
    }
    Matrix<Num>R(n,n);
    for (int i=1;i<=n;++i) R[1][i]=A[1][i];
    for (int i=1;i<=n-1;++i){
        for (int j=1;j<=n-1;++j){
            R[i+1][j+1]=p.second[i][j];
        }
    }
    return std::make_pair(H.transpose()*_Q.transpose(),R);
}
template<class Num>
std::vector<Num> EigenVals(Matrix<Num>A){
    assert(A.row==A.col);
    int n=A.row;
    if (n==1) return std::vector<Num>{A[1][1]};
    Matrix eye=Matrix<Num>(n,n,1);
    while(true){
        Num sigma=A[n][n];
        auto p=QR(A-sigma*eye);
        Matrix Q=p.first,R=p.second;
        A=R*Q+sigma*eye;
        bool flag=true;
        for (int i=1;i<=n-1;++i){
            if (!equals(A[n][i],(Num)(0),1e-8)){
                flag=false;
                break;
            }
        }
        if (flag) break;
    }
    Num eig_val=A[n][n];
    std::vector<Num> eig=EigenVals(subMatrix(A,1,n-1,1,n-1));
    eig.push_back(eig_val);
    return eig;
}
template<class Num>
Num length(Matrix<Num> A){
    return sqrt(Num(A&A));
}
template<class Num>
bool isOrthogonalMatrix(Matrix<Num> A){
    assert(A.row==A.col);
    return A*A.transpose()==Matrix<Num>(A.row,A.col,1);
}
template<class Num>
auto identilize(Matrix<Num> v){
    Num l=Num(1)/Num(length(v));
    return std::make_pair(l*v,-l*v);
}

template<class Num>
Num mse_loss(Matrix<Num>y_true,Matrix<Num>y_pred){
    int n=y_true.row;
    Num sum=0;
    for (int i=1;i<=n;++i) sum+=(y_true(i)-y_pred(i))*(y_true(i)-y_pred(i));
    return sum/n;
}

template<class Num>
auto identilize(std::vector<Matrix<Num> > s){
    for (int i=0;i<s.size();++i){
        s[i]=identilize(s[i]).first;
    }
    return s;
}
template<class Num>
std::vector<Matrix<Num> >baseExpansion(std::vector<Matrix<Num> > v){
    return identilize(Schmidt(baseSolution(addH(v).transpose())));
}
template<class Num>
Matrix<Num> Expand(Matrix<Num> A){
    if (A.row==A.col) return A;
    return addH(A,addH(identilize(Schmidt(baseSolution(A.transpose())))));
}
template<class Num>
auto diagonalize(Matrix<Num> A){
    assert(A.row==A.col);
    auto eig=EigenVals(A);
    std::sort(eig.begin(),eig.end(),std::greater<Num>());
    eig.erase(unique(eig.begin(),eig.end(),[](Num a,Num b){return equals(a,b);}),eig.end());
    std::vector<Matrix<Num> >s;
    for (Num lambda:eig){
        // std::cout<<lambda<<std::endl;
        Matrix<Num> B=A-lambda*Matrix<Num>(A.row,A.col,1);
        // std::cout<<Gauss(B)<<std::endl;
        auto baseS=Schmidt(baseSolution(B));
        // std::cout<<"Size of BaseS:"<<baseS.size()<<std::endl;
        for (auto x:baseS) s.push_back(x);
    }
    // assert(s.size()==A.row);
    for (auto &x:s) x=identilize(x).first;
    // std::cout<<addH(s)<<std::endl;
    Matrix<Num> Q=Expand(addH(s));
    // std::cout<<Q*Q.transpose()<<std::endl;
    // Q.resize(A.col,A.row);
    Matrix<Num> Lambda=(Q.transpose())*A*Q;
    // std::cout<<(Q*Lambda*(Q.transpose())-A)<<std::endl;
    return std::make_pair(Q,Lambda);
}
template<class Num>
auto svd(Matrix<Num> A){
    int m=A.row,n=A.col;
    auto p=diagonalize(A.transpose()*A);
    auto V=p.first,Lambda=p.second;
    auto v=breakAsVector(V,'C');
    Matrix<Num> Sigma=Lambda.resize(m,n);
    std::vector<Matrix<Num> >u;
    for (int i=1;i<=std::min(m,n);++i){
        if (!equals(Sigma[i][i],(Num)(0))){
            Sigma[i][i]=sqrt(Sigma[i][i]);
            u.push_back(((Num)(1)/Sigma[i][i])*(A*v[i-1]));
        }
    }
    Matrix<Num>U=addH(addH(u),addH(baseExpansion(u)));
    V=V.transpose();
    return std::make_tuple(U,Sigma,V);
}
template<class Num>
auto mean(std::vector<Matrix<Num> >v){
    Matrix<Num>m(v[0].row,v[0].col);
    for (auto x:v) m=m+x;
    return (Num)(1)/(Num)(v.size())*m;
}
template<class Num>
auto devi(std::vector<Matrix<Num> >v){
    Matrix<Num>M=mean(v);
    int n=v.size();
    Matrix<Num>sigma(M.row,M.col);
    for (int i=1;i<=M.col;++i){
        sigma[1][i]=0;
        for (int j=1;j<=n;++j){
            sigma[1][i]+=(v[j-1][1][i]-M[1][i])*(v[j-1][1][i]-M[1][i]);
        }
        sigma[1][i]/=n;
        sigma[1][i]=sqrt(sigma[1][i]);
    }
    return sigma;
}
template<class Num>
auto mean(Matrix<Num> A){
    Num sum=0;
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            sum+=A[i][j];
        }
    }
    return sum/(Num)(A.row*A.col);
}
template<class Num>
auto to_mean(std::vector<Matrix<Num> >v){
    Matrix m=mean(v);
    std::vector<Matrix<Num> >v_new;
    for (auto x:v) v_new.push_back(x-m);
    return v_new;
}
template<class Num>
auto to_std(std::vector<Matrix<Num> >v){
    Matrix m=mean(v),d=devi(v);
    std::vector<Matrix<Num> >v_new;
    for (auto x:v){
        Matrix y=x-m;
        for (int i=1;i<=y.col;++i) y(i)/=d(i);
        v_new.push_back(y);
    }
    return v_new;
}
template<class Num>
auto cov(std::vector<Matrix<Num> >v){
    Matrix<Num>S(v[0].col,v[0].col);
    for (auto x:v) S=S+x.transpose()*x;
    return (Num(1)/Num(v[0].col-1))*S;
}
template<class Num>
auto pca(std::vector<Matrix<Num> >v){
    auto S=cov(v);
    int n=S.col;
    auto p=diagonalize(S);
    auto V=p.first.transpose();
    V.resize(n-1,n);
    return baseSolution(V).front();
}

template<class Num>
auto pca_with_svd(std::vector<Matrix<Num> >v){
    auto S=addH(to_mean(v));
    int n=S.row;
    Matrix<Num>U,Sigma,V;
    std::tie(U,Sigma,V)=svd(S.transpose());
    V.resize(n-1,n);
    return baseSolution(V).front();
}

template<class Num>
Matrix<Num> Vector(Num A,Num B,Num C){
    return Matrix<Num>('R',std::vector<Num>{A,B,C});
}
template<class Num>
Matrix<Num> Plane(Num A,Num B,Num C,Num D){
    return Matrix<Num>('R',std::vector<Num>{A,B,C,D});
}
template<class Num>
Matrix<Num> cross(Matrix<Num> A,Matrix<Num> B){
    if (A.row>A.col && B.row>B.col) return cross(A.transpose(),B.transpose()).transpose();
    assert(A.row==1 && A.col==3 && B.row==1 && B.col==3);
    Matrix<Num> ret(1,3);
    ret[1][1]=A[1][2]*B[1][3]-A[1][3]*B[1][2];
    ret[1][2]=-A[1][1]*B[1][3]+A[1][3]*B[1][1];
    ret[1][3]=A[1][1]*B[1][2]-A[1][2]*B[1][1];
    return ret;
}
/*
template<class Num>
auto length2(Matrix<Num> A){
    return (A&A);
}
template<class Num>
auto dist2(Matrix<Num> A,Matrix<Num> B){
    return length2(A-B);
}
template<class Num>
auto angle2(Matrix<Num> A,Matrix<Num> B){
    return (A&B)*(A&B)/(length2(A)*length2(B));
}

typedef std::pair<Matrix<poly>,Matrix<poly> > Line;
template<class Num>
std::string Arccos(Num x){
    if (x==Num("0")) return "\\pi/2";
    if (x==Num("1/2")) return "\\pi/3";
    if (x==Num("1/2\3")) return "\\pi/6";
    if (x==Num("1")) return "0";
    return "arccos("+to_latex(x.eval(),0)+")";
}
auto angle(Matrix<poly> A,Matrix<poly> B){
    return (A&B)/(length(A)*length(B));
}
auto angle(Line A,Line B){
    return angle(A.second,B.second);
}
Matrix<poly> proj(Matrix<poly> A,Matrix<poly> B){
    return (A&B)/length(A);
}
Matrix<poly> proj_vec(Matrix<poly> A,Matrix<poly> B){
    return proj(A,B)*identilize(A).first;
}
Matrix<poly> Nvec(Matrix<poly> A){
    A.resize(1,3);
    return A;
}

Matrix<poly> Plane(Matrix<poly> V,Matrix<poly> P){
    Matrix<poly> ret=V;
    ret.resize(1,4);
    ret[1][4]=(V&P);
    return ret;
}
Matrix<poly> Plane(Matrix<poly> A,Matrix<poly> B,Matrix<poly> C){
    Matrix<poly> ret=cross(B-A,C-A);
    ret.resize(1,4);
    ret[1][4]=Determinant(addV(-A,B-A,C-A));
    return ret;
}
auto triple_product(Matrix<poly> A,Matrix<poly> B,Matrix<poly> C){
    return A&cross(B,C);
}
auto dot_on_pl(Matrix<poly> A,Matrix<poly> P){
    return (A&Nvec(P))+P[1][4];
}
auto common_plane(Line A,Line B){
    return triple_product(A.first-B.first,A.second,B.second);
}
auto para_vec_pl(Matrix<poly> L,Matrix<poly> P){
    return L&Nvec(P);
}
Matrix<poly> toIntercept(Matrix<poly> pl){
    assert(!(pl[1][4]==(poly)(0)));
    return Matrix('R',std::vector<poly>{-pl[1][1]/pl[1][4],-pl[1][2]/pl[1][4],-pl[1][3]/pl[1][4]});
}
Line toLine(Matrix<poly> A,Matrix<poly> B){
    Matrix<poly> S=addV(A,B);
    auto baseS=baseSolution(subMatrix(S,1,2,1,3),-subMatrix(S,1,2,4,4));
    return std::make_pair(baseS.back().transpose(),baseS.front().transpose());
}
Line distLine(Line l1,Line l2){
    Matrix<poly> P1=l1.first,V1=l1.second,P2=l2.first,V2=l2.second;
    auto baseS=baseSolution(addV(V1,V2));
    Matrix<poly> P0=baseS.back().transpose(),V0=baseS.front().transpose();
    Matrix<poly> sol=(P0-P1+P2)*(addV(-V0,V1,-V2)^(-1));
    return Line((P1+sol[1][2]*V1),(P1+sol[1][2]*V1)-(P2+sol[1][3]*V2));
}
Line commonPlumb(Line l1,Line l2){
    Matrix<poly> dir=cross(l1.second,l2.second);
    Matrix<poly> n1=cross(dir,l1.second);
    Matrix<poly> n2=cross(dir,l2.second);
    auto d1=n1&l1.first,d2=n2&l2.first;
    n1.resize(1,4),n2.resize(1,4);
    n1[1][4]=d1,n2[1][4]=d2;
    return toLine(n1,n2);
}
auto dist_dot_pl(Matrix<poly> A,Matrix<poly> P){
    return abs(dot_on_pl(A,P))/length(Nvec(P));
}
auto dist2_dot_pl(Matrix<poly> A,Matrix<poly> P){
    auto val=dot_on_pl(A,P);
    return (val*val)/length2(Nvec(P));
}
auto dist_dot_ln(Matrix<poly> A,Line L){
    return length(cross(L.second,A-L.first))/length(L.second);
}
auto dist2_dot_ln(Matrix<poly> A,Line L){
    return length2(cross(L.second,A-L.first))/length2(L.second);
}
void output(Matrix<poly> P){
    std::cout<<P[1][1]<<"X+"<<P[1][2]<<"Y+"<<P[1][3]<<"Z+"<<P[1][4]<<"=0"<<std::endl;
}
void output(Line L){
    std::cout<<"(X-"<<L.first[1][1]<<")/"<<L.second[1][1]<<"=(Y-"<<L.first[1][2]<<")/"<<L.second[1][2]<<"=(Z-"<<L.first[1][3]<<")/"<<L.second[1][3]<<std::endl;
}
Matrix<poly> houseHolder(Matrix<poly> v){
    v=identilize(v).first;
    int n=v.row;
    return Matrix<poly>(n,n,1)-(poly(2)*v*v.transpose());
}
*/
#endif