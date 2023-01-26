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
std::vector<Matrix<double> > Convex2D(std::vector<Matrix<double> >points){
    std::vector<Matrix<double> >hull;
    int min_x=0,max_x=0;
    for (int i=0;i<(int)(points.size());++i){
        if (points[i](1)<points[min_x](1)) min_x=i;
        if (points[i](1)>points[max_x](1)) max_x=i;
    }
    quickHull(hull,points,points[min_x],points[max_x],1);
    quickHull(hull,points,points[min_x],points[max_x],-1);
    // for (auto pt:hull) std::cout<<pt;
    std::sort(hull.begin(),hull.end(),[](Matrix<double> a,Matrix<double> b){return a(1)<b(1)?true:a(2)<b(2);});
    hull.erase(unique(hull.begin(),hull.end(),[](Matrix<double> a,Matrix<double> b){return a==b;}),hull.end());
    return hull;
}