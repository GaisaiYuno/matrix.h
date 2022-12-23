//欧氏空间
#include "matrix.h"
Num operator & (Matrix A,Matrix B){
    assert(A.row==B.row && A.col==B.col);
    Matrix C(A.row,A.col);
    Num ret=(Num)(0);
    for (int i=1;i<=A.row;++i){
        for (int j=1;j<=A.col;++j){
            ret=ret+A[i][j]*B[i][j];
        }
    }
    return ret;
}
Matrix Discrete(Num (*F)(frac),frac l,frac r,frac step){
    std::vector<Num>v;
    for (frac i=l;i<=r;i=i+step){
        v.push_back(F(i));
    }
    return Matrix('R',v);
}
void Cauchy_Schwarz(Matrix A,Matrix B){
    std::cout<<(A&B)*(A&B)<<"<="<<(A&A)*(B&B)<<std::endl;
}
std::vector<Matrix> Schmidt(std::vector<Matrix>alpha){
    int s=alpha.size();
    std::vector<Matrix>beta;
    for (int i=1;i<=s;++i){
        Matrix beta_i=alpha[i-1];
        for (int j=1;j<=i-1;++j){
            Num lambda=(alpha[i-1]&beta[j-1])/(beta[j-1]&beta[j-1]);
            beta_i=beta_i-lambda*beta[j-1];
        }
        beta_i.Message="\\beta_"+std::to_string(i);
        beta.push_back(beta_i);
    }
    return beta;
}
bool isOrthogonalMatrix(Matrix A){
    assert(A.row==A.col);
    return A*A.transpose()==Matrix(A.row,A.col,1);
}


auto length2(Matrix A){
    return (A&A);
}
auto dist2(Matrix A,Matrix B){
    return length2(A-B);
}
auto angle2(Matrix A,Matrix B){
    return (A&B)*(A&B)/(length2(A)*length2(B));
}

#ifndef SQRT_FIELD

#else
typedef std::pair<Matrix,Matrix> Line;
std::string Arccos(Num x){
    if (x==Num("0")) return "\\pi/2";
    if (x==Num("1/2")) return "\\pi/3";
    if (x==Num("1/2\3")) return "\\pi/6";
    if (x==Num("1")) return "0";
    return "arccos("+to_latex(x.eval(),0)+")";
}
Matrix Vector(Num A,Num B,Num C){
    return Matrix('R',std::vector<Num>{A,B,C});
}
Matrix Plane(Num A,Num B,Num C,Num D){
    return Matrix('R',std::vector<Num>{A,B,C,D});
}
Num length(Matrix A){
    return Num(sqrtNum(0,1,(A&A).eval().x));
}
auto angle(Matrix A,Matrix B){
    return (A&B)/(length(A)*length(B));
}
auto angle(Line A,Line B){
    return angle(A.second,B.second);
}
auto identilize(Matrix v){
    return std::make_pair((Num(1)/length(v))*v,(Num(-1)/length(v))*v);
}
Matrix proj(Matrix A,Matrix B){
    return (A&B)/length(A);
}
Matrix proj_vec(Matrix A,Matrix B){
    return proj(A,B)*identilize(A).first;
}
Matrix Nvec(Matrix A){
    A.resize(1,3);
    return A;
}
Matrix cross(Matrix A,Matrix B){
    if (A.row>A.col && B.row>B.col) return cross(A.transpose(),B.transpose()).transpose();
    assert(A.row==1 && A.col==3 && B.row==1 && B.col==3);
    Matrix ret(1,3);
    ret[1][1]=A[1][2]*B[1][3]-A[1][3]*B[1][2];
    ret[1][2]=-A[1][1]*B[1][3]+A[1][3]*B[1][1];
    ret[1][3]=A[1][1]*B[1][2]-A[1][2]*B[1][1];
    return ret;
}
Matrix Plane(Matrix V,Matrix P){
    Matrix ret=V;
    ret.resize(1,4);
    ret[1][4]=(V&P);
    return ret;
}
Matrix Plane(Matrix A,Matrix B,Matrix C){
    Matrix ret=cross(B-A,C-A);
    ret.resize(1,4);
    ret[1][4]=Determinant(addV(-A,B-A,C-A));
    return ret;
}
auto dot_on_pl(Matrix A,Matrix P){
    return (A&Nvec(P))+P[1][4];
}
auto para_vec_pl(Matrix L,Matrix P){
    return L&Nvec(P);
}
Matrix toIntercept(Matrix pl){
    assert(!(pl[1][4]==(Num)(0)));
    return Matrix('R',std::vector<Num>{-pl[1][1]/pl[1][4],-pl[1][2]/pl[1][4],-pl[1][3]/pl[1][4]});
}
Line toLine(Matrix A,Matrix B){
    Matrix S=addV(A,B);
    auto baseS=baseSolution(subMatrix(S,1,2,1,3),-subMatrix(S,1,2,4,4));
    return std::make_pair(baseS.back().transpose(),baseS.front().transpose());
}
Matrix distLine(Line l1,Line l2){
    Matrix P1=l1.first,V1=l1.second,P2=l2.first,V2=l2.second;
    auto baseS=baseSolution(addV(V1,V2));
    Matrix P0=baseS.back().transpose(),V0=baseS.front().transpose();
    Matrix sol=(P0-P1+P2)*(addV(-V0,V1,-V2)^(-1));
    return (P1+sol[1][2]*V1)-(P2+sol[1][3]*V2);
}
Line commonPlumb(Line l1,Line l2){
    Matrix dir=cross(l1.second,l2.second);
    Matrix n1=cross(dir,l1.second);
    Matrix n2=cross(dir,l2.second);
    auto d1=n1&l1.first,d2=n2&l2.first;
    n1.resize(1,4),n2.resize(1,4);
    n1[1][4]=d1,n2[1][4]=d2;
    // std::cout<<n1<<" "<<n2<<std::endl;
    return toLine(n1,n2);
}
auto dist_dot_pl(Matrix A,Matrix P){
    return abs(dot_on_pl(A,P))/length(Nvec(P));
}
auto dist2_dot_pl(Matrix A,Matrix P){
    auto val=dot_on_pl(A,P);
    return (val*val)/length2(Nvec(P));
}
auto dist_dot_ln(Matrix A,Line L){
    return length(cross(L.second,A-L.first))/length(L.second);
}
auto dist2_dot_ln(Matrix A,Line L){
    return length2(cross(L.second,A-L.first))/length2(L.second);
}
void output(Matrix P){
    std::cout<<P[1][1]<<"X+"<<P[1][2]<<"Y+"<<P[1][3]<<"Z+"<<P[1][4]<<"=0"<<std::endl;
}
void output(Matrix R0,Matrix S){
    std::cout<<"(X-"<<R0[1][1]<<")/"<<S[1][1]<<"=(Y-"<<R0[1][2]<<")/"<<S[1][2]<<"=(Z-"<<R0[1][3]<<")/"<<S[1][3]<<std::endl;
}
Matrix houseHolder(Matrix v){
    v=identilize(v).first;
    int n=v.row;
    return Matrix(n,n,1)-(Num(2)*v*v.transpose());
}
#endif