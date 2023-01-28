#include "matrix.h"
#include "euclid.h"
#define conv_eps 1e-6
double cross(Matrix<double>P1,Matrix<double>P2){
    return P1(1)*P2(2)-P1(2)*P2(1);
}
int findSide(Matrix<double>P1,Matrix<double>P2,Matrix<double>P){
    double val=cross(P-P1,P2-P1);
    if (val>conv_eps) return 1;
    else if (val<-conv_eps) return -1;
    else return 0;
}
double lineDist(Matrix<double>P1,Matrix<double>P2,Matrix<double>P){
    return myabs(cross(P-P1,P2-P1));
}
void quickHull(std::vector<Matrix<double> >&hull,std::vector<Matrix<double> >&points,Matrix<double>P1,Matrix<double>P2,int side){
    int ind=-1;
    double max_dist=0;
    for (int i=0;i<(int)(points.size());++i){
        double temp=lineDist(P1,P2,points[i]);
        if (findSide(P1,P2,points[i])==side && temp>max_dist){
            ind=i,max_dist=temp;
        }
    }
    if (ind==-1){
        hull.push_back(P1);
        hull.push_back(P2);
        return ;
    }
    quickHull(hull,points,points[ind],P1,-findSide(points[ind],P1,P2));
    quickHull(hull,points,points[ind],P2,-findSide(points[ind],P2,P1));
}
std::vector<Matrix<double> > jarvis(std::vector<Matrix<double> >points){
    std::vector<Matrix<double> > hull;
    int ind=0;
    for (int i=1;i<(int)(points.size());++i){
        if (points[i](1)<points[ind](1)) ind=i;
    }
    Matrix<double>pointOnHull=points[ind];
    while (true){
        hull.push_back(pointOnHull);
        Matrix<double>endPoint=points[0];
        for (int j=0;j<(int)(points.size());++j){
            if (endPoint==pointOnHull||findSide(endPoint,pointOnHull,points[j])==-1){
                endPoint=points[j];
            }
        }
        pointOnHull=endPoint;
        // std::cout<<endPoint;
        if (endPoint==hull.front()) break;
    }
    return hull;
}
std::vector<Matrix<double> > Convex2D(std::vector<Matrix<double> >points,std::string method){
    if (method=="quickhull"){
        std::vector<Matrix<double> >hull;
        int min_x=0,max_x=0;
        for (int i=1;i<(int)(points.size());++i){
            if (points[i](1)<points[min_x](1)) min_x=i;
            if (points[i](1)>points[max_x](1)) max_x=i;
        }
        quickHull(hull,points,points[min_x],points[max_x],1);
        quickHull(hull,points,points[min_x],points[max_x],-1);
        std::sort(hull.begin(),hull.end(),[](Matrix<double> a,Matrix<double> b){return a(1)<b(1)?true:a(2)<b(2);});
        hull.erase(unique(hull.begin(),hull.end(),[](Matrix<double> a,Matrix<double> b){return a==b;}),hull.end());
        return hull;
    }
    else if (method=="jarvis"){
        return jarvis(points);
    }
    else{
        assert(0);
    }
}
double Simplex(Matrix<double>A,Matrix<double>b,Matrix<double>c){
    Matrix<double>M=addV(addH(c,Matrix<double>(1,1)),addH(A,b));
    int n=A.col,m=A.row;
    Matrix<int>isBasic(1,n);
    for (int i=n-m+1;i<=n;++i) isBasic(i)=true;
    int last=n+1;
    while (true){
        // std::cout<<M<<std::endl;
        int e=0;
        for (int i=1;i<=n;++i){
            if (!isBasic(i)&&M[1][i]>0){
                e=i;
                break;
            }
        }
        if (e==0){
            return -M[1][last];
        }
        int pos=0;
        double min_f=0;
        for (int i=2;i<=m+1;++i){
            if (M[i][e]>0){
                if (pos==0||M[i][last]/M[i][e]<min_f){
                    pos=i;
                    min_f=M[i][last]/M[i][e];
                }
            }
        }
        // std::cout<<pos<<std::endl;
        if (pos==0){
            return INFINITY;
        }
        else{
            int l=0;
            for (int i=1;i<=n;++i){
                if (isBasic(i)&&equals(M[pos][i],1.0)){
                    l=i;
                    break;
                }
            }
            // std::cout<<"leave "<<l<<" enter "<<e<<std::endl;
            isBasic(l)=false;
            isBasic(e)=true;
            M.times('R',pos,1/M[pos][e]);
            for (int i=1;i<=m+1;++i){
                if (i!=pos){
                    M.addtimes('R',pos,-M[i][e],i);
                }
            }
        }
    }
}